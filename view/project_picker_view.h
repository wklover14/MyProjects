#ifndef PROJECT_PICKER_VIEW_H
#define PROJECT_PICKER_VIEW_H

#include <list>
#include <map>

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
#include <QComboBox>

#include "components/date_picker.h"
#include "parameters.h"
#include "logic/project_step.h"
#include "logic/project_value.h"
#include "logic/project_step_value.h"
#include "logic/projectException.h"

#include "database/project_step_db.h"
#include "database/category_db.h"

class Project_picker_view : public QWidget
{
    Q_OBJECT
private:
    QTextEdit* project_name = new QTextEdit() ;
    QSpinBox* priority_selector = new QSpinBox() ;
    QSpinBox* total_value_selector = new QSpinBox() ;
    QPlainTextEdit* description = new QPlainTextEdit() ;
    QCheckBox* is_value = new QCheckBox("Project with value") ;
    QCheckBox* is_step = new QCheckBox("Adding step") ;
    QPushButton* ok_button = new QPushButton("Add") ;
    QPushButton* clear_button = new QPushButton("Clear") ;
    Date_picker* begin = new Date_picker(this), *end = new Date_picker(this);
    QComboBox* categories_cmb = new QComboBox() ;
    map<QString, int> map_name_id ;  //
    QVBoxLayout* layout = new QVBoxLayout() ;

public:
    Project_picker_view(QWidget* parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout() ;

        //stylesheet
        project_name->setStyleSheet(Parameters::text_edit_stylesheet) ;
        priority_selector->setStyleSheet(Parameters::text_edit_stylesheet) ;
        total_value_selector->setStyleSheet(Parameters::text_edit_stylesheet) ;
        description->setStyleSheet(Parameters::text_plain_edit_stylesheet) ;
        is_step->setStyleSheet(Parameters::text_stylesheet_1) ;
        is_value->setStyleSheet(Parameters::text_stylesheet_1) ;

        priority_selector->setRange(0, 10) ;
        total_value_selector->setRange(10, 1000) ;
        total_value_selector->setSingleStep(10) ;
        begin->set_date(QDate::currentDate()) ; end->set_date(QDate::currentDate()) ;


        //init all the categories
        Category_db cat_db ;
        list<Category*>* categories = cat_db.fetch() ;
        for( auto category : *categories ) {
            categories_cmb->addItem( category->getName() ) ;
            map_name_id[category->getName()] = category->getId_category() ;
        }

        //layout creation and adding item
        layout->addLayout( add_label_plus_item("Name ", project_name) ) ;
        layout->addLayout( add_label_plus_item("Category ", categories_cmb )) ;
        layout->addLayout( add_label_plus_item("Priority ", priority_selector) ) ;

        QHBoxLayout* date_layout = new QHBoxLayout() ;
        add_label_plus_item("Begin date :", begin, date_layout ) ;
        add_label_plus_item("End date :", end, date_layout ) ;
        layout->addLayout( date_layout ) ;

        QHBoxLayout* value_layout = new QHBoxLayout() ;
        value_layout->addWidget(is_value) ;
        add_label_plus_item("Value :", total_value_selector, value_layout) ;
        layout->addLayout(value_layout) ;

        QHBoxLayout* step_layout = new QHBoxLayout() ;
        value_layout->addWidget(is_step) ;
        layout->addLayout(step_layout) ;

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
    QHBoxLayout* add_label_plus_item(QString name, QWidget* widget, QHBoxLayout* alternative_layout = nullptr ) {
        //this method create a QHboxLayout and add a qlabel with the name and the wodget inside
        QHBoxLayout* name_layout = new QHBoxLayout() ;
        QLabel* tmp = new QLabel(name) ;
        tmp->setStyleSheet(Parameters::text_stylesheet_1) ;
        name_layout->setAlignment(Qt::AlignLeft) ;
        tmp->setMaximumWidth( Parameters::label_width ) ;
        name_layout->addWidget(tmp) ;
        name_layout->addWidget(widget);
        if( alternative_layout == nullptr ){
            return name_layout ;
        } else {
            alternative_layout->addLayout(name_layout) ;
            return alternative_layout ;
        }
    }

    void handle_creation() {
        //fetch data
        QString name = project_name->toPlainText() ;
        QString des = description->toPlainText() ;
        int category_id =  map_name_id[ categories_cmb->itemText(categories_cmb->currentIndex()) ] ;
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

        if( !is_value->isChecked() && !is_step->isChecked() ){
            error += "you must select a project with value, or with steps or both \n" ;
        }

        if( error != ""){
            QMessageBox m( QMessageBox::Warning ,"Error", error, QMessageBox::Ok ) ;
            m.exec() ;
            return ;
        }

        //create the project
        if( is_value->isChecked() && is_step->isChecked() ){
            //a project step with value
            Project_step_value* p = new Project_step_value(name, pr) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setId_category( category_id ) ;
            p->setDescription( des ) ;
            emit project_created(p) ;
        } else if( is_value->isChecked() ){
            //project with value
            Project_value* p = new Project_value(name, pr, total_value, 0 ) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setId_category( category_id ) ;
            p->setDescription( des );
            emit project_created(p) ;
        } else {
            //project with step only
            Project_step* p = new Project_step(name, pr) ;
            p->setBegin_date( begin->get_date() );
            p->setEnd_date( end->get_date()  ) ;
            p->setId_category( category_id ) ;
            p->setDescription( des );

            //add to the database
            Project_step_db p_db;
            try {
                p_db.insert(*p, p->getId_category() ) ; //0 for the default project
            } catch(ProjectException* e){
                qDebug() << e->get_message() ;
            }

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
        is_step->setChecked(false) ;
        categories_cmb->setCurrentIndex(0) ;
        begin->set_date(QDate::currentDate()) ;
        end->set_date(QDate::currentDate()) ;

        //re-init all the categories
        Category_db cat_db ;
        list<Category*>* categories = cat_db.fetch() ;
        for( auto category : *categories ) {
            categories_cmb->addItem( category->getName() ) ;
            map_name_id[category->getName()] = category->getId_category() ;
        }
    }
};

#endif // PROJECT_PICKER_VIEW_H
