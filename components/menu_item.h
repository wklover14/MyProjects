#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>

#include "parameters.h"

class Item_menu : public QWidget
{
    Q_OBJECT
private :
    QLabel* image = new QLabel();
    QLabel* title = new QLabel() ;
    QLabel* underline  = new QLabel();
    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* title_layout = new QVBoxLayout() ;

public:
   explicit Item_menu(QString newImage, QString newTitle, QWidget* parent = nullptr) :
        QWidget(parent)
    {
        QPixmap *px = new QPixmap(newImage) ;
        QPixmap new_px = px->scaled( QSize(Parameters::icon_width, Parameters::icon_height) ) ;
        image->setPixmap( new_px ) ;
        image->setStyleSheet(Parameters::icon_stylesheet) ;
        title->setText(newTitle) ;

        underline->setStyleSheet(Parameters::underline_stylesheet) ;
        title->setStyleSheet(Parameters::text_stylesheet_1);

        title_layout->addWidget(title);
        title_layout->addWidget(underline);
        layout->addWidget(image);
        layout->addLayout(title_layout);

        this->setAcceptDrops(true) ;
        this->setLayout(layout);
        this->setMaximumSize( Parameters::item_width, Parameters::item_height ) ;

        underline->hide() ;
        //connect( this, &Item_menu::mousePressEvent, this, &Item_menu::set_active  ) ;
    }
    ~Item_menu(){} ;

signals :
    void mousePressEvent(QMouseEvent* event) override ;

public slots :
    void toggle_active() {
        if( underline->isHidden() ){
            underline->show() ;
        } else {
            underline->hide() ;
        }
    }
};


#endif // MENU_ITEM_H
