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
#include <iostream.h>

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
  return "KNetSwitchModule::MBasicNetworking";
}

QString MBasicNetworking::getName() {
  return "Basic Networking";
}


QWidget* MBasicNetworking::getWidget() {
  return widget;
}

void MBasicNetworking::init(QDomElement config) {
    cout << "Initializing Module " << getIdentifier() << endl;
    reset(config);
}

QDomElement MBasicNetworking::save() {
  // just write the content of our widgets to dom tree

  cout << "setting dom elements" << endl;
  root->namedItem("ipconfig").attributes().namedItem("hostip").toAttr().setValue(widget->le_hostip->text());
  root->namedItem("ipconfig").attributes().namedItem("netmask").toAttr().setValue(widget->le_netmask->text());
  root->namedItem("ipconfig").attributes().namedItem("gateway").toAttr().setValue(widget->le_gateway->text());
  root->namedItem("device").attributes().namedItem("devicename").toAttr().setValue(widget->le_deviceName->text());
  root->namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().setValue(widget->le_dnsip->text());

  return *root;
}

void MBasicNetworking::reset(QDomElement config) {
  cout << "Resetting Basic Networking Module: Loading configuration." << endl;

  cout << ">>" << config.text();
  root = new QDomElement(config);
  // if any of the following nodes/attributes does not exist, create them so
  // that we have a complete dom tree when we save the current items
  // later on.

  // get tcp/ip information
  hostip = config.namedItem("ipconfig").attributes().namedItem("hostip").toAttr().value();
  netmask = config.namedItem("ipconfig").attributes().namedItem("netmask").toAttr().value();
  gateway = config.namedItem("ipconfig").attributes().namedItem("gateway").toAttr().value();
  dnsip = config.namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().value();
  // get device name
  device = config.namedItem("device").attributes().namedItem("devicename").toAttr().value();

  widget->le_hostip->setText(hostip);
  widget->le_netmask->setText(netmask);
  widget->le_gateway->setText(gateway);
  widget->le_dnsip->setText(dnsip);
  widget->le_deviceName->setText(device);

}

bool MBasicNetworking::run() {}

