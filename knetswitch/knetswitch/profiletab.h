/****************************************************************************
** Form interface generated from reading ui file './profiletab.ui'
**
** Created: Sun Sep 16 20:05:55 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef WIDGET_PROFILETAB_H
#define WIDGET_PROFILETAB_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;

class widget_profiletab : public QWidget
{ 
    Q_OBJECT

public:
    widget_profiletab( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~widget_profiletab();

    QTabWidget* TabWidget2;
    QWidget* tab;
    QLabel* TextLabel1;
    QComboBox* combo_profileNames1;
    QGroupBox* GroupBox1;
    QLabel* lbl_netmask;
    QLabel* lbl_dns;
    QLabel* TextLabel1_3_2_2_3;
    QLabel* TextLabel1_3_3;
    QLabel* TextLabel1_3_2_4;
    QLabel* lbl_gateway;
    QLabel* lbl_deviceName;
    QLabel* TextLabel1_3_2_3_2;
    QLabel* TextLabel1_3_2_2_2_2;
    QLabel* lbl_ip;
    QWidget* tab_2;
    QLabel* TextLabel1_2;
    QComboBox* combo_profileNames2;
    QPushButton* pb_saveCurrentProfile;
    QPushButton* pb_resetCurrentProfile;
    QLineEdit* le_hostip;
    QLineEdit* le_netmask;
    QLineEdit* le_dnsip;
    QLineEdit* le_gateway;
    QLineEdit* le_deviceName;
    QPushButton* pb_newProfile;
    QLabel* TextLabel1_3_2_3;
    QLabel* TextLabel1_3;
    QLabel* TextLabel1_3_2_2;
    QLabel* TextLabel1_3_2_2_2;
    QLabel* TextLabel1_3_2;

};

#endif // WIDGET_PROFILETAB_H
