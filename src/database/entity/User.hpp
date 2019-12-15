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


#ifndef USER_HPP
#define USER_HPP

#include <QtGui/QPixmap>

struct User final
{
    Q_DISABLE_COPY(User)

public:
    enum StatusFlag { Admin = 1, Candidate = 2 };
    Q_DECLARE_FLAGS(Status, StatusFlag)
public:
    User(const uint16_t& id) : id(id) {}
    ~User();
public:
    const uint16_t id;
    QString firstName;
    QString lastName;
    QString pseudo;
    QPixmap* avatar;
    const User* vote;
    QString desc;
    Status status;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(User::Status)

inline User::~User() {
    if (avatar != nullptr)
        delete avatar;

    if (vote != nullptr)
        delete vote;
}

#endif // USER_HPP
