/***************************************************************************
                          knetswitch.cpp  -  description
                             -------------------
    begin                : Tue Sep 11 13:00:54 CEST 2001
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
#include <qlayout.h>


#include <klocale.h>
#include <kglobal.h>

#include "knetswitch.h"

#include <iostream.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qgroupbox.h>

// module stuff
#include "netswitchmodule.h"
#include "msocks.h"
#include "mbasicnetworking.h"

#include "modulelistboxitem.h"

#include <klineeditdlg.h>
#include <kstddirs.h>

KNetSwitch::KNetSwitch(QWidget *parent, const char *name):KCModule(parent,name)
{
  rcfile = locateLocal("appdata", "knetswitchrc");
  cout << rcfile << endl;

  // place widgets here
  this->setMinimumHeight(400);
  profileWidget = new ProfileWidget(this);

  NetswitchModule* m = new MSocks(profileWidget->GroupBox2);
  cout << "Adding Module " << m->getIdentifier() << endl;
  profileWidget->list_modules->insertItem(new ModuleListBoxItem( QPixmap("/home/olistrut/programmierung/c/knetswitch/knetswitch/knetswitch/lock.png"),m->getName(), m->getIdentifier()));
  modules.insert(m->getIdentifier(), m);

  m = new MBasicNetworking(profileWidget->GroupBox2);
  activeModule = m;

  cout << "Adding Module " << m->getIdentifier() << endl;
  m->getWidget()->hide();
  profileWidget->list_modules->insertItem(new ModuleListBoxItem( QPixmap("/opt/kde2/share/icons/hicolor/32x32/actions/connect_established.png"),m->getName(), m->getIdentifier()));
  modules.insert(m->getIdentifier(), m);

  load();

  currentProfileChanged = false;
  connect(profileWidget->combo_profileNames2, SIGNAL(activated(const QString&)), this, SLOT(profileEditActivated(const QString&)));
  connect(profileWidget->pb_saveCurrentProfile, SIGNAL(clicked()), this, SLOT(saveProfileClicked()));
  connect(profileWidget->pb_resetCurrentProfile, SIGNAL(clicked()), this, SLOT(resetProfileClicked()));
  connect(profileWidget->pb_newProfile, SIGNAL(clicked()), this, SLOT(newProfileClicked()));
  connect(profileWidget->list_modules, SIGNAL(selectionChanged()), this,  SLOT(switchModule()));

  cout << "init done " << endl;
/*  if (getuid() != 0) {
      QLayoutIterator it = layout->iterator();
      QLayoutItem *child;
      while ( (child = it.current() ) ) {
          //child->widget()->setEnabled(false);
          ++it;
      }
  }
*/

}

/*void KNetSwitch::processFinished(KProcess* dummy) {
  profileWidget->lbl_ip->setText("done");
} */

void KNetSwitch::textChanged(const QString& text) {
  currentProfileChanged = true;
}

void KNetSwitch::newProfileClicked() {
  // show dialog for creating new profile
  KLineEditDlg dlg("Profile Name", "", this);
  dlg.show();
  if (!dlg.text().stripWhiteSpace().isEmpty()) {
     profileWidget->combo_profileNames2->insertItem(dlg.text(), 0);
  }


  // add nodes to dom tree
  QDomElement e = dataStore->createElement("knetswitchprofile");
  e.setAttribute("name", dlg.text());
  root.appendChild(e);

  QDictIterator<NetswitchModule> it( modules );
  while ( it.current() ) {
      cout << "Adding new profile for module: " <<  it.current()->getIdentifier() << endl;

      QDomElement e2 = dataStore->createElement("modulesettings");
      e2.setAttribute("modulename", it.current()->getIdentifier());
      e.appendChild(e2);
      it.current()->init(e2);
      ++it;
  }

  cout << dataStore->toString();

  profileEditActivated(dlg.text());
}

void KNetSwitch::resetProfileClicked() {
  profileEditActivated(curProfileName);
  // TODO:
}

void KNetSwitch::saveProfileClicked() {
//  if (currentProfileChanged) {
      // better: disable button before first change and after save
      cout << "saving profile..." << endl;

      // iterate over profiles in dom tree to find the one that's currently edited
      QDomNodeList profiles = dataStore->elementsByTagName("knetswitchprofile");
      for (unsigned int i = 0; i < profiles.count(); i++) {
          QDomNode curProf = profiles.item(i);

          // get profile name
          QDomNamedNodeMap map = curProf.attributes();
          QDomNode name = map.namedItem("name");

          if (name.toAttr().value() != curProfileName) {
            cout << name.toAttr().value() << " => will continue " << endl;
            continue;
          }

          // remove old child nodes. all nodes will be regenerated
          // using the save methods of the modules.
          QDomNode n = curProf.firstChild();

          QDomNode result;
          while ( !n.isNull() ) {
              result = curProf.removeChild(n);
              cout << "removing child" << endl;
              if (!result.isNull()) { n = result; } else { cout << "Error: Element could not be deleted." << endl; }
              n = n.nextSibling();
          }

          // next, iterate over modules and integrate generated
          // dom structures into the main config file
          QDictIterator<NetswitchModule> it( modules );
          while ( it.current() ) {
              cout << "Saving data for module: " <<  it.current()->getIdentifier() << endl;
              QDomElement a = it.current()->save();
              curProf.appendChild(a);
              ++it;
          }

      }

      cout << dataStore->toString();

      QFile* outfile = new QFile(rcfile);
      cout << "Opening outfile" << endl;
      outfile->open(IO_WriteOnly);
      QTextStream outStream(outfile);
      outStream << dataStore->toString();
      outfile->close();
      currentProfileChanged = false;
//  }
}

