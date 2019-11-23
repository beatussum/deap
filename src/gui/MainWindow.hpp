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


#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"

class LoginWidget;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    inline static const QString m_kTitle = "DEAP - ";
    enum Status { Login };
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private:
    void setStatus(Status);
private:
    Ui::MainWindow *const m_ui;
    LoginWidget* m_loginWidget;
};

inline MainWindow::~MainWindow()
{
    delete m_ui;
}

#endif // MAINWINDOW_HPP
