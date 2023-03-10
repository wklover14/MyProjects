#include "checkpoint.h"
#include "view/checkpoint_view.h"

Checkpoint::Checkpoint(QDate d,QString comment ,int value): Step(d, comment), value(value)
{

}

Checkpoint::~Checkpoint(){

}

void Checkpoint::rollback() {
    Step::rollback() ;
    dynamic_cast<Checkpoint_view*>( widget() )->reload() ;
}

QWidget* Checkpoint::widget() {
    if( source == nullptr ){
        source = new Checkpoint_view(this) ;
    }
    return source ;
}

//getters only

int Checkpoint::getValue() const
{
    return value;
}

