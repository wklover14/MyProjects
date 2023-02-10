#ifndef CATEGORY_VIEW_H
#define CATEGORY_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <list>
#include <QInputDialog>

#include "view/project_view.h"
#include "logic/category.h"
#include "parameters.h"
#include "components/color_picker.h"
#include "components/text_picker.h"

using namespace std ;

class Category_view : public QWidget, private list<Project_view*>
{
    Q_OBJECT
private:
    Text_picker* label = new Text_picker();
    Category* source ;
    Color_picker* color_picker = new Color_picker() ;
    QVBoxLayout* layout = new QVBoxLayout();

    void operator=(const Category_view& ) {} ; //

public:
    explicit Category_view( Category* c, QWidget* parent = nullptr): QWidget(parent), list<Project_view*>(),
        source( c )
    {
        QHBoxLayout* name_Layout = new QHBoxLayout();
        name_Layout->addWidget(label);
        name_Layout->addStretch() ;
        name_Layout->addWidget(color_picker);
        name_Layout->setContentsMargins(0,0,0,0) ;

        layout->addLayout(name_Layout);
        layout->setSpacing( 5 );
        layout->setAlignment(Qt::AlignTop);
        this->setLayout(layout);
        this->setMaximumWidth( Parameters::category_width  ) ;

        connect( color_picker, &Color_picker::color_change, this, &Category_view::update_color ) ;

        label->setText(c->getName()) ;
        label->setStyleSheet(Parameters::text_stylesheet_1);
        label->setAcceptDrops(true) ;

        connect( label, &Text_picker::value_changed, this, [this](QString new_value){
            this->source->setName(new_value) ;
        } ) ;

        //add all the projects
        for( auto it : c->get_project() )
        {
            add_project(it);
        }
        update_color(c->getColor()) ;
    }
    ~Category_view(){}
    void add_project(A_project* p) {
        //if( list<A_project*>::count == 0 )
        Project_view* view_p = new Project_view(p) ;
        list<Project_view*>::push_back(view_p) ;
        layout->addWidget(view_p);

        connect( view_p, &Project_view::mousePressEvent, this, [this, p](QMouseEvent* event){
             emit project_selected(p); //notify that this project is selected
            if( event != nullptr ) event->pos() ;
        } ) ;
    }
    void remove_project(A_project* p){
        for(auto it = list<Project_view*>::begin() ; it != list<Project_view*>::end(); it++ ){
            if( (*it)->get_project() == p ){
                list<Project_view*>::remove(*it) ;
                break ;
            }
        }
    }

    void reload(){
        for(auto it= list<Project_view*>::begin() ; it != list<Project_view*>::end() ; it++){
            (*it)->reload() ;
        }
    }


private slots :
    void update_color(QColor c) {
        for( auto it = list<Project_view*>::begin() ; it != list<Project_view*>::end() ; it++ )
        {
            (*it)->setColor(c);
            source->setColor(c.name()) ; //change color
        }
    }

signals:
    void project_selected(A_project*) ;
};

#endif // CATEGORY_VIEW_H
