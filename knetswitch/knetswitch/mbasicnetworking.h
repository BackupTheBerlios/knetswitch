/***************************************************************************
                          mbasicnetworking.h  -  description
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

#ifndef MBASICNETWORKING_H
#define MBASICNETWORKING_H

#include <netswitchmodule.h>
#include <basicnetworking.h>

/**
  *@author Oliver Strutynski
  */

class MBasicNetworking : public NetswitchModule  {
public: 
	MBasicNetworking(QWidget* parent);
	virtual ~MBasicNetworking();

  /**
   * Initializes the Module. The appropriate port of the configuration file
   * is passed in via the config parameter.
  */
  virtual void init(QDomElement);

  virtual QString getIdentifier();
  virtual QString getName();
  virtual QWidget* getWidget();

  /**
   * Resets the Module with the data passed in via the config parameter
   * Modules should basically perform the same operation as with the init()
   * routine.
  */
  virtual void reset(QDomElement);

  /**
   * Creates a DOM tree to be written to be written to the
   * full configuration file.
  */
  virtual QDomElement save();

  /**
   * Finalize the configuration. There should be some feedback via signals
   * implemented in the future.
  */
  virtual bool run();

private:
  Widget_BasicNetworking* widget;
  QString hostip, netmask, gateway, dnsip, device;
  QDomElement* root;
};

#endif
