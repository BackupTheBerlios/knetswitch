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

void MBasicNetworking::textChanged(const QString&) {
}


QDomElement MBasicNetworking::save() {
  // just write the content of our widgets to dom tree

  currentProfileChanged = true;
  cout << "Profile changed ... " << endl;
  hostip = widget->le_hostip->text();
  netmask = widget->le_netmask->text();
  gateway = widget->le_gateway->text();
  dnsip = widget->le_dnsip->text();
  device = widget->le_deviceName->text();

  if (currentProfileChanged) {
      cout << "setting dom elements" << endl;
      root->namedItem("ipconfig").attributes().namedItem("hostip").toAttr().setValue(hostip);
      root->namedItem("ipconfig").attributes().namedItem("netmask").toAttr().setValue(netmask);
      root->namedItem("ipconfig").attributes().namedItem("gateway").toAttr().setValue(gateway);
      root->namedItem("device").attributes().namedItem("devicename").toAttr().setValue(device);
      root->namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().setValue(dnsip);
  }
  return *root;
}

void MBasicNetworking::reset(QDomElement config) {
  cout << "Resetting Basic Networking Module: Loading configuration." << endl;
  currentProfileChanged = false;

  // if any of the following nodes/attributes does not exist, create them so
  // that we have a complete dom tree when we save the current items
  // later on.
  QDomElement e, e2;
  if (config.namedItem("ipconfig").isNull()) {
      e = config.ownerDocument().createElement("ipconfig");
      e.setAttribute("hostip", "");
      e.setAttribute("netmask", "");
      e.setAttribute("gateway", "");
      config.appendChild(e);
  }
  if (config.namedItem("device").isNull()) {
      e = config.ownerDocument().createElement("device");
      e.setAttribute("devicename", "");
      config.appendChild(e);
  }
  if (config.namedItem("dnsconfig").isNull()) {
      e = config.ownerDocument().createElement("dnsconfig");
      QDomElement e2 = config.ownerDocument().createElement("dns");
      e2.setAttribute("dnsip", "");
      config.appendChild(e);
      e.appendChild(e2);
  }

  root = new QDomElement(config);
//  root->appendChild(e);

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

bool MBasicNetworking::run() {

  currentProfileChanged = true;
  cout << "Profile changed ... " << endl;
  hostip = widget->le_hostip->text();
  netmask = widget->le_netmask->text();
  gateway = widget->le_gateway->text();
  dnsip = widget->le_dnsip->text();
  device = widget->le_deviceName->text();


  QString commandLine;
  commandLine = QString("ifconfig ") + QString("eth0 ") + dnsip + QString(" netmask ") + netmask;
  cout << commandLine << endl;

  KTempFile script(QString::null, QString::null, 0700 );
  if (script.status()) {
      cout << "Error: Could not create temporary script file." << endl;
      return false;
  }

  //script.setAutoDelete(true);
  QTextStream outfile(script.file());
  outfile <<  QString("/sbin/route del default;") << endl;
  outfile << QString("/sbin/route add default gw ") << gateway << ">& /tmp/test.log;" << endl;
  outfile << QString("/sbin/ifconfig ") << device << " " << hostip << " netmask " << netmask << ";" << endl;
  script.close();

  KProcess proc;
  proc << script.name();

//  connect(&proc, SIGNAL(processExited(KProcess *)), this, SLOT(processFinished(KProcess *)));
  proc.start( KProcess::Block );

  // write dns server to /etc/resolv.conf
  QFile* resolvfile = new QFile("/etc/resolv.conf");
  resolvfile->open(IO_WriteOnly);
  QTextStream outStream(resolvfile);
  outStream << "search local" << endl;
  outStream << "nameserver " << dnsip << endl;
  resolvfile->close();

  currentProfileChanged = false;

  // TODO: Insert sanity and security checks!!! ifconfig needs to be run as root.
}

#include "mbasicnetworking.moc"
