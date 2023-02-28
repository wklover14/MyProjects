#ifndef CHECKPOINT_VIEW_H
#define CHECKPOINT_VIEW_H

#include "step_view.h"
#include "logic/checkpoint.h"

class Checkpoint ;
class Checkpoint_view : public Step_view
{
private:
    QLabel* value = new QLabel() ;

public:
    Checkpoint_view(Checkpoint* new_source, QWidget* parent= nullptr): Step_view(new_source, parent)
    {
        value->setText(  QString::number(new_source->getValue())  );
        Step_view::more_layout->addWidget( value );
    }
    ~Checkpoint_view(){}
    QLabel *getValue() const;
    void setValue(QLabel *newValue);
};

inline QLabel *Checkpoint_view::getValue() const
{
    return value;
}

inline void Checkpoint_view::setValue(QLabel *newValue)
{
    value = newValue;
}

#endif // CHECKPOINT_VIEW_H