void KNetSwitch::profileEditActivated(const QString& profileName) {
  profileWidget->combo_profileNames2->setEditable(false);

  cout << "new profile selected: " << profileName << endl;
  if (currentProfileChanged) {
    cout << "current profile has been changed. all changes will be lost." << endl;
  }
  curProfileName = profileName;
  // print out the element names of all elements that are a direct child
  // of the outermost element.
  QDomElement docElem = dataStore->documentElement();
  QDomNodeList profiles = dataStore->elementsByTagName("knetswitchprofile");
  // iterate over profiles in config file
  for (unsigned int i = 0; i < profiles.count(); i++) {
      cout << "Profile " << i << endl;
      QDomNode curProf = profiles.item(i);

      // get profile name
      QDomNamedNodeMap map = curProf.attributes();
      // will most certainly crash if there is no attribute "name" inside
      // the knetswitchprofile tag
      QDomNode name = map.namedItem("name");

      if (name.toAttr().value() != profileName) {
        cout << name.toAttr().value() << " => will continue " << endl;
        continue;
      }

      QDomNode m = curProf.firstChild();
      while( !m.isNull() ) {
          if ( m.isElement() ) {
              QDomElement e = m.toElement();
              map = e.attributes();
              cout << "Module: " << map.namedItem("modulename").toAttr().value() << endl;
              if (modules[map.namedItem("modulename").toAttr().value()]) {
                  modules[map.namedItem("modulename").toAttr().value()]->init(e);
              }
          }
          m = m.nextSibling();
      }


  }
}



KNetSwitch::~KNetSwitch() {
}


void KNetSwitch::load() {
  // Load config from file.
  dataStore = new QDomDocument("configfile");
  QFile f( rcfile );
  if (!f.open(IO_ReadOnly)) {
      cout << "Could not open config file. Using default (zero) configuration instead." << endl;
      dataStore->appendChild(dataStore->createElement("knetswitchprofiles"));
      root = dataStore->documentElement();
      return;
  }
  if (!dataStore->setContent(&f)) {
      cout << "Error reading input file. Using default (zero) configuration instead." << endl;
      f.close();
      dataStore->appendChild(dataStore->createElement("knetswitchprofiles"));
      root = dataStore->documentElement();
      return;
  }
  f.close();

  // print out the element names of all elements that are a direct child
  // of the outermost element.
  root = dataStore->documentElement();
  QDomNodeList profiles = dataStore->elementsByTagName("knetswitchprofile");
  // iterate over profiles in config file
  cout << "Number of profiles in config file: " << profiles.count() << endl;
  for (unsigned int i = 0; i < profiles.count(); i++) {
      cout << ">>Profile " << i << endl;
      QDomNode curProf = profiles.item(i);

      // get profile name
      QDomNamedNodeMap map = curProf.attributes();
      // will most certainly crash if there is no attribute "name" inside
      // the knetswitchprofile tag
      profileWidget->combo_profileNames2->insertItem(map.namedItem("name").toAttr().value());

      // make the first profile the active one
      if (i == 0) {
          profileEditActivated(map.namedItem("name").toAttr().value());
      }


  }
}


void KNetSwitch::switchModule() {
  cout << "adding new widget" << cout << profileWidget->list_modules->currentText() << endl;
  ModuleListBoxItem* item = dynamic_cast <ModuleListBoxItem*>(profileWidget->list_modules->item(profileWidget->list_modules->currentItem()));
  activeModule->getWidget()->hide();
  cout << "Identifier: " << dynamic_cast <ModuleListBoxItem*>(item)->getIdentifier();
  modules[dynamic_cast <ModuleListBoxItem*>(item)->getIdentifier()]->getWidget()->show();
}

void KNetSwitch::defaults() {
  // insert your default settings code here...
	emit changed(true);
}

void KNetSwitch::save() {
  // changed profiles are stored only if the user clicks the save button in the
  // "edit profiles" tab.
  // selecting apply or ok will only change the network configuration

  // iterate over modules
  QDictIterator<NetswitchModule> it( modules );
  while ( it.current() ) {
      cout << "Applying data for module: " <<  it.current()->getIdentifier() << endl;
      if (it.current()->run()) { cout << "ok" << endl; }
      ++it;
  }


  emit changed(true);
}

int KNetSwitch::buttons () {
        return KCModule::Apply|KCModule::Help;
}

void KNetSwitch::configChanged() {
        // insert your saving code here...
        emit changed(true);
}

QString KNetSwitch::quickHelp() const
{
         return i18n("1st Helpful information about the knetswitch module.");
}

// ------------------------------------------------------------------------

extern "C"
{

        KCModule *create_knetswitch(QWidget *parent, const char *name)
        {
                KGlobal::locale()->insertCatalogue("knetswitch");
                return new KNetSwitch(parent, name);
        }
}

#include "knetswitch.moc"
