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


#include "LoginWidget.hpp"
#include "core/FilePath.hpp"

#include <QAction>

LoginWidget::LoginWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::LoginWidget())
    , m_error(false)
{
    m_ui->setupUi(this);

    const QScopedPointer<FilePath> f(new FilePath());
    m_ui->tooglePasswordButton->setIcon(f->onOffIcon("password-show"));

    connect(m_ui->lineEditUsername, &QLineEdit::textEdited,
            this, &LoginWidget::setReadyToLogin);
    connect(m_ui->lineEditPassword, &QLineEdit::textEdited,
            this, &LoginWidget::setReadyToLogin);

    connect(m_ui->tooglePasswordButton, &QToolButton::clicked,
            this, &LoginWidget::tooglePassword);

    connect(m_ui->loginButton, &QPushButton::pressed,
            this, &LoginWidget::tryToLogin);
}

void LoginWidget::setError(bool status)
{
    QPalette palette;

    if (status)
        palette.setColor(QPalette::Text, Qt::red);

    m_ui->lineEditUsername->setPalette(palette);
    m_ui->lineEditPassword->setPalette(palette);
    m_ui->loginButton->setDisabled(status);
}

void LoginWidget::setReadyToLogin()
{
    if (!m_error)
        setError(false);

    bool a = m_ui->lineEditUsername->text().count() >= m_kMinimumSize;
    a &= m_ui->lineEditPassword->text().count() >= m_kMinimumSize;

    m_ui->loginButton->setEnabled(a);
}

void LoginWidget::tooglePassword(bool checked)
{
    m_ui->lineEditPassword->setEchoMode(checked
                                        ? QLineEdit::Normal
                                        : QLineEdit::Password);
}

Database::UserType LoginWidget::getUserType() const
{
    return m_ui->studentLoginRadio->isChecked()
           ? Database::Student : Database::Admin;
}

void LoginWidget::tryToLogin()
{
    Database db;

    bool a = db.login(m_ui->lineEditUsername->text(),
                      m_ui->lineEditPassword->text(),
                      getUserType());

    if (a) {
        // TODO: login success
    } else if (!m_error) {
        setError(true);
    }
}
