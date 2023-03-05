#ifndef PROJECT_STEP_VALUE_VIEW_H
#define PROJECT_STEP_VALUE_VIEW_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "logic/project_step_value.h"
#include "view/project_step_view.h"
#include "view/Checkpoint_picker_view.h"

class Project_step_value_view : public Project_step_view
{
    Q_OBJECT
protected :
    Project_step_value* source ;

public :
    Project_step_value_view(Project_step_value* new_source ,QWidget* parent = nullptr) : Project_step_view(new_source, parent), source(new_source)
    {

    }
    ~Project_step_value_view() {}
protected slots :
    void handle_step_creation(QMouseEvent* ) override { // redefine the behavior in order to use checkpoint_picker_view instead of step_picker_view
        Checkpoint_picker_view* p = new Checkpoint_picker_view() ;
        connect(p, &Checkpoint_picker_view::checkpoint_created, this, [this](Checkpoint* s){
               try {
                   source->add_Checkpoint( s ) ;
                   carrousel->add( s ) ;
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

#endif // PROJECT_STEP_VALUE_VIEW_H
