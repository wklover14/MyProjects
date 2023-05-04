#include "step.h"
#include "view/step_view.h"

Step::Step(QDate d, QString comment): date(d), is_done(false), comment(comment)
{
}

Step::~Step(){

}

void Step::rollback() {
    //this method unchange the previous changes
    is_done = !is_done ;
    dynamic_cast<Step_view*>( widget() )->reload() ;
}

const QDate &Step::getDate() const
{
    return date;
}

void Step::setDate(const QDate &newDate)
{
    date = newDate;
}

bool Step::getIs_done() const
{
    return is_done;
}

void Step::setIs_done(bool newIs_done)
{
    is_done = newIs_done;
}

const QString &Step::getComment() const
{
    return comment;
}

void Step::setComment(const QString &newComment)
{
    comment = newComment;
}

QWidget* Step::widget() {
    if( source == nullptr ){
        source = new Step_view(this) ;
    }
    return source ;
}

int Step::getId_step() const
{
    return id_step;
}

void Step::setId_step(int newId_step)
{
    id_step = newId_step;
}
