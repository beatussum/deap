/*
 * Copyright (C) 2019 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "database/Database.hpp"

#include "core/FilePath.hpp"
#include "database/entity/User.hpp"

#include <QtSql/QSqlQuery>
#include <QtCore/QVariant>
#include <QtCore/QCryptographicHash>

Database::Database()
{
    const FilePath f;

    m_db = QSqlDatabase::database(QSqlDatabase::defaultConnection, false);
    if (!m_db.isValid())
        m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName(f.getUserDataPath() + m_kDbName);
}

bool Database::init()
{
    bool a = m_db.open();

    if (a && isEmpty())
        a = createDb();

    return a;
}

bool Database::createDb() const
{
    QSqlQuery q;

    bool a = q.exec("PRAGMA foreign_keys = ON");
    a &= q.exec("PRAGMA user_version = " + QString::number(m_kDbVersion));

    a &= q.exec("CREATE TABLE user "
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "first_name TEXT, "
                "last_name TEXT, "
                "pseudo TEXT NOT NULL, "
                "password BLOB NOT NULL, "
                "avatar BLOB, "
                "vote INTEGER REFERENCES user (id) "
                "    DEFERRABLE INITIALLY DEFERRED, "
                "desc TEXT, "
                "status INTEGER)");
    a &= q.exec("CREATE UNIQUE INDEX full_name "
                "ON user (first_name, last_name)");

    a &= q.prepare("INSERT OR FAIL INTO user (id, pseudo, password, status) "
                   "VALUES (0, 'root', :password, :status)");
    q.bindValue(":password",
                QCryptographicHash::hash("password", QCryptographicHash::Sha256));
    q.bindValue(":status", User::Admin);
    a &= q.exec();

    return a;
}

uint8_t Database::getDbVersion() const
{
    QSqlQuery q;

    q.exec("PRAGMA user_version");
    q.last();

    return static_cast<uint8_t>(q.value(0).toUInt());
}

User* Database::login(const QString& pseudo,
                      const QString& password) const
{
    QSqlQuery q;

    q.prepare("SELECT * FROM user "
              "WHERE pseudo = :pseudo");
    q.bindValue(":pseudo", pseudo);

    bool ok = false;
    if (q.exec() && q.first()) {
        ok = QCryptographicHash::hash(password.toUtf8(),
                                      QCryptographicHash::Sha256)
             == q.value("password").toByteArray();
    }

    User* user = nullptr;
    if (ok) {
        user = new User(static_cast<uint8_t>(q.value("id").toUInt()));

        user->firstName = q.value("first_name").toString();
        user->lastName = q.value("last_name").toString();
        user->pseudo = q.value("pseudo").toString();
        user->desc = q.value("desc").toString();

        QPixmap* pixmap = nullptr;
        QByteArray pixmapByte = q.value("avatar").toByteArray();
        if (!pixmapByte.isNull()) {
            pixmap = new QPixmap();
            pixmap->loadFromData(pixmapByte);
        }
        user->avatar = pixmap;

        uint8_t status = static_cast<uint8_t>(q.value("status").toUInt());
        if (status & User::Admin) {
            user->status |= User::Admin;
        } else if (status & User::Candidate) {
            user->status |= User::Candidate;
        }
    }

    return user;
}

bool Database::vote(const User& voter, const User& candidate) const
{
    QSqlQuery q;

    q.prepare("INSERT OR IGNORE INTO user (vote) "
              "VALUES (:voter) "
              "WHERE id = :candidate");
    q.bindValue("voter", voter.id);
    q.bindValue("candidate", candidate.id);

    return q.exec();
}
