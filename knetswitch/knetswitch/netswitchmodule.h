/***************************************************************************
                          netswitchmodule.h  -  description
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

#ifndef NETSWITCHMODULE_H
#define NETSWITCHMODULE_H


#include <qdom.h>
#include <qobject.h>
/**
 *Base class for all modules providing advanced
 * KNewSwitch configuration options.
 *@author Oliver Strutynski
*/
class NetswitchModule : public QObject {
 Q_OBJECT
public:
	NetswitchModule(QWidget* parent);
	virtual ~NetswitchModule();

  /**
   * Initializes the Module. The appropriate port of the configuration file
   * is passed in via the config parameter. Module has to be prepared to receive
   * a null element or an empty dom subtree.
  */
  virtual void init(QDomElement config) = 0;

  /**
   * Returns the unique identifier of this module.
  */
  virtual QString getIdentifier() = 0;

  /**
   * Returns a human readable name for this module.
  */
  virtual QString getName() = 0;

  /**
   * Returns the widget to be displayed to the main configuration dialog.
  */
  virtual QWidget* getWidget() = 0;

  /**
   * Resets the Module with the data passed in via the config parameter
   * Modules should basically perform the same operation as with the init()
   * routine.
  */
  virtual void reset(QDomElement) = 0;

  /**
   * Creates a DOM tree to be written to be written to the
   * full configuration file.
  */
  virtual QDomElement save() = 0;

  /**
   * Finalize the configuration. There should be some feedback via signals
   * implemented in the future.
  */
  virtual bool run() = 0;
};

#endif
