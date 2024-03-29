#ifndef PROJECT_VALUE_VIEW_H
#define PROJECT_VALUE_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "logic/project_value.h"
#include "logic/projectException.h"
#include "components/text_picker.h"
#include "components/date_picker.h"

#include "database/category_db.h"

class Project_value_view : public A_project_view
{
    Q_OBJECT
private:
    Project_value* source ;
    Text_picker* project_name = new Text_picker() ;
    Text_picker* value_status = new Text_picker("Change the value", "enter the new value") ;
    Date_picker* begin = new Date_picker() ;
    Date_picker* end = new Date_picker() ;

    void notify_source_modified() { emit source_modified(source) ; }

public:
    Project_value_view(Project_value* new_source, QWidget* parent = nullptr ) : A_project_view(parent), source(new_source)
    {
        QVBoxLayout* layout = new QVBoxLayout() ;

        QHBoxLayout* date_layout = new QHBoxLayout() ;
        date_layout->setSpacing(0) ;
        date_layout->addWidget( new QLabel("Begin", this) );
        date_layout->addWidget(begin);
        date_layout->addWidget( new QLabel("end", this) );
        date_layout->addWidget(end) ;

        layout->addWidget( project_name );
        layout->addLayout(date_layout) ;


        QHBoxLayout* status_layout = new QHBoxLayout() ;
        QLabel* status_label = new QLabel("Current status") ;
        status_label->setStyleSheet(Parameters::text_stylesheet_1) ;
        status_layout->addWidget(status_label) ;
        status_layout->addWidget( value_status ) ;

        layout->addLayout(status_layout) ;
        layout->setAlignment(Qt::AlignTop);
        layout->setAlignment(Qt::AlignJustify);

        layout->addStretch();
        reload() ;
        this->setLayout(layout) ;

        //change on the name of the project
        connect( project_name , &Text_picker::value_changed , this , [this](QString new_name){
            source->setName(new_name) ;
            notify_source_modified() ;
        } ) ;

        //change on date
        connect( begin, &Date_picker::value_changed , this, [this](QDate new_date){
            source->setBegin_date(new_date) ;
            notify_source_modified() ;
        } ) ;

        connect( end, &Date_picker::value_changed , this, [this](QDate new_date){
            source->setEnd_date(new_date) ;
            notify_source_modified() ;
        } ) ;
        //change on status
        connect( value_status, &Text_picker::value_changed, this, [this](QString new_value){
           bool convertion_ok = true ;
           int new_status = new_value.toInt( &convertion_ok ) ;

           if( ! convertion_ok || new_status > source->getTotal_value() ){
               QMessageBox  m(QMessageBox::Warning, "Wrong Value", "wrong value", QMessageBox::Ok) ;
               m.exec() ;
               value_status->setText( QString::number( source->getStatus() ) );
               return ;
           }
           source->setStatus(new_status) ;
           notify_source_modified() ;

           //test for the category_db
           Category_db c ;
           c.fetch() ;
        } );
    }
    ~Project_value_view() {}
    void reload(){
        project_name->setText( source->getName() ) ;
        begin->set_date( source->getBegin_date() ) ;
        end->set_date( source->getEnd_date() ) ;
        value_status->setText( QString::number(source->getStatus()) ) ;
    }
};

#endif // PROJECT_VALUE_VIEW_H
