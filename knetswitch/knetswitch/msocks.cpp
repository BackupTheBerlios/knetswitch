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

#include <iostream.h>
#include <klineeditdlg.h>
#include <qcombobox.h>


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

void MSocks::init(QDomElement config) {
  reset(config);
}

void MSocks::createNewRoute() {
  KLineEditDlg dlg("Socks Route Name", "", widget);
  dlg.show();
  if (!dlg.text().stripWhiteSpace().isEmpty()) {
     widget->combo_Routes->insertItem(dlg.text(), 0);
  }

  SocksRoute* route = new SocksRoute(dlg.text());
  routes.insert(dlg.text(),route);
}

QDomElement MSocks::save() {

return *root;

}

void MSocks::reset(QDomElement config) {

  cout << "Resetting Socks Module: Loading configuration." << endl;

  currentProfileChanged = false;

  routes.setAutoDelete(true);
  routes.clear();

  root = new QDomElement(config);

  // get tcp/ip information
/*  hostip = config.namedItem("ipconfig").attributes().namedItem("hostip").toAttr().value();
  netmask = config.namedItem("ipconfig").attributes().namedItem("netmask").toAttr().value();
  gateway = config.namedItem("ipconfig").attributes().namedItem("gateway").toAttr().value();
  dnsip = config.namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().value();*/
  // get device name
//  device = config.namedItem("device").attributes().namedItem("devicename").toAttr().value();




}

bool MSocks::run() {}

