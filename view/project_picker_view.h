#ifndef PROJECT_PICKER_VIEW_H
#define PROJECT_PICKER_VIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "components/date_picker.h"
#include "parameters.h"
#include "logic/project_step.h"
#include "logic/project_value.h"
#include "logic/project_step_value.h"

class Project_picker_view : public QWidget
{
    Q_OBJECT
private:
    QTextEdit* project_name = new QTextEdit() ;
    QSpinBox* priority_selector = new QSpinBox() ;
    QSpinBox* total_value_selector = new QSpinBox() ;
    QPlainTextEdit* description = new QPlainTextEdit() ;
    QCheckBox* is_value = new QCheckBox("Project with value") ;
    QCheckBox* checkpoint = new QCheckBox("Adding step") ;
    QPushButton* ok_button = new QPushButton("Add") ;
    QPushButton* clear_button = new QPushButton("Clear") ;
    Date_picker* begin = new Date_picker(this), *end = new Date_picker(this);

public:
    Project_picker_view(QWidget* parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout() ;

        //stylesheet
        project_name->setStyleSheet(Parameters::text_edit_stylesheet) ;
        priority_selector->setStyleSheet(Parameters::text_edit_stylesheet) ;
        total_value_selector->setStyleSheet(Parameters::text_edit_stylesheet) ;
        description->setStyleSheet(Parameters::text_plain_edit_stylesheet) ;
        checkpoint->setStyleSheet(Parameters::text_stylesheet_1) ;
        is_value->setStyleSheet(Parameters::text_stylesheet_1) ;

        priority_selector->setRange(0, 10) ;
        total_value_selector->setRange(10, 1000) ;
        total_value_selector->setSingleStep(10) ;
        begin->set_date(QDate::currentDate()) ; end->set_date(QDate::currentDate()) ;

        //layout creation and adding item
        QHBoxLayout* name_layout = new QHBoxLayout() ;
        QLabel* tmp = new QLabel("Project Name") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        name_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        name_layout->addWidget(tmp) ;
        name_layout->addWidget(project_name);
        layout->addLayout(name_layout) ;

        QHBoxLayout* priority_selector_layout = new QHBoxLayout() ;
        tmp = new QLabel("priority_selector ") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        priority_selector_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        priority_selector_layout->addWidget(tmp) ;
        priority_selector_layout->addWidget(priority_selector);
        layout->addLayout(priority_selector_layout) ;

        QHBoxLayout* date_layout = new QHBoxLayout() ;
        tmp = new QLabel("Begin") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        date_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        date_layout->addWidget(tmp) ;
        date_layout->addWidget(begin);
        tmp = new QLabel("End") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        date_layout->addWidget(tmp) ;
        date_layout->addWidget(end);
        layout->addLayout(date_layout) ;

        QHBoxLayout* description_layout = new QHBoxLayout() ;
        tmp = new QLabel("Description ") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        description_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        description_layout->addWidget(tmp) ;
        description_layout->addWidget(description);
        layout->addLayout( description_layout ) ;

        QHBoxLayout* value_layout = new QHBoxLayout() ;
        tmp = new QLabel("Total value : ") ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        value_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        value_layout->addWidget(is_value) ;
        value_layout->addWidget(tmp) ;
        value_layout->addWidget(total_value_selector);
        layout->addLayout(value_layout) ;

        QHBoxLayout* checkpoint_layout = new QHBoxLayout() ;
        checkpoint_layout->setAlignment(Qt::AlignLeft) ;
        checkpoint_layout->addWidget(checkpoint) ;
        layout->addLayout(checkpoint_layout) ;

        QHBoxLayout* button_layout = new QHBoxLayout();
        button_layout->addWidget(ok_button)  ;
        button_layout->addStretch();
        button_layout->addWidget(clear_button) ;
        layout->addLayout(button_layout) ;


        //connect
        //if there is no value we hide the text input for the value
        connect( is_value, &QCheckBox::clicked, this , [this](bool value){
            if( value ){
                total_value_selector->show();
            } else {
                total_value_selector->hide() ;
            }
        } ) ;

        connect( ok_button , &QPushButton::released , this, &Project_picker_view::handle_creation );
        connect( clear_button, &QPushButton::released, this, &Project_picker_view::clear );

        //init
        this->setLayout(layout) ;
    } ;
    ~Project_picker_view(){}

signals :
    void project_created(A_project* a) ;

private slots :
    void handle_creation() {
        //fetch data
        QString name = project_name->toPlainText() ;
        QString des = description->toPlainText() ;
        int pr = priority_selector->value()  ;
        int total_value = total_value_selector->value() ;

        QString error = "" ;
        //check the data
        if( name.isEmpty() || name.size()  >= 20 ){
            error += "Name can't be empty or exceed 20 characters \n" ;
        }
        if( !name.contains(QRegularExpression("[A-Za-z0-9]")) ){
            error+="Name must contains an aphabetical character \n" ;
        }
        if( end->get_date() < QDate::currentDate() ) {
            error += "End date can't be before today / you can't add completed projects\n" ;
        }
        if( end->get_date() <= begin->get_date() ){
            error += "Begin date can't be after end date \n" ;
        }

        if( !is_value->isChecked() && !checkpoint->isChecked() ){
            error += "you must select a project with value, or with steps or both \n" ;
        }

        if( error != ""){
            QMessageBox m( QMessageBox::Warning ,"Error", error, QMessageBox::Ok ) ;
            m.exec() ;
            return ;
        }

        //create the project
        if( is_value->isChecked() && checkpoint->isChecked() ){
            //a project step with value
            Project_step_value* p = new Project_step_value(name, pr) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setDescription( des );
            emit project_created(p) ;
        } else if( is_value->isChecked() ){
            //project with value
            Project_value* p = new Project_value(name, pr, total_value, 0 ) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setDescription( des );
            emit project_created(p) ;
        } else {
            //project with step only
            Project_step* p = new Project_step(name, pr) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setDescription( des );
            emit project_created(p) ;
        }
        clear() ;
    }
    void clear() {
        project_name->setText("") ;
        priority_selector->setValue(0) ;
        total_value_selector->setValue(100) ;
        description->clear() ;
        is_value->setChecked(false) ;
        checkpoint->setChecked(false) ;
        begin->set_date(QDate::currentDate()) ;
        end->set_date(QDate::currentDate()) ;
    }
};

#endif // PROJECT_PICKER_VIEW_H
