#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './profiletab.ui'
**
** Created: Sun Sep 16 20:06:03 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "profiletab.h"

#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a widget_profiletab which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
widget_profiletab::widget_profiletab( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "widget_profiletab" );
    resize( 503, 448 ); 
    setCaption( i18n( "Form1" ) );

    TabWidget2 = new QTabWidget( this, "TabWidget2" );
    TabWidget2->setGeometry( QRect( 20, 30, 460, 390 ) ); 

    tab = new QWidget( TabWidget2, "tab" );

    TextLabel1 = new QLabel( tab, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 20, 120, 20 ) ); 
    TextLabel1->setText( i18n( "Profile Name" ) );

    combo_profileNames1 = new QComboBox( FALSE, tab, "combo_profileNames1" );
    combo_profileNames1->setGeometry( QRect( 140, 20, 310, 21 ) ); 

    GroupBox1 = new QGroupBox( tab, "GroupBox1" );
    GroupBox1->setGeometry( QRect( 5, 45, 441, 311 ) ); 
    GroupBox1->setTitle( i18n( "Profile Settings" ) );

    lbl_netmask = new QLabel( GroupBox1, "lbl_netmask" );
    lbl_netmask->setGeometry( QRect( 140, 50, 260, 20 ) ); 
    lbl_netmask->setText( i18n( "TextLabel2" ) );

    lbl_dns = new QLabel( GroupBox1, "lbl_dns" );
    lbl_dns->setGeometry( QRect( 140, 75, 230, 20 ) ); 
    lbl_dns->setText( i18n( "TextLabel2" ) );

    TextLabel1_3_2_2_3 = new QLabel( GroupBox1, "TextLabel1_3_2_2_3" );
    TextLabel1_3_2_2_3->setGeometry( QRect( 15, 50, 111, 21 ) ); 
    TextLabel1_3_2_2_3->setText( i18n( "Netmask" ) );

    TextLabel1_3_3 = new QLabel( GroupBox1, "TextLabel1_3_3" );
    TextLabel1_3_3->setGeometry( QRect( 15, 25, 111, 21 ) ); 
    TextLabel1_3_3->setText( i18n( "IP-Adress" ) );

    TextLabel1_3_2_4 = new QLabel( GroupBox1, "TextLabel1_3_2_4" );
    TextLabel1_3_2_4->setGeometry( QRect( 15, 100, 111, 21 ) ); 
    TextLabel1_3_2_4->setText( i18n( "Default-Gateway" ) );

    lbl_gateway = new QLabel( GroupBox1, "lbl_gateway" );
    lbl_gateway->setGeometry( QRect( 140, 100, 270, 20 ) ); 
    lbl_gateway->setText( i18n( "TextLabel2" ) );

    lbl_deviceName = new QLabel( GroupBox1, "lbl_deviceName" );
    lbl_deviceName->setGeometry( QRect( 140, 125, 270, 20 ) ); 
    lbl_deviceName->setText( i18n( "TextLabel2" ) );

    TextLabel1_3_2_3_2 = new QLabel( GroupBox1, "TextLabel1_3_2_3_2" );
    TextLabel1_3_2_3_2->setGeometry( QRect( 15, 125, 111, 21 ) ); 
    TextLabel1_3_2_3_2->setText( i18n( "Device" ) );

    TextLabel1_3_2_2_2_2 = new QLabel( GroupBox1, "TextLabel1_3_2_2_2_2" );
    TextLabel1_3_2_2_2_2->setGeometry( QRect( 15, 75, 111, 21 ) ); 
    TextLabel1_3_2_2_2_2->setText( i18n( "Name-Server" ) );

    lbl_ip = new QLabel( GroupBox1, "lbl_ip" );
    lbl_ip->setGeometry( QRect( 140, 25, 250, 20 ) ); 
    lbl_ip->setText( i18n( "TextLabel2" ) );
    TabWidget2->insertTab( tab, i18n( "Select Profile" ) );

    tab_2 = new QWidget( TabWidget2, "tab_2" );

    TextLabel1_2 = new QLabel( tab_2, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 20, 120, 20 ) ); 
    TextLabel1_2->setText( i18n( "Profile Name" ) );

    combo_profileNames2 = new QComboBox( FALSE, tab_2, "combo_profileNames2" );
    combo_profileNames2->setGeometry( QRect( 130, 20, 210, 21 ) ); 

    pb_saveCurrentProfile = new QPushButton( tab_2, "pb_saveCurrentProfile" );
    pb_saveCurrentProfile->setGeometry( QRect( 140, 290, 104, 28 ) ); 
    pb_saveCurrentProfile->setText( i18n( "Save Profile" ) );

    pb_resetCurrentProfile = new QPushButton( tab_2, "pb_resetCurrentProfile" );
    pb_resetCurrentProfile->setGeometry( QRect( 250, 290, 104, 28 ) ); 
    pb_resetCurrentProfile->setText( i18n( "Reset Profile" ) );

    le_hostip = new QLineEdit( tab_2, "le_hostip" );
    le_hostip->setGeometry( QRect( 130, 60, 261, 22 ) ); 

    le_netmask = new QLineEdit( tab_2, "le_netmask" );
    le_netmask->setGeometry( QRect( 130, 90, 261, 22 ) ); 

    le_dnsip = new QLineEdit( tab_2, "le_dnsip" );
    le_dnsip->setGeometry( QRect( 130, 120, 261, 22 ) ); 

    le_gateway = new QLineEdit( tab_2, "le_gateway" );
    le_gateway->setGeometry( QRect( 130, 150, 261, 22 ) ); 

    le_deviceName = new QLineEdit( tab_2, "le_deviceName" );
    le_deviceName->setGeometry( QRect( 128, 185, 261, 22 ) ); 

    pb_newProfile = new QPushButton( tab_2, "pb_newProfile" );
    pb_newProfile->setGeometry( QRect( 350, 20, 80, 20 ) ); 
    pb_newProfile->setText( i18n( "New Profile..." ) );

    TextLabel1_3_2_3 = new QLabel( tab_2, "TextLabel1_3_2_3" );
    TextLabel1_3_2_3->setGeometry( QRect( 10, 180, 111, 21 ) ); 
    TextLabel1_3_2_3->setText( i18n( "Device" ) );

    TextLabel1_3 = new QLabel( tab_2, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 10, 60, 111, 21 ) ); 
    TextLabel1_3->setText( i18n( "IP-Adress" ) );

    TextLabel1_3_2_2 = new QLabel( tab_2, "TextLabel1_3_2_2" );
    TextLabel1_3_2_2->setGeometry( QRect( 10, 90, 111, 21 ) ); 
    TextLabel1_3_2_2->setText( i18n( "Netmask" ) );

    TextLabel1_3_2_2_2 = new QLabel( tab_2, "TextLabel1_3_2_2_2" );
    TextLabel1_3_2_2_2->setGeometry( QRect( 10, 120, 111, 21 ) ); 
    TextLabel1_3_2_2_2->setText( i18n( "Name-Server" ) );

    TextLabel1_3_2 = new QLabel( tab_2, "TextLabel1_3_2" );
    TextLabel1_3_2->setGeometry( QRect( 10, 150, 111, 21 ) ); 
    TextLabel1_3_2->setText( i18n( "Default-Gateway" ) );
    TabWidget2->insertTab( tab_2, i18n( "Edit Profiles" ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
widget_profiletab::~widget_profiletab()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "profiletab.moc"
