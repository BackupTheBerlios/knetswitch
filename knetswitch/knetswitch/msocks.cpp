/***************************************************************************
                          msocks.cpp  -  description
                             -------------------
    begin                : Fri Oct 5 2001
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

#include "msocks.h"

MSocks::MSocks(QWidget* parent) : NetswitchModule(parent) {
  widget = new widget_dantesocks(parent);
}
MSocks::~MSocks() {
}

QString MSocks::getIdentifier() {
  return "KNetSwitchModule::MSocks";
}

QString MSocks::getName() {
  return "Socks";
}


QWidget* MSocks::getWidget() {
  return widget;
}

void MSocks::init(QDomElement config) {}

QDomElement MSocks::save() { QDomElement x; return x; }

void MSocks::reset(QDomElement config) {}

bool MSocks::run() {}

