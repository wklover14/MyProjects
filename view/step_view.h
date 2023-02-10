#ifndef STEP_VIEW_H
#define STEP_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDate>

#include "parameters.h"
#include "logic/step.h"

class Step_view : public QWidget
{
    //this class provide a widget in order to print information for a milestone / checkpoint
    Q_OBJECT
public :
        Step_view(Step* s ,QWidget* parent = nullptr): QWidget(parent), source(s) {

        //content
        date->setText(s->getDate().toString());

        // comment.setText( QString::number(c->getValue()) );
        if(!s->getIs_done())
            action->setText("validate") ;
        else
            action->setText("undo") ;

        //style
        date->setStyleSheet( Parameters::date_stylesheet ) ;
        action->setStyleSheet( Parameters::button_stylesheet ) ;
        this->setMaximumSize( Parameters::milestone_width , Parameters::milestone_height ) ;

        QVBoxLayout* layout = new QVBoxLayout() ;
        QHBoxLayout* button_layout = new QHBoxLayout() ;

        button_layout->setAlignment(Qt::AlignRight) ;
        button_layout->addWidget( action ) ;
        layout->addWidget( date ) ;
        layout->addLayout(more_layout) ;
        layout->addLayout( button_layout ) ;

        this->setLayout( layout ) ;
        this->setStyleSheet(Parameters::milestone_stylesheet) ;

        connect( action, &QPushButton::released , this , &Step_view::toggle_button_action_value  ) ;

        //animation for action button
    } ;
    ~Step_view(){} ;
    QDate getDate()const { return QDate::currentDate() ; }
    Step* get_source() const { return source ; }

signals:
    void value_changed() ;

private slots :
    void toggle_button_action_value()
    {
        if( source->getIs_done() ){
            //do something to the reel milestone
            action->setText("undo") ;
            source->setIs_done(false) ;
        } else {
            //do something to the real milestone
            action->setText("validate") ;
            source->setIs_done(true) ;
        }
        //notify that there is a new value
        emit value_changed() ;
    };

private :
    // any class with  "_widget" particle will do a aggregation of a class without particle,
    // in order to represent this main class
    QLabel* date = new QLabel() ;
    QPushButton* action  = new QPushButton() ;
    Step* source;

protected :
     QHBoxLayout* more_layout = new QHBoxLayout() ; //it will be use for adding external item to the widget
};

#endif // STEP_VIEW_H
