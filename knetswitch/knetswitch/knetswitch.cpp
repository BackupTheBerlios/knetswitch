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
#include <qtextstream.h>
#include <qgroupbox.h>

// module stuff
#include "netswitchmodule.h"
#include "msocks.h"
#include "mbasicnetworking.h"

#include "modulelistboxitem.h"

#include <ktempfile.h>
#include <klineeditdlg.h>

KNetSwitch::KNetSwitch(QWidget *parent, const char *name):KCModule(parent,name)
{
  rcfile = "/home/olistrut/.knetswitchrc";
  // place widgets here
  this->setMinimumHeight(400);
  profileWidget = new ProfileWidget(this);

  NetswitchModule* m = new MSocks(profileWidget->GroupBox2);
  cout << "Adding Module " << m->getIdentifier() << endl;
  profileWidget->list_modules->insertItem(new ModuleListBoxItem( QPixmap("/opt/kde2/share/icons/hicolor/64x64/mimetypes/video.png"),m->getName(), m->getIdentifier()));
  modules.insert(m->getIdentifier(), m);

  m = new MBasicNetworking(profileWidget->GroupBox2);
  activeModule = m;

  cout << "Adding Module " << m->getIdentifier() << endl;
  m->getWidget()->hide();
  profileWidget->list_modules->insertItem(new ModuleListBoxItem( QPixmap("/opt/kde2/share/icons/hicolor/64x64/mimetypes/video.png"),m->getName(), m->getIdentifier()));
  modules.insert(m->getIdentifier(), m);




  load();

  currentProfileChanged = false;
  connect(profileWidget->combo_profileNames1, SIGNAL(activated(const QString&)), this, SLOT(profileViewActivated(const QString&)));
  connect(profileWidget->combo_profileNames2, SIGNAL(activated(const QString&)), this, SLOT(profileEditActivated(const QString&)));
/*  connect(profileWidget->le_hostip, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
  connect(profileWidget->le_dnsip, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
  connect(profileWidget->le_netmask, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
  connect(profileWidget->le_gateway, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
*/
  connect(profileWidget->pb_saveCurrentProfile, SIGNAL(clicked()), this, SLOT(saveProfileClicked()));
  connect(profileWidget->pb_resetCurrentProfile, SIGNAL(clicked()), this, SLOT(resetProfileClicked()));
  connect(profileWidget->pb_newProfile, SIGNAL(clicked()), this, SLOT(newProfileClicked()));
  connect(profileWidget->list_modules, SIGNAL(selectionChanged( QListBoxItem * )), this, SLOT(switchModule( QListBoxItem *  )));

/*  cout << "init done " << endl;
  if (getuid() != 0) {
      QLayoutIterator it = layout->iterator();
      QLayoutItem *child;
      while ( (child = it.current() ) ) {
          //child->widget()->setEnabled(false);
          ++it;
      }
  }
*/
//  QLayout* layout = this->layout();

//  _layout->add(test->getWidget());
}

void KNetSwitch::processFinished(KProcess* dummy) {
  profileWidget->lbl_ip->setText("done");
}

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
  QDomElement e2, e3;
  e2 = dataStore->createElement("device");
  e2.setAttribute("devicename", "eth0");
  e.appendChild(e2);
  e2 = dataStore->createElement("ipconfig");
  e.appendChild(e2);
  e2.setAttribute("netmask", "0.0.0.0");
  e2.setAttribute("hostip", "0.0.0.0");
  e2.setAttribute("gateway", "0.0.0.0");
  e2 = dataStore->createElement("dnsconfig");
  e.appendChild(e2);
  e3 = dataStore->createElement("dns");
  e3.setAttribute("dnsip", "0.0.0.0");
  e2.appendChild(e3);
  // add nodns entries somehow
  profileWidget->combo_profileNames1->insertItem(dlg.text(), 0);
  profileEditActivated(dlg.text());
  cout << " === Dump === " << endl;
  cout << dataStore->toString();
}

void KNetSwitch::resetProfileClicked() {
  profileEditActivated(curProfileName);
}

void KNetSwitch::saveProfileClicked() {
  // better: disable button before first change and after save
  if (currentProfileChanged) {
      cout << "saving profile..." << endl;
      // iterate over lineedit widgets and write to dom tree
      QDomNodeList profiles = dataStore->elementsByTagName("knetswitchprofile");
      // iterate over profiles in dom tree to find the one that's currently edited
      for (unsigned int i = 0; i < profiles.count(); i++) {
          QDomNode curProf = profiles.item(i);

          // get profile name
          QDomNamedNodeMap map = curProf.attributes();
          QDomNode name = map.namedItem("name");

          if (name.toAttr().value() != curProfileName) {
            cout << name.toAttr().value() << " => will continue " << endl;
            continue;
          }

          // set device name
          // QString deviceName = curProf.namedItem("device").attributes().namedItem("devicename").toAttr().value();
          // set tcp/ip information
          cout << "creating dom elements" << endl;
/*          curProf.namedItem("ipconfig").attributes().namedItem("hostip").toAttr().setValue(profileWidget->le_hostip->text());
          curProf.namedItem("ipconfig").attributes().namedItem("netmask").toAttr().setValue(profileWidget->le_netmask->text());
          curProf.namedItem("ipconfig").attributes().namedItem("gateway").toAttr().setValue(profileWidget->le_gateway->text());
          curProf.namedItem("device").attributes().namedItem("devicename").toAttr().setValue(profileWidget->le_deviceName->text());
          curProf.namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().setValue(profileWidget->le_dnsip->text());
*/
      }
      QFile* outfile = new QFile(rcfile);
      outfile->open(IO_WriteOnly);
      QTextStream outStream(outfile);
      outStream << dataStore->toString();
      outfile->close();
      currentProfileChanged = false;
  }
}

