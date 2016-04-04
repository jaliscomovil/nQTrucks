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

#include "CamaraIP.h"
#include <QNetworkRequest>
#include <QLoggingCategory>

namespace nQTrucks{
namespace Devices {

CamaraIP::CamaraIP(int nDevice, QSettings *_appsettings, QObject *parent)
    : QObject(parent)
    , m_nDevice(nDevice)
    , m_settings(_appsettings)
    , m_netmanager(new QNetworkAccessManager(this))
{
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

    fotoCamaraError = QImage(1280,720, QImage::Format_RGB32);
    fotoCamaraError.fill(Qt::red);
    fotoCamaraError.text("ERROR DE CONEXION");

    m_settings = _appsettings;
    switch (nDevice) {
    case 1:
        m_configroot = (QString(CAMARA1));
        break;
    case 2:
        m_configroot = (QString(CAMARA2));
        break;
    default:
        m_configroot = (QString(CAMARA1));
        break;
    }

    loadconfig();
    connect(m_netmanager, SIGNAL(finished(QNetworkReply*)), this , SLOT(camaraNetworkReplyFinished(QNetworkReply*)));
}

void CamaraIP::loadconfig()
{

    m_settings->beginGroup(m_configroot);
    setTipoCamara(static_cast<CameraType>(m_settings->value("tipo",0).toInt()));
    setCamaraHost(m_settings->value("host","10.42.0.251").toString());
    setCamaraPort(m_settings->value("port","80").toString());
    setCamaraUser(m_settings->value("user","nqtrucks").toString());
    setCamaraPass(m_settings->value("pass","nqtrucks2016").toString());
    m_settings->endGroup();
}

void CamaraIP::setTipoCamara(const CameraType &_TipoCamara)
{
    if (m_TipoCamara != static_cast<CameraType>(_TipoCamara)) {
        m_TipoCamara  = static_cast<CameraType>(_TipoCamara);
        m_settings->setValue("tipo",QString::number(_TipoCamara));
        emit TipoCamaraChanged();
    }
}

void CamaraIP::setCamaraHost(const QString &_CamaraHost)
{
    if (m_CamaraHost != _CamaraHost) {
        m_CamaraHost = _CamaraHost;
        m_settings->setValue("host",_CamaraHost);
        emit CamaraHostChanged();
    }
}

void CamaraIP::setCamaraPort(const QString &_CamaraPort)
{
    if (m_CamaraPort != _CamaraPort)
    {
        m_CamaraPort = _CamaraPort;
        m_settings->setValue("port",_CamaraPort);
        emit CamaraPortChanged();
    }
}

void CamaraIP::setCamaraUser(const QString &_CamaraUser)
{
    if (m_CamaraUser != _CamaraUser)
    {
        m_CamaraUser = _CamaraUser;
        m_settings->setValue("user",_CamaraUser);
        emit CamaraUserChanged();
    }
}

void CamaraIP::setCamaraPass(const QString &_CamaraPass)
{
    if (m_CamaraPass != _CamaraPass)
    {
        m_CamaraPass = _CamaraPass;
        m_settings->setValue("pass",_CamaraPass);
        emit CamaraPassChanged();
    }
}


QUrl CamaraIP::setCamaraURL()
{
    loadconfig();
    QUrl curl("http://");
    curl.setHost(CamaraHost());
    curl.setPort(CamaraPort().toInt());
    curl.setUserName(CamaraUser());
    curl.setPassword(CamaraPass());

    emit CamaraIPWeb(curl.toString());

    switch (m_TipoCamara) {
    case CameraType::HIKVISION :
        curl.setPath("/Streaming/channels/101/picture");
        break;
    case CameraType::CAMTRONIC:
        /** TODO Implemetar mas tipos **/
        break;
    default:
        break;
    }
    return curl;
}

void CamaraIP::sendCamaraIPFotoRequest()
{
    /**  Peticion ***/
    QUrl Servidor = setCamaraURL();
    QNetworkRequest request(Servidor);


    /** TODO Stuff SSL (por probar) **/
    //QSslConfiguration config = request.sslConfiguration();
    //config.setPeerVerifyMode(QSslSocket::VerifyNone);
    //QSsl::TlsV1SslV3;
    //config.setProtocol(QSsl::TlsV1SslV3);
    //request.setSslConfiguration(config);

    m_netmanager->get(request);
}

void CamaraIP::camaraNetworkReplyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QImage fotoCamara;
    if (fotoCamara.loadFromData(data)){
        emit ReplyCamaraIPFoto(fotoCamara);
    }else{
        emit ReplyCamaraIPFoto(fotoCamaraError);
    }
    reply->deleteLater();
}


} /** END NAMESPACE Devices  **/

} /** END NAMESPACE nQTrucks **/
