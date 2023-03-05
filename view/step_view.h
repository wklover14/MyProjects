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
        reload() ;

        //style
        date->setStyleSheet( Parameters::date_stylesheet ) ;
        description->setStyleSheet(Parameters::text_stylesheet_2 ) ;
        this->setMaximumSize( Parameters::milestone_width , Parameters::milestone_height ) ;

        QVBoxLayout* layout = new QVBoxLayout() ;
        QHBoxLayout* button_layout = new QHBoxLayout() ;

        button_layout->setAlignment(Qt::AlignRight) ;
        button_layout->addWidget( action ) ;
        layout->addWidget( date ) ;
        layout->addWidget( description ) ;
        layout->addLayout( add_layout ) ;
        layout->addLayout( button_layout ) ;

        this->setLayout( layout ) ;
        //this->setStyleSheet(Parameters::milestone_stylesheet) ;

        connect( action, &QPushButton::released , this , &Step_view::toggle_button_action_value  ) ;
        //animation for action button
    } ;
    ~Step_view(){} ;
    QDate getDate()const { return QDate::currentDate() ; }
    Step* get_source() const { return source ; }
    void set_disabled(bool b) { action->setDisabled(b) ;  }
    void set_enabled(bool b) {action->setEnabled(b) ; }

    virtual void reload() {
        date->setText(source->getDate().toString()) ;
        description->setText( source->getComment() ) ;

        if(!source->getIs_done())
            action->setText("validate") ;
        else
            action->setText("undo") ;
    }

signals:
    void value_changed() ;

private slots :
    void toggle_button_action_value()
    {
        if( source->getIs_done() ){
            //do something to the reel step
            action->setText("validate") ;
            source->setIs_done(false) ;
        } else {
            //do something to the real step
            action->setText("undo") ;
            source->setIs_done(true) ;
        }
        //notify that there is a new value
        emit value_changed() ;
    };

private :
    QLabel* date = new QLabel() ;
    QLabel* description = new QLabel() ;
    QPushButton* action  = new QPushButton() ;
    QVBoxLayout* add_layout = new QVBoxLayout() ;
    Step* source;

protected :
    void add_widget(QWidget* item) {  add_layout->addWidget( item) ;  } ; //it will be use for adding external item to the widget by all inherited classes
};

#endif // STEP_VIEW_H
