/***************************************************************************
                          profilewidget.h  -  description
                             -------------------
    begin                : Tue Sep 11 2001
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

#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <profiletab.h>
#include <qcombobox.h>

/**
  *@author Oliver Strutynski
  */

class ProfileWidget : public widget_profiletab  {
public: 
	ProfileWidget(QWidget* parent = 0);
	~ProfileWidget();
};

#endif
