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


#include "MainWindow.hpp"
#include "gui/LoginWidget.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow())
    , m_loginWidget(new LoginWidget(this))
{
    m_ui->setupUi(this);

    setCentralWidget(m_loginWidget);
    setStatus(Login);
}

void MainWindow::setStatus(Status status)
{
    if (status == Login) {
        setWindowTitle(m_kTitle + tr("Log in"));
    }
}
