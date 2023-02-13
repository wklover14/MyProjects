#ifndef PROJECT_STEP_VIEW_H
#define PROJECT_STEP_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "components/text_picker.h"
#include "components/date_picker.h"
#include "components/carrousel.h"
#include "logic/project_step.h"
#include "view/a_project_view.h"


class Project_step_view : public A_project_view
{
    Q_OBJECT
    //this class provide a widget for a project with step only,
private :
    Project_step* source ;
    Text_picker* project_name = new Text_picker() ;
    Date_picker* begin = new Date_picker() ;
    Date_picker* end = new Date_picker() ;
    Carrousel* carrousel = new Carrousel() ;

    void notify_source_modified() { emit source_modified(source) ;   };
public:
    Project_step_view(Project_step* new_source,QWidget* parent = nullptr) : A_project_view(parent), source(new_source)
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
        layout->addWidget(carrousel) ;
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

        //change on step
        connect( carrousel, &Carrousel::step_changed , this , [this](Step* s){
            auto tmp = source->get_steps() ;
            auto it = tmp.find(s) ;
            //we need to verify if he can really validate this stepwith a specific method
            (*it)->setIs_done( !((*it)->getIs_done()) );
            notify_source_modified() ;
        } ) ;

    }
    ~Project_step_view(){}

    void reload(){
        project_name->setText( source->getName() ) ;
        begin->set_date( source->getBegin_date() ) ;
        end->set_date( source->getEnd_date() ) ;
        carrousel->remove_all() ;

        //adding all steps to carrousel
        for(auto it = source->begin() ; it != source->end() ; it++){
            carrousel->add( new Step_view(*it) ) ;
        }
    }
};

#endif // PROJECT_STEP_VIEW_H
