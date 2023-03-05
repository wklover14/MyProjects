#ifndef STEP_PICKER_VIEW_H
#define STEP_PICKER_VIEW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

#include "components/date_picker.h"
#include "logic/step.h"
#include "parameters.h"

class Step_picker_view : public QDialog
{
    Q_OBJECT
    bool is_inherited = false ;
protected :
    QPlainTextEdit* comment = new QPlainTextEdit() ;
    Date_picker* date = new Date_picker() ;
    QPushButton *okButton = new QPushButton("OK");
    QHBoxLayout* add_layout = new QHBoxLayout() ; //in order to add other field for inherited classes

    void add_widget(QWidget* item) {
        //this function allow to all the inheritted class to add a widget to the father
        add_layout->addWidget(item) ;
        is_inherited = true ;
    }

public:
    Step_picker_view(QWidget* parent = nullptr) : QDialog(parent){
        this->setWindowTitle("Create new Step") ;
        date->set_date(QDate::currentDate()) ;
        comment->setStyleSheet(Parameters::text_plain_edit_stylesheet) ;
        QVBoxLayout* layout = new QVBoxLayout(this) ;

        QLabel* tmp = new QLabel("Select the Date : ") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_2) ;
        QHBoxLayout* date_layout = new QHBoxLayout() ;
        date_layout->addWidget( tmp ) ;
        date_layout->addWidget( date ) ;
        date_layout->setSpacing( 10 );
        date_layout->setAlignment(Qt::AlignLeft) ;
        layout->addLayout(date_layout) ;

        QLabel* des_label = new QLabel("Description : ") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_2) ;
        QHBoxLayout* comment_layout = new QHBoxLayout() ;
        comment_layout->addWidget( des_label ) ;
        comment_layout->addWidget( comment ) ;
        comment_layout->setSpacing( 10 );
        comment_layout->setAlignment(Qt::AlignLeft) ;
        layout->addLayout(comment_layout) ;

        layout->addLayout(add_layout) ;

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QPushButton *cancelButton = new QPushButton("Annuler");
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addLayout(buttonLayout) ;

        this->setLayout(layout) ;
        resize(200,200) ;

        connect( okButton, &QPushButton::released, this,
                [this](){
                    if( !is_inherited )
                    {
                        //if this layout is empty, it must be a inheritted class, wich will emit the signal,
                        Step* step = new Step( date->get_date(), comment->toPlainText() );
                        //send a signal to notify that there is a new value
                        emit this->step_created(step) ;
                    }

                    close() ;
                } ) ;

        connect(cancelButton, &QPushButton::released, this, &Step_picker_view::close ) ;
    }
    virtual ~Step_picker_view(){}

signals:
    void step_created(Step*) ;
};

#endif // STEP_PICKER_VIEW_H
