/****************************************************************************
** Form implementation generated from reading ui file 'dantesocks.ui'
**
** Created: Fri Oct 5 20:39:49 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "dantesocks.h"

#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a widget_dantesocks which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
widget_dantesocks::widget_dantesocks( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "widget_dantesocks" );
    resize( 390, 291 ); 
    setCaption( tr( "Form1" ) );

    pb_newSocksRoute = new QPushButton( this, "pb_newSocksRoute" );
    pb_newSocksRoute->setGeometry( QRect( 325, 10, 60, 25 ) ); 
    pb_newSocksRoute->setText( tr( "New..." ) );

    ComboBox1 = new QComboBox( FALSE, this, "ComboBox1" );
    ComboBox1->setGeometry( QRect( 90, 10, 221, 21 ) ); 

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 15, 15, 61, 15 ) ); 
    TextLabel1->setText( tr( "Routes" ) );

    TextLabel2_2 = new QLabel( this, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 20, 85, 61, 15 ) ); 
    TextLabel2_2->setText( tr( "To" ) );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 20, 60, 61, 15 ) ); 
    TextLabel2->setText( tr( "From" ) );

    TextLabel2_3 = new QLabel( this, "TextLabel2_3" );
    TextLabel2_3->setGeometry( QRect( 20, 110, 61, 15 ) ); 
    TextLabel2_3->setText( tr( "Via" ) );

    LineEdit1_2_2 = new QLineEdit( this, "LineEdit1_2_2" );
    LineEdit1_2_2->setGeometry( QRect( 140, 140, 151, 22 ) ); 

    LineEdit1_2_3 = new QLineEdit( this, "LineEdit1_2_3" );
    LineEdit1_2_3->setGeometry( QRect( 140, 165, 151, 22 ) ); 

    LineEdit1_2_4 = new QLineEdit( this, "LineEdit1_2_4" );
    LineEdit1_2_4->setGeometry( QRect( 140, 190, 151, 22 ) ); 

    TextLabel2_3_3 = new QLabel( this, "TextLabel2_3_3" );
    TextLabel2_3_3->setGeometry( QRect( 20, 170, 105, 16 ) ); 
    TextLabel2_3_3->setText( tr( "Proxy-Protocol" ) );

    TextLabel2_3_2 = new QLabel( this, "TextLabel2_3_2" );
    TextLabel2_3_2->setGeometry( QRect( 20, 145, 105, 16 ) ); 
    TextLabel2_3_2->setText( tr( "Protocol" ) );

    TextLabel2_3_4 = new QLabel( this, "TextLabel2_3_4" );
    TextLabel2_3_4->setGeometry( QRect( 20, 195, 100, 16 ) ); 
    TextLabel2_3_4->setText( tr( "Method" ) );

    LineEdit1 = new QLineEdit( this, "LineEdit1" );
    LineEdit1->setGeometry( QRect( 140, 55, 151, 22 ) ); 

    LineEdit1_2 = new QLineEdit( this, "LineEdit1_2" );
    LineEdit1_2->setGeometry( QRect( 140, 80, 151, 22 ) ); 

    LineEdit1_2_5 = new QLineEdit( this, "LineEdit1_2_5" );
    LineEdit1_2_5->setGeometry( QRect( 140, 105, 151, 22 ) ); 
}

/*  
 *  Destroys the object and frees any allocated resources
 */
widget_dantesocks::~widget_dantesocks()
{
    // no need to delete child widgets, Qt does it all for us
}

