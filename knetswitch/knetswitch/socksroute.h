/***************************************************************************
                          socksroute.h  -  description
                             -------------------
    begin                : Sun Oct 14 2001
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

#ifndef SOCKSROUTE_H
#define SOCKSROUTE_H

#include <qstring.h>

/**
  *@author Oliver Strutynski
  */

class SocksRoute {
public: 
	SocksRoute(QString name);
	~SocksRoute();
private:
  QString name, from, to, via, proto, proxyproto, method;
};

#endif
