/***************************************************************************
                          mbasicnetworking.cpp  -  description
                             -------------------
    begin                : Sun Oct 7 2001
    copyright            : (C) 2001 by Oliver Strutynski
    email                : olistrut@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mbasicnetworking.h"
#include "ipvalidator.h"
#include <qlineedit.h>

MBasicNetworking::MBasicNetworking(QWidget* parent) : NetswitchModule(parent) {
  widget = new Widget_BasicNetworking(parent);

  IPValidator* val1 = new IPValidator(widget);
  widget->le_hostip->setValidator(val1);
  widget->le_gateway->setValidator(val1);
  widget->le_netmask->setValidator(val1);
  widget->le_dnsip->setValidator(val1);

}
MBasicNetworking::~MBasicNetworking() {
}

QString MBasicNetworking::getIdentifier() {
  return "KNetSwitchModule::MBasicNetworking::0.1";
}

QString MBasicNetworking::getName() {
  return "Basic Networking";
}


QWidget* MBasicNetworking::getWidget() {
  return widget;
}

void MBasicNetworking::init(QDomElement config) {}
QDomElement MBasicNetworking::save() {}
void MBasicNetworking::reset(QDomElement config) {}
bool MBasicNetworking::run() {}

