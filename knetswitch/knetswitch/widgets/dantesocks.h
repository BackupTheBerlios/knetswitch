/****************************************************************************
** Form interface generated from reading ui file 'dantesocks.ui'
**
** Created: Fri Oct 5 20:39:48 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef WIDGET_DANTESOCKS_H
#define WIDGET_DANTESOCKS_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;

class widget_dantesocks : public QWidget
{ 
    Q_OBJECT

public:
    widget_dantesocks( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~widget_dantesocks();

    QPushButton* pb_newSocksRoute;
    QComboBox* ComboBox1;
    QLabel* TextLabel1;
    QLabel* TextLabel2_2;
    QLabel* TextLabel2;
    QLabel* TextLabel2_3;
    QLineEdit* LineEdit1_2_2;
    QLineEdit* LineEdit1_2_3;
    QLineEdit* LineEdit1_2_4;
    QLabel* TextLabel2_3_3;
    QLabel* TextLabel2_3_2;
    QLabel* TextLabel2_3_4;
    QLineEdit* LineEdit1;
    QLineEdit* LineEdit1_2;
    QLineEdit* LineEdit1_2_5;

};

#endif // WIDGET_DANTESOCKS_H
