/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef URLS_H
#define URLS_H

#include <QString>

const QString AUTH_URL("https://login.ubuntu.com/api/v2/tokens/oauth");
const QString BASE_URL("https://one.ubuntu.com/api/v1");
const QString BASE_URL_ACCOUNT("https://one.ubuntu.com/api/account/");
const QString BASE_URL_QUOTA("https://one.ubuntu.com/api/quota/");
const QString BASE_URL_FILES("https://one.ubuntu.com/api/file_storage/v1");
const QString CONTENT_ROOT_FILES("https://files.one.ubuntu.com");
const QString BASE_URL_MUSIC("https://one.ubuntu.com/api/music/v2");
const QString BASE_URL_MOBILE_LOGIN("http://one.ubuntu.com/phones/creds");

#endif // URLS_H
