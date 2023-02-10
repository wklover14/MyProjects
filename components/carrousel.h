#ifndef CARROUSEL_H
#define CARROUSEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <list>
#include <QStackedWidget>

#include "view/step_view.h"
#include "parameters.h"

//provide a carroussel of step_view ,
using namespace std ;

class Carrousel : public QWidget {
  Q_OBJECT

private :
    QPushButton* left_arrow  = new QPushButton();
    QPushButton* right_arrow  = new QPushButton();
    QHBoxLayout* layout  = new QHBoxLayout();
    list<Step_view*> elements ;
    QStackedWidget* elements_ = new QStackedWidget() ;

    using iterator =  list<Step_view*>::iterator ;
    iterator current ; //the element that will be print

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

    void add(Step_view* e) {
        elements.push_back(e) ;
        elements_->addWidget(e) ;
        connect( e, &Step_view::value_changed , this, [e, this](){
            emit step_changed(e->get_source()) ;
        } ) ;
    };

    void remove(Step_view* e) {
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

    void remove_all() {
        //remova all elements from carrousel
        elements.clear() ;
        for(int i=0 ; i < elements_->count() ; i++ ){
            elements_->removeWidget( elements_->widget(i) ) ;
        }
    }
signals :
    void step_changed(Step*) ;

public slots :
    void next()  {
        current++;
        if( current == elements.end() )//return at the begining
        {
            current = elements.begin() ;
            //qDebug() << "return to beginning" ;
        }
        //qDebug() << "next \n"  ;

        elements_->setCurrentWidget( *current ) ;  // display the new element
        this->update() ;
    };
    void previous() {
        if( current == elements.begin() )//return at the end
        {
            current = elements.end() ;
            current-- ;
            //qDebug() << "return to the last \n"  ;
        }
        else
        {
            current--;
            //qDebug() << "previous \n"  ;
        }

        elements_->setCurrentWidget( *current ) ;  // display the new element
        this->update() ;
    } ;

};

#endif // CARROUSEL_H
