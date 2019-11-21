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


#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include "ui_LoginWidget.h"
#include "database/Database.hpp"

class LoginWidget final : public QWidget
{
    Q_OBJECT

public:
    static constexpr uint8_t m_kMinimumSize = {5};
public:
    explicit LoginWidget(QWidget* parent = nullptr);
    ~LoginWidget();

    Database::UserType getUserType() const;
private:
    void setError(bool status);
private slots:
    void setReadyToLogin();
    void tooglePassword(bool checked = false);
    void tryToLogin();
private:
    Ui::LoginWidget *const m_ui;
    bool m_error;
};

inline LoginWidget::~LoginWidget()
{
    delete m_ui;
}

#endif // LOGINWIDGET_HPP