void KNetSwitch::profileViewActivated(const QString& profileName) {

  cout << "new profile selected: " << profileName << endl;

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
/*      // get device name
      QString deviceName = curProf.namedItem("device").attributes().namedItem("devicename").toAttr().value();
      // get tcp/ip information
      QString hostip = curProf.namedItem("ipconfig").attributes().namedItem("hostip").toAttr().value();
      QString netmask = curProf.namedItem("ipconfig").attributes().namedItem("netmask").toAttr().value();
      QString gateway = curProf.namedItem("ipconfig").attributes().namedItem("gateway").toAttr().value();
      QString dnsip = curProf.namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().value();

      profileWidget->lbl_ip->setText(hostip);
      profileWidget->lbl_netmask->setText(netmask);
      profileWidget->lbl_gateway->setText(gateway);
      profileWidget->lbl_dns->setText(dnsip);
      profileWidget->lbl_deviceName->setText(deviceName);
*/
  }



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
      // get device name
      QString deviceName = curProf.namedItem("device").attributes().namedItem("devicename").toAttr().value();
      // get tcp/ip information
      QString hostip = curProf.namedItem("ipconfig").attributes().namedItem("hostip").toAttr().value();
      QString netmask = curProf.namedItem("ipconfig").attributes().namedItem("netmask").toAttr().value();
      QString gateway = curProf.namedItem("ipconfig").attributes().namedItem("gateway").toAttr().value();
      QString dnsip = curProf.namedItem("dnsconfig").namedItem("dns").attributes().namedItem("dnsip").toAttr().value();

      /*profileWidget->le_hostip->setText(hostip);
      profileWidget->le_netmask->setText(netmask);
      profileWidget->le_gateway->setText(gateway);
      profileWidget->le_dnsip->setText(dnsip);*/

  }
}



KNetSwitch::~KNetSwitch() {
}


void KNetSwitch::load() {
  // Load config from file.
//switchModule();
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
  for (unsigned int i = 0; i < profiles.count(); i++) {
      cout << "Profile " << i << endl;
      QDomNode curProf = profiles.item(i);

      // get profile name
      QDomNamedNodeMap map = curProf.attributes();
      // will most certainly crash if there is no attribute "name" inside
      // the knetswitchprofile tag
      profileWidget->combo_profileNames1->insertItem(map.namedItem("name").toAttr().value());
      profileWidget->combo_profileNames2->insertItem(map.namedItem("name").toAttr().value());

      if (i == 0) { profileViewActivated(map.namedItem("name").toAttr().value()); }

  }
}


void KNetSwitch::switchModule(QListBoxItem* item) {
  cout << "adding new widget" << cout << profileWidget->list_modules->currentText() << endl;

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

  QString commandLine;
  commandLine = QString("ifconfig ") + QString("eth0 ") + profileWidget->lbl_ip->text() + QString(" netmask ") + profileWidget->lbl_netmask->text();
  cout << commandLine << endl;

  KTempFile script(QString::null, QString::null, 0700 );
  if (script.status()) {
      cout << "Error: Could not create temporary script file." << endl;
      return;
  }

  script.setAutoDelete(true);
  QTextStream outfile(script.file());
  outfile <<  QString("/sbin/route del default;") << endl;
  //outfile << QString("/sbin/route add default gw ") << profileWidget->lbl_gateway->text() << ">> /tmp/test.log;" << endl;
  outfile << QString("/sbin/route add default gw ") << profileWidget->lbl_gateway->text() << ">> /tmp/test.log;" << endl;
  outfile << QString("/sbin/ifconfig ") << profileWidget->lbl_deviceName->text() << " " << profileWidget->lbl_ip->text() << " netmask " << profileWidget->lbl_netmask->text() << ";" << endl;
  script.close();

  KProcess proc;
  proc << script.name();

  connect(&proc, SIGNAL(processExited(KProcess *)), this, SLOT(processFinished(KProcess *)));
  proc.start( KProcess::Block );

  // write dns server to /etc/resolv.conf
  QFile* resolvfile = new QFile("/etc/resolv.conf");
  resolvfile->open(IO_WriteOnly);
  QTextStream outStream(resolvfile);
  outStream << "search local" << endl;
  outStream << "nameserver " << profileWidget->lbl_dns->text() << endl;
  resolvfile->close();

  currentProfileChanged = false;

  // TODO: Insert sanity and security checks!!! ifconfig needs to be run as root.

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
