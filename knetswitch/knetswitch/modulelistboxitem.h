/***************************************************************************
                          modulelistboxitem.h  -  description
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

#ifndef MODULELISTBOXITEM_H
#define MODULELISTBOXITEM_H

#include <qlistbox.h>
#include <qpixmap.h>

/**
  *@author Oliver Strutynski
  */

class ModuleListBoxItem : public QListBoxPixmap  {
public: 
	ModuleListBoxItem(const QPixmap & pm, const QString & name, const QString & identifier);
	~ModuleListBoxItem();
	
	/** returns the identifier associated with this listbox item */
	QString getIdentifier();
private:
  QString identifier;
};

#endif
