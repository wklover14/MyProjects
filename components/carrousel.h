#ifndef CARROUSEL_H
#define CARROUSEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <set>
#include <QStackedWidget>

#include "view/step_view.h"
#include "logic/step.h"
#include "parameters.h"

//provide a carroussel of step_view ,
using namespace std ;

class Carrousel : public QWidget {
  Q_OBJECT

private :
    QPushButton* left_arrow  = new QPushButton();
    QPushButton* right_arrow  = new QPushButton();
    QHBoxLayout* layout  = new QHBoxLayout();
    set<Step*, StepCmp> elements ;
    QStackedWidget* elements_ = new QStackedWidget() ;

    using iterator =  set<Step*, StepCmp>::iterator ;
    iterator current = elements.begin() ; //the element that will be print

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

    void add(Step* e) {
        elements.insert(e) ;
        elements_->addWidget(e->widget()) ;
        connect( dynamic_cast<Step_view*>(e->widget()), &Step_view::value_changed , this, [e, this](){
            emit step_changed(e) ;
        } ) ;
    };

    void remove(Step* e) {
        if( e == *current )
        {
            next() ;
        }
        if ( elements_->indexOf( e->widget() ) == elements_->currentIndex() ){
            elements_->setCurrentIndex( (elements_->currentIndex() + 1) % elements_->count() ) ;
        }
        elements.erase(e) ;
        elements_->removeWidget(e->widget()) ;
    };

    void remove_all() {
        //remove all elements from carrousel
        elements.clear() ;
        for(int i=0 ; i < elements_->count() ; i++ ){
            elements_->removeWidget( elements_->widget(i) ) ;
        }
    }

    void reload(Step* s) {
        int index = elements_->indexOf(s->widget()) ;
        if( index != -1 )
        {
            //verify if the step is already present
            if( s->getIs_done() == false ) {
                dynamic_cast<Step_view*>(s->widget())->set_disabled(true) ;
            } else {
                dynamic_cast<Step_view*>(s->widget())->set_enabled(true) ;
            }
                dynamic_cast<Step_view*>(s->widget())->update() ; //step already present
            return  ;
        }
        //if not, it'll be add
        add( s ) ;
    }

    void set_current(Step* s) {
        auto it = elements.find(s) ;
        if( it == elements.end() ) //find the elements
            return ;
        current = it ;
        elements_->setCurrentWidget( s->widget() ) ;
        dynamic_cast<Step_view*>(s->widget())->set_enabled(true) ; //current is always enable
    }
signals :
    void step_changed(Step*) ;

public slots :
    void next()  {
        if( elements.empty() ) return ;
        current++ ;
        if( current == elements.end() )//last element
        {
            current-- ;
            return ;
        }
        elements_->setCurrentWidget( (*current)->widget() ) ;  // display the new element
        this->update() ;
    };

    void previous() {
        if( elements.empty() ) return ;
        if( current == elements.begin() )//first element
        {
            return ;
        }
        current--;

        elements_->setCurrentWidget( (*current)->widget() ) ;  // display the new element
        this->update() ;
    } ;

};

#endif // CARROUSEL_H
