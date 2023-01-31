#include "color_picker.h"
#include "parameters.h"
#include "color_item.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>
#include <list>

Color_picker::Color_picker(QWidget *parent): QWidget(parent), item(){

    //add item
    layout->addWidget(&item) ;
    this->setLayout(layout) ;
    this->setMaximumSize( Parameters::color_shape_weight * 2 , Parameters::color_shape_height * 2 ) ;
    setAcceptDrops(true) ;
    this->setStyleSheet("border-color : #FFFFFF;") ;
    connect(this , &Color_picker::mousePressEvent , this, &Color_picker::handleClick );
}

Color_picker::~Color_picker() {};


void Color_picker::handleClick(QMouseEvent* mouseClickEvent){
    QDialog colors ;

    QVBoxLayout layout ;
    layout.setSpacing(4) ;

    //create all colors item
    list<Color_item*> items;
    for(auto it: Parameters::hexa_code_colors ){
        QString code = it.second ;
        QString name = Parameters::colors_name.find(it.first)->second ;
        items.push_back( new Color_item( code, name ) ) ;
    }

    //connect all the color item to QDialog colors
    for(Color_item* it : items){
        layout.addWidget(it) ;
        connect( it, &Color_item::mousePressEvent , &colors , [it, &colors, this](){
            this->item.setColor( it->getColor() ) ;
            colors.close() ; //we need to delete all the item next
        }) ;
    }

    //add the cancel buttons
    QPushButton *cancelButton = new QPushButton("Cancel") ;
    layout.addWidget(cancelButton) ;
    connect(cancelButton, &QPushButton::released, &colors, &QDialog::close ) ;

    colors.setLayout(&layout) ;
    colors.exec();
    mouseClickEvent->isBeginEvent() ; //in order to avoid warning
}
