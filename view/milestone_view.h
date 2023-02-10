#ifndef MILESTONE_VIEW_H
#define MILESTONE_VIEW_H

#include "step_view.h"
#include "logic/milestone.h"

class Milestone_view : public Step_view
{
private :
    QLabel* comment = new QLabel() ;

public:
    Milestone_view(Milestone* new_source, QWidget* parent = nullptr): Step_view(new_source, parent)
    {
        comment->setText( new_source->getComment() ) ;
        Step_view::more_layout->addWidget( comment )  ;
    }
    ~Milestone_view() {};
};

#endif // MILESTONE_VIEW_H
