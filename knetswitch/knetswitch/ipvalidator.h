/***************************************************************************
                          ipvalidator.h  -  description
                             -------------------
    begin                : Mon Sep 17 2001
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

#ifndef IPVALIDATOR_H
#define IPVALIDATOR_H

#include <qvalidator.h>

/**
  *@author Oliver Strutynski
  */

class IPValidator : public QValidator  {
public: 
	IPValidator( QWidget * parent, const char * name = 0);
	~IPValidator();

  virtual State validate ( QString &, int & ) const;
  virtual void fixup ( QString & ) const;
private:
  bool checkForByte(const QString s) const;
};

#endif
