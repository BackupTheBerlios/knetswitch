/***************************************************************************
                          ipvalidator.cpp  -  description
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

#include "ipvalidator.h"
#include <qregexp.h>
#include <iostream.h>

IPValidator::IPValidator( QWidget * parent, const char * name = 0) : QValidator(parent, name) {
}

IPValidator::~IPValidator(){
}

bool IPValidator::checkForByte(QString s) const {
  QRegExp r("^[0-9]+$");
  cout << "checking: " << s << endl;
  if (r.find(s, 0) >= 0) {
      if (s.toUInt() > 255) {
          // not in the range of 0..255
          return false;
      }
  } else {
      return false;
  }
  return true;
}

QValidator::State IPValidator::validate ( QString &s, int &pos ) const {
  QRegExp r("[0-9]+");
  cout << "validating "<< "\n";

  int last = 0; int count = 1;
  cout << pos << endl;

  for (unsigned int i = 0; i < s.length(); i++) {
      if ((0 != r.find(QString(s[i]), 0)) && ('.' != s[i]) ) {
          cout << "invalid character " << endl;
          s = s.left(pos - 1); pos--; return QValidator::Intermediate;
      }

      if ('.' == s[i]) {
          if (4 == count) { s = s.left(pos - 1); pos--; return QValidator::Intermediate; }
          cout << s.mid(last, i-last+1) << endl;
          if (r.find(s.mid(last, i-last+1), 0) >= 0) {
              if (s.mid(last, i-last+1).toUInt() > 255) {
                  // not a valid ip adress
                  s = s.left(pos - 1); pos--; return QValidator::Intermediate;
              }
          } else { s = s.left( pos - 1); pos--; return QValidator::Intermediate; }
          last = i+1;
          count++;
      } else if ((s.length() - 1) == i) {
          cout << "last character" << endl;
          if (!checkForByte(s.mid(last))) {
              s = s.left( pos - 1); pos--; return QValidator::Intermediate;
          }
      } else {
          if (0 != r.find(QString(s[i]), 0)) {
              cout << "invalid character " << endl;
              s = s.left(pos - 1); pos--; return QValidator::Intermediate;
          }
      }

  }

  if (3 != count) {
      return QValidator::Intermediate;
  } else {
      return QValidator::Valid;
  }
}


void IPValidator::fixup ( QString & ) const {}
