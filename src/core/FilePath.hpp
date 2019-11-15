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


#ifndef FILEPATH_HPP
#define FILEPATH_HPP

#include <QIcon>
#include <QHash>

class FilePath
{
    Q_DISABLE_COPY(FilePath)

public:
    FilePath();

    QIcon onOffIcon(const QString& name);
    QString getUserDataPath() const;
private:
    QString m_userDataPath;
    QHash<QString, QIcon> m_iconCache;
};

inline QString FilePath::getUserDataPath() const
{
    return m_userDataPath;
}

#endif // FILEPATH_HPP
