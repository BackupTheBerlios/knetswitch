/***************************************************************************
                          knetswitch.h  -  description
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
#ifndef KNETSWITCH_H_
#define KNETSWITCH_H_

#include <kcmodule.h>
#include <kaboutdata.h>
#include <profilewidget.h>
#include <ipvalidator.h>
#include <netswitchmodule.h>

// qt xml includes
#include <qdom.h>

#include <qfile.h>
#include <qlistbox.h>
#include <qdict.h>

#include <kprocess.h>

class KNetSwitch: public KCModule
{
   Q_OBJECT
   public:
      KNetSwitch(QWidget *parent = 0L, const char *name = 0L);
      virtual ~KNetSwitch();

      void load();
      void save();
      void defaults();
      int buttons();
      QString quickHelp() const;
      const KAboutData* aboutData() {return myAboutData; };

   public slots:
      void configChanged();
      void profileViewActivated(const QString& profileName);
      void profileEditActivated(const QString& profileName);
      void resetProfileClicked();
      void saveProfileClicked();
      void newProfileClicked();
      void textChanged(const QString& text);
      void processFinished(KProcess *);
      void switchModule();
   private:
      KAboutData *myAboutData;
      ProfileWidget* profileWidget;
      QDomDocument* dataStore;
      QDomElement root;
      bool currentProfileChanged;
      QString curProfileName;
      QString rcfile;
      QVBoxLayout*  _layout;
      QDict<NetswitchModule> modules;
      NetswitchModule* activeModule;
};

#endif
