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
  connect(widget->pb_newSocksRoute, SIGNAL(clicked()), this, SLOT(createNewRoute()));
  connect(widget->combo_Routes, SIGNAL(activated(const QString&)), this, SLOT(routeActivated(const QString&)));

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
  // just write the content of our widgets to dom tree

  currentProfileChanged = true;
  cout << "Profile changed ... " << endl;

  if (currentProfileChanged) {
      cout << "setting dom elements" << endl;
      // remove old child nodes. all nodes will be regenerated
      // using the save methods of the modules.
      QDomNode n = root->namedItem("routes").firstChild();
      QDomNode result;
      while ( !n.isNull() ) {
          result = root->removeChild(n);
          cout << "removing child" << endl;
          if (!result.isNull()) { n = result; } else { cout << "Error: Element could not be deleted." << endl; }
          n = n.nextSibling();
      }

      // iterate over routes and create appropriate xml elements
      QDomElement e;


      QDictIterator<SocksRoute> it(routes);
      while(it.current()) {
         SocksRoute *route = it.current();
         e = root->ownerDocument().createElement("SocksRoute");
         e.setAttribute("name", it.currentKey());
         e.setAttribute("from", route->from);
         e.setAttribute("to", route->to);
         e.setAttribute("via", route->via);
         e.setAttribute("protocol", route->proto);
         e.setAttribute("proxyprotocol", route->proxyproto);
         e.setAttribute("method", route->method);
         root->namedItem("routes").appendChild(e);
         ++it;
      }
  }
  return *root;

}

void MSocks::routeActivated(const QString& route) {
  cout << "Current route: " << route << endl;
  routes[currentRoute]->from = widget->le_from->text();

  currentRoute = route;
}

void MSocks::reset(QDomElement config) {

  cout << "Resetting Socks Module: Loading configuration." << endl;

  currentProfileChanged = false;

  routes.setAutoDelete(true);
  routes.clear();

  root = new QDomElement(config);

  // if any of the following nodes/attributes does not exist, create them so
  // that we have a complete dom tree when we save the current items
  // later on. nodes for individual routes will be added as required when saving.
  QDomElement e;
  if (config.namedItem("routes").isNull()) {
      cout << "Creating \"routes\" element..." << endl;
      e = config.ownerDocument().createElement("routes");
      config.appendChild(e);
  } else { cout << "routes exists" << endl; }
}

bool MSocks::run() {}

