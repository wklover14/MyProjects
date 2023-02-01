#ifndef CARROUSEL_H
#define CARROUSEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <list>
#include <QStackedWidget>

#include "milestone_widget.h"
#include "parameters.h"

//provide a carroussel of milestone ,
using namespace std ;

class Carrousel : public QWidget {
  Q_OBJECT
public :
    explicit Carrousel( QWidget* parent = nullptr) : QWidget(parent){
        current = elements.begin() ; //first element

        //init
        left_arrow->setIcon( QIcon( "../MyProjects/images/left_arrow.png" )) ;
        right_arrow->setIcon ( QIcon ("../MyProjects/images/right_arrow.png" ) ) ;
        elements_->setMaximumSize( Parameters::milestone_width , Parameters::milestone_height ) ;
        left_arrow->setMaximumSize( Parameters::arrow_width, Parameters::arrow_height ) ;
        right_arrow->setMaximumSize( Parameters::arrow_width, Parameters::arrow_height ) ;
        this->setMaximumSize( Parameters::carrousel_width , Parameters::carrousel_height ) ;

        //interface
        layout->addWidget( left_arrow ) ;
        layout->addWidget( elements_ ) ; //we only display the stackedWidget
        layout->addWidget( right_arrow ) ;

        //link click to the functions next
        connect( left_arrow, SIGNAL( released() ) , this, SLOT(previous()) );
        connect( right_arrow, SIGNAL( released() ), this, SLOT(next()) ) ;

        this->setLayout( layout ) ;
    } ;
    ~Carrousel(){} ;

    void add(Milestone_widget* e) {
        elements.push_back(e) ;
        //sort the list by date
        elements.sort( [](Milestone_widget* e1,Milestone_widget* e2){
            return e1->getDate() < e2->getDate() ;
        } ) ;
        elements_->addWidget(e) ;
    };
    void remove(Milestone_widget* e) {
        if( e == *current )
        {
            next() ;
        }
        if ( elements_->indexOf(e) == elements_->currentIndex() ){
            elements_->setCurrentIndex( (elements_->currentIndex() + 1) % elements_->count() ) ;
        }
        elements.remove(e) ;
        elements_->removeWidget(e) ;
    };


public slots :
    void next()  {
        current++;
        if( current == elements.end() )//return at the begining
        {
            current = elements.begin() ;
            qDebug() << "return to beginning" ;
        }
        qDebug() << "next \n"  ;

        elements_->setCurrentWidget( *current ) ;  // display the new element
        this->update() ;
    };
    void previous() {
        if( current == elements.begin() )//return at the end
        {
            current = elements.end() ;
            current-- ;
            qDebug() << "return to the last \n"  ;
        }
        else
        {
            current--;
            qDebug() << "previous \n"  ;
        }

        elements_->setCurrentWidget( *current ) ;  // display the new element
        this->update() ;
    } ;

private :
    QPushButton* left_arrow  = new QPushButton();
    QPushButton* right_arrow  = new QPushButton();
    QHBoxLayout* layout  = new QHBoxLayout();
    list<Milestone_widget*> elements ;
    QStackedWidget* elements_ = new QStackedWidget() ;

    using iterator =  list<Milestone_widget*>::iterator ;
    iterator current ; //the element that will be print
};

#endif // CARROUSEL_H
