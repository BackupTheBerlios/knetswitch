/***************************************************************************
                          modulelistboxitem.cpp  -  description
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

#include "modulelistboxitem.h"
#include <qpixmap.h>
#include <qstring.h>

ModuleListBoxItem::ModuleListBoxItem(const QPixmap & pm, const QString & name, const QString & identifier) : QListBoxPixmap(pm, name) {
  this->identifier = identifier;
}

ModuleListBoxItem::~ModuleListBoxItem(){
}

QString ModuleListBoxItem::getIdentifier() {
  return identifier;
}
