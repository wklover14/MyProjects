#ifndef PROJECT_STEP_VIEW_H
#define PROJECT_STEP_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "components/text_picker.h"
#include "components/date_picker.h"
#include "components/carrousel.h"
#include "components/icon_button.h"
#include "logic/project_step.h"
#include "logic/projectException.h"
#include "view/a_project_view.h"
#include "view/step_picker_view.h"

#include "database/project_step_db.h"


class Project_step_view : public A_project_view
{
    Q_OBJECT
    //this class provide a widget for a project with step only,
protected :
    Project_step* source ;
    Text_picker* project_name = new Text_picker() ;
    Date_picker* begin = new Date_picker() ;
    Date_picker* end = new Date_picker() ;
    Carrousel* carrousel = new Carrousel() ;
    Icon_button* add_step_button = new Icon_button() ;
    Project_step_db* project_step_dtb = new Project_step_db() ;

    void notify_source_modified() { emit source_modified(source) ;   };
    void update_database() const  { project_step_dtb->update( *source ) ;  }
    void add_database(Step s) const { project_step_dtb->add_step( *source , s );  }
public:
    Project_step_view(Project_step* new_source,QWidget* parent = nullptr) : A_project_view(parent), source(new_source)
    {
        QVBoxLayout* layout = new QVBoxLayout() ;

        QHBoxLayout* date_layout = new QHBoxLayout() ;
        date_layout->setSpacing(0) ;
        QLabel* begin_label = new QLabel("Begin", this)  ;
        date_layout->addWidget( begin_label );
        date_layout->addWidget(begin);

        QHBoxLayout* date_layout2 = new QHBoxLayout() ;
        QLabel* end_label = new QLabel("End", this)  ;
        date_layout2->addWidget( end_label );
        date_layout2->addWidget(end) ;

        layout->addWidget( project_name );
        layout->addLayout(date_layout) ;
        layout->addLayout(date_layout2) ;
        layout->addWidget(carrousel) ;
        layout->setAlignment(Qt::AlignTop);
        layout->setAlignment(Qt::AlignJustify);
        layout->addWidget(add_step_button) ;

        this->setLayout(layout) ;

        //load data
        this->reload() ;

        //change on the name of the project
        connect( project_name , &Text_picker::value_changed , this , [this](QString new_name){
            source->setName(new_name) ;
            update_database() ;
            notify_source_modified() ;
        } ) ;

        //change on date
        connect( begin, &Date_picker::value_changed , this, [this](QDate new_date){
            source->setBegin_date(new_date) ;
            update_database() ;
            notify_source_modified() ;
        } ) ;

        connect( end, &Date_picker::value_changed , this, [this](QDate new_date){
            source->setEnd_date(new_date) ;
            update_database() ;
            notify_source_modified() ;
        } ) ;

        //change on step
        connect( carrousel, &Carrousel::step_changed , this , [this](Step* s){
            //validate the step
            try{
                source->update_step(s) ;
                reload() ;
                //update the project view
                update_database() ;
                notify_source_modified() ;
            } catch ( ProjectException* e ) {
                s->rollback() ;
                QMessageBox m( QMessageBox::Warning ,"Error", e->get_message(), QMessageBox::Ok ) ;
                m.exec() ;
            }
        } ) ;

        //add step
        connect(add_step_button, &Icon_button::mousePressEvent, this, &Project_step_view::handle_step_creation) ;

    }
    ~Project_step_view(){}

    virtual void reload(){
        project_name->setText( source->getName() ) ;
        begin->set_date( source->getBegin_date() ) ;
        end->set_date( source->getEnd_date() ) ;

        //adding all steps to carrousel
        for(auto it = source->begin() ; it != source->end() ; it++){
            carrousel->reload( *it ) ;
        }
        carrousel->set_current( source->getCurrent() ) ;
    }

protected slots:
    virtual void handle_step_creation(QMouseEvent*) {
        Step_picker_view* p = new Step_picker_view() ;

        connect(p, &Step_picker_view::step_created, this, [this](Step* s){
               try {
                   source->add_step( s ) ;
                   carrousel->add( s );
                   add_database(*s) ;
                   reload() ;
                   notify_source_modified() ;
                } catch ( ProjectException* e ){
                   QMessageBox m( QMessageBox::Warning ,"Error", e->get_message(), QMessageBox::Ok ) ;
                   m.exec() ;
               }
        }) ;
        p->exec() ;
    }
};
#endif // PROJECT_STEP_VIEW_H
