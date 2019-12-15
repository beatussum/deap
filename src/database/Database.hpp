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


#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QtSql/QSqlDatabase>

struct User;

class Database final
{
    Q_DISABLE_COPY(Database)

public:
    inline static const QString m_kDbName = "deap.db";
    static constexpr uint8_t m_kDbVersion = {1};
public:
    Database();
    bool init();

    uint8_t getDbVersion() const;
    bool isEmpty() const;

    User* login(const QString& pseudo,
                const QString& password) const;
    bool vote(const User& voter, const User& candidate) const;
private:
    bool createDb() const;
private:
    QSqlDatabase m_db;
};

inline bool Database::isEmpty() const {
    return getDbVersion() == 0;
}

#endif // DATABASE_HPP
