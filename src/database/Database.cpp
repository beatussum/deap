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


#include "Database.hpp"
#include "config-deap.hpp"

#include <QStandardPaths>
#include <QScopedPointer>
#include <QDir>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QVariant>

const QString Database::m_kDbName = "deap.db";

Database::Database()
#ifndef BUILD_TYPE_DEBUG
    : m_path(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/")
#endif
{
    m_db = QSqlDatabase::database(QSqlDatabase::defaultConnection, false);
    if (!m_db.isValid())
        m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName(m_path + m_kDbName);
}

bool Database::init()
{
    bool a = true;

    if (!m_path.isEmpty()) {
        const QScopedPointer<QDir> dir(new QDir());
        a = dir->mkpath(m_path);
    }

    if (a)
        a = m_db.open();

    if (a && isEmpty())
        a = createDb();

    return a;
}

bool Database::createDb() const
{
    QSqlQuery q;

    bool a = q.exec("PRAGMA foreign_keys = ON");
    a &= q.exec("PRAGMA user_version = " + QString::number(m_kDbVersion));

    a &= q.exec("CREATE TABLE student "
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "first_name TEXT NOT NULL, "
                "last_name TEXT NOT NULL, "
                "pseudo TEXT NOT NULL, "
                "password INTEGER NOT NULL, "
                "avatar BLOB, "
                "vote INTEGER REFERENCES delegate (id) "
                "    DEFERRABLE INITIALLY DEFERRED)");
    a &= q.exec("CREATE UNIQUE INDEX full_name "
                "ON student (first_name, last_name)");
    a &= q.exec("CREATE TABLE delegate "
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "student_id INTEGER REFERENCES student (id), "
                "desc TEXT NOT NULL)");
    a &= q.exec("CREATE TABLE admin "
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "first_name TEXT, "
                "last_name TEXT, "
                "pseudo TEXT NOT NULL, "
                "password INTEGER NOT NULL, "
                "avatar BLOB)");

    a &= q.prepare("INSERT INTO admin (id, pseudo, password) "
                   "VALUES (0, 'root', ?)");
    q.bindValue(0, QCryptographicHash::hash("root", QCryptographicHash::Sha256));
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

bool Database::login(const QString& pseudo, const QString& password, UserType login) const
{
    QSqlQuery q;

    QString table = (login == Student) ? "student" : "admin";

    q.prepare("SELECT password FROM :table "
              "WHERE pseudo = :pseudo");
    q.bindValue(":table", table);
    q.bindValue(":pseudo", pseudo);
    q.exec();
    q.last();

    return QCryptographicHash::hash(password.toUtf8(),
                                    QCryptographicHash::Sha256)
           == q.value(0).toByteArray();
}

bool Database::vote(const uint8_t& id) const
{
    QSqlQuery q;

    q.prepare("INSERT OR IGNORE INTO student (vote) "
              "VALUES (?)");
    q.bindValue(0, id);

    return q.exec();
}

QSqlTableModel* Database::getModel(UserType table) const
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable((table == Student) ? "student" : "admin");

    return model;
}
