/***************************************************************************
                          msocks.h  -  description
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

#ifndef MSOCKS_H
#define MSOCKS_H

#include <netswitchmodule.h>
#include <dantesocks.h>
#include <socksroute.h>

/**KNetswitch Module implementing socks configuration.
  *@author Oliver Strutynski
  */

class MSocks : public NetswitchModule  {
public: 
	MSocks(QWidget* widget);
	virtual ~MSocks();

  /**
   * Initializes the Module. The appropriate port of the configuration file
   * is passed in via the config parameter.
  */
  virtual void MSocks::init(QDomElement);

  virtual QString getIdentifier();
  virtual QString getName();
  virtual QWidget* MSocks::getWidget();

  /**
   * Resets the Module with the data passed in via the config parameter
   * Modules should basically perform the same operation as with the init()
   * routine.
  */
  virtual void MSocks::reset(QDomElement);

  /**
   * Creates a DOM tree to be written to be written to the
   * full configuration file.
  */
  virtual QDomElement MSocks::save();

  /**
   * Finalize the configuration. There should be some feedback via signals
   * implemented in the future.
  */
  virtual bool MSocks::run();

public slots:

  void createNewRoute();

private:
  widget_dantesocks* widget;
  QDomElement* root;
  QDict<SocksRoute> routes;
  bool currentProfileChanged;
};

#endif
