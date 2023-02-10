#ifndef MILESTONE_WIDGET_H
#define MILESTONE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDate>

#include "parameters.h"
#include "logic/milestone.h"
#include "logic/checkpoint.h"

class Milestone_widget : public QWidget
{
    //this class provide a widget in order to print information for a milestone / checkpoint
    Q_OBJECT
public :
    explicit Milestone_widget(Checkpoint* c ,QWidget* parent = nullptr): QWidget(parent) {
        checkpoint = c ;

        //content
        date.setText(c->getDate().toString());
        comment.setText( QString::number(c->getValue()) );
        if(!c->getIs_donne())
            action.setText("validate") ;
        else
            action.setText("unvalidate") ;
        //style
        date.setStyleSheet( Parameters::date_stylesheet ) ;
        comment.setStyleSheet( Parameters::text_stylesheet_2 ) ;
        action.setStyleSheet( Parameters::button_stylesheet ) ;
        comment.setWordWrap(true) ;

        this->setMaximumSize( Parameters::milestone_width , Parameters::milestone_height ) ;


        button_layout.setAlignment(Qt::AlignRight) ;
        button_layout.addWidget( &action ) ;
        layout.addWidget( &date ) ;
        layout.addWidget( &comment ) ;
        layout.addLayout( &button_layout ) ;
        this->setLayout( &layout ) ;
        this->setStyleSheet(Parameters::milestone_stylesheet) ;

        connect( &action, &QPushButton::released , this , &Milestone_widget::toggle_button_action_value  ) ;

        //animation for action button
    } ;
    explicit Milestone_widget(Milestone* m ,QWidget* parent = nullptr): QWidget(parent) {
        milestone = m ;

        //content
        date.setText(m->getDate().toString());
        comment.setText( m->getComment() );
        if( !m->getIs_done() )
            action.setText("validate") ;
        else
            action.setText("unvalidate") ;

        //style
        date.setStyleSheet( Parameters::date_stylesheet ) ;
        comment.setStyleSheet( Parameters::text_stylesheet_2 ) ;
        action.setStyleSheet( Parameters::button_stylesheet ) ;
        comment.setWordWrap(true) ;
        this->setStyleSheet(Parameters::milestone_stylesheet) ;

        this->setMaximumSize( Parameters::milestone_width , Parameters::milestone_height ) ;


        button_layout.setAlignment(Qt::AlignRight) ;
        button_layout.addWidget( &action ) ;
        layout.addWidget( &date ) ;
        layout.addWidget( &comment ) ;
        layout.addLayout( &button_layout ) ;
        this->setLayout( &layout ) ;

        connect( &action, &QPushButton::released , this , &Milestone_widget::toggle_button_action_value  ) ;

        //animation for action button
    } ;

    ~Milestone_widget(){} ;
    QDate getDate()const { return QDate::currentDate() ; }
    void setComment(QString c) { comment.setText(c) ;  }

private slots :
    void toggle_button_action_value()
    {
        if( action.text() == "validate" ){
            //do something to the reel milestone
            action.setText("undo") ;
        } else {
            //do something to the real milestone
            action.setText("validate") ;
        }
    };

private :
    // any class with  "_widget" particle will do a aggregation of a class without particle,
    // in order to represent this main class
    QLabel date ;
    QLabel comment ;
    QPushButton action ;
    QVBoxLayout layout ;
    QHBoxLayout button_layout ;
    Checkpoint* checkpoint = new Checkpoint(QDate::currentDate(), 10) ;
    Milestone* milestone = new Milestone(QDate::currentDate(), "") ;

};

#endif // MILESTONE_WIDGET_H
