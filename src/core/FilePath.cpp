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


#include "core/FilePath.hpp"
#include "config-deap.hpp"

#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtGui/QIcon>

QCache<QString, QIcon> FilePath::m_iconCache(5);

FilePath::FilePath()
#ifndef BUILD_TYPE_DEBUG
    : m_userDataPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/")
#endif
{
    if (!m_userDataPath.isEmpty()) {
        const QDir dir;
        dir.mkpath(m_userDataPath);
    }
}

QIcon FilePath::onOffIcon(const QString& name)
{
    QIcon* icon = m_iconCache.object(name);

    if (icon == nullptr) {
        icon = new QIcon();

        const QList<uint8_t> sizes = {16, 22, 24, 32};
        for (const uint8_t i : sizes) {
            icon->addPixmap(QIcon::fromTheme(name + "-off").pixmap(i));
            icon->addPixmap(QIcon::fromTheme(name + "-on").pixmap(i),
                           QIcon::Normal, QIcon::On);
        }

        m_iconCache.insert(name, icon);
    }

    return *icon;
}
