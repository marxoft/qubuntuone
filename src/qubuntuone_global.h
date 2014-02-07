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

#ifndef QUBUNTUONE_GLOBAL_H
#define QUBUNTUONE_GLOBAL_H

#include <qglobal.h>

#if defined(QUBUNTUONE_LIBRARY)
#  define QUBUNTUONESHARED_EXPORT Q_DECL_EXPORT
#elif defined(QUBUNTUONE_STATIC_LIBRARY)
# define QUBUNTUONESHARED_EXPORT
#else
#  define QUBUNTUONESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QUBUNTUONE_GLOBAL_H
