#ifndef PROJECT_STEP_VALUE_VIEW_H
#define PROJECT_STEP_VALUE_VIEW_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "logic/project_step_value.h"
#include "components/text_picker.h"
#include "components/date_picker.h"
#include "components/carrousel.h"
#include "view/project_step_view.h"

class Project_step_value_view : public Project_step_view
{
    Q_OBJECT
protected :
    Project_step_value* source ;

public :
    Project_step_value_view(Project_step_value* new_source ,QWidget* parent = nullptr) : Project_step_view(new_source, parent), source(new_source)
    {
        //change on checkpoints
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
    void reload() override {
        project_name->setText( source->getName() ) ;
        begin->set_date( source->getBegin_date() ) ;
        end->set_date( source->getEnd_date() ) ;
        carrousel->remove_all() ;

        //adding all steps to carrousel
        for(auto it = source->begin() ; it != source->end() ; it++){
            auto tmp = dynamic_cast<Checkpoint*>(*it) ; //it is not really a cast,
            carrousel->add( tmp ) ;
        }
    }
};

#endif // PROJECT_STEP_VALUE_VIEW_H
