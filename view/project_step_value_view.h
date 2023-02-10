#ifndef PROJECT_STEP_VALUE_VIEW_H
#define PROJECT_STEP_VALUE_VIEW_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "logic/project_step_value.h"
#include "view/checkpoint_view.h"
#include "components/text_picker.h"
#include "components/date_picker.h"
#include "components/carrousel.h"

class Project_step_value_view : public QWidget
{
    Q_OBJECT
private :
    Project_step_value *source ;
    Text_picker* project_name = new Text_picker() ;
    Date_picker* begin = new Date_picker() ;
    Date_picker* end = new Date_picker() ;
    Carrousel* carrousel = new Carrousel() ;
    void notify_source_modified() { emit source_modified(source) ; }

public :
    Project_step_value_view(QWidget* parent = nullptr) : QWidget(parent)
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
            auto c  =  dynamic_cast<Checkpoint*>(s) ;
            auto tmp = source->get_checkpoint() ;
            auto it = tmp.find(c) ;
            //we need to verify if he can really validate this stepwith a specific method
            (*it)->setIs_done( !((*it)->getIs_done()) );
            notify_source_modified() ;
        } ) ;
    }
    ~Project_step_value_view() {}
    void reload(){
        project_name->setText( source->getName() ) ;
        begin->set_date( source->getBegin_date() ) ;
        end->set_date( source->getEnd_date() ) ;
        carrousel->remove_all() ;

        //adding all steps to carrousel
        for(auto it = source->begin() ; it != source->end() ; it++){
            auto tmp = dynamic_cast<Checkpoint*>(*it) ; //it is not really a cast,
            carrousel->add( new Checkpoint_view(tmp) ) ;
        }
    }
signals :
    void source_modified(Project_step_value*) ;
};

#endif // PROJECT_STEP_VALUE_VIEW_H
