/***************************************************************************
 *   This file is part of the nQTrucks project                             *
 *   Copyright (C) 2015 by Efraím Pérez                                    *
 *   newsages2014@gmail.com                                                *
 *                                                                         *
 **                   GNU General Public License Usage                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 **                  GNU Lesser General Public License                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library.                                      *
 *   If not, see <http://www.gnu.org/licenses/>.                           *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ****************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
#include "qglobal.h"
#include <stdexcept>
#include <QString>

#if defined(NQTRUCKS_EXPORTS)
#  define NQTRUCKS_EXPORT Q_DECL_EXPORT
#elif defined (NQTRUCKS_IMPORTS)
#  define NQTRUCKS_EXPORT Q_DECL_IMPORT
#else
#  define NQTRUCKS_EXPORT   /**/
#endif

namespace nQTrucks {

namespace Const{

}
    QString extractClassName(QString className);
    //enum RenderPass {FirstPass, SecondPass};
    //enum ArrangeType {AsNeeded, Force};
    class nQTrucksError : public std::runtime_error{
    public:
        nQTrucksError(const QString& message):std::runtime_error(message.toStdString()){}
    };

} // namespace nQTrucks

#endif // GLOBAL_H