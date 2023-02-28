#ifndef CHECKPOINT_PICKER_VIEW_H
#define CHECKPOINT_PICKER_VIEW_H

#include "logic/checkpoint.h"
#include "view/step_picker_view.h"

#include <QTextEdit>
#include <QMessageBox>

class Checkpoint_picker_view : public Step_picker_view
{
    Q_OBJECT
private :
    QTextEdit* value = new QTextEdit() ;

public :
    Checkpoint_picker_view(QWidget* parent = nullptr ) : Step_picker_view(parent)  {
        Step_picker_view::add_widget( value ) ;

        //connect
        connect( Step_picker_view::okButton, &QPushButton::released, this , [this](){
            //check if the value button is integer
            bool convertion_ok = true ;
            int new_status = value->toPlainText().toInt( &convertion_ok ) ;
            if( ! convertion_ok ) {
                QMessageBox  m(QMessageBox::Warning, "Wrong Value", "wrong value", QMessageBox::Ok) ;
                m.exec() ;
                return ;
            }
            Checkpoint* ch = new Checkpoint( date->get_date(), comment->toPlainText() , new_status ) ;
            emit step_created(ch) ;
        } ) ;
    }
    ~Checkpoint_picker_view() {};

signals :
    void checkpoint_created(Checkpoint*) ;
};

#endif // CHECKPOINT_PICKER_VIEW_H
