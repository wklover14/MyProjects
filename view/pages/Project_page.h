#ifndef PROJECT_PAGE_H
#define PROJECT_PAGE_H

#include <list>

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

#include "parameters.h"
#include "logic/category.h"
#include "view/category_view.h"

#include "database/category_db.h"
#include "database/project_step_db.h"

class Project_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* overview = new QLabel("Overview") ;
    QVBoxLayout* overview_layout = new QVBoxLayout() ;
    QVBoxLayout* categories_layout = new QVBoxLayout() ; //layout for adding category_view
    QLabel* detail = new QLabel("Detail") ;
    QVBoxLayout* detail_layout = new QVBoxLayout() ;
    QWidget* current = nullptr ; //the widget in the detail_layout


public :    
    Project_page(QWidget *parent= nullptr) : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout();

        overview->setStyleSheet( Parameters::title_stylesheet ) ;
        overview->setAlignment(Qt::AlignCenter) ;
        detail->setStyleSheet( Parameters::title_stylesheet ) ;
        detail->setAlignment( Qt::AlignCenter ) ;
        overview_layout->addWidget(overview) ;
        detail_layout->addWidget(detail);

        //OVERVIEW

        //create scroll
        QWidget* categories_scroll = new QWidget(this) ;
        categories_scroll->setLayout( categories_layout );
        QScrollArea* scroll = new QScrollArea() ;
        scroll->setWidget(categories_scroll) ;
        scroll->setFrameShape(QFrame::NoFrame) ; //
        scroll->setWidgetResizable(true);
        scroll->setMaximumWidth(Parameters::carrousel_width) ;
        overview_layout->addWidget( scroll ) ;

        // DETAIL
        detail_layout->setAlignment(Qt::AlignTop);

        layout->addLayout(overview_layout) ;
        layout->addLayout( detail_layout ) ;
        this->setAcceptDrops(true) ;
        this->setLayout( layout ) ;
    }

    ~Project_page(){}

    void add_category(Category *c){
        categories_layout->addWidget( c->widget() ) ;
    }

    void remove_categories(Category *c) {
        categories_layout->removeWidget(c->widget()) ;
    }

    void set_current_project(A_project *a){
        if( current != nullptr ){
            detail_layout->removeWidget( current );
            current->hide() ;
        }
        detail_layout->addWidget( a->widget() );
        current = a->widget() ;
        current->show();
    }

    void get_data_from_database() {
        //get all categories
        list<Category*>* lst_categories ;
        Category_db category_db ;
        Project_step_db project_step_db ;

        lst_categories = category_db.fetch() ;

        //get all_project
        for(auto category : *lst_categories ){
            //looking for projects_steps, we need to exclude value referenced by a project_step_value
            list<Project_step*>* projects ;
            projects = project_step_db.fetch_all_for_category(category->getId_category() ) ;

            for(auto project : *projects ){
                category->add_project(project) ;
            }
            //looking for projects_value

            //looking for projects_steps_value
            //we need to replace value referenced by a project_step_value

            //we add the category to the page
            add_category( category ) ;

            //connection for the category
            Category_view* tmp = dynamic_cast<Category_view*>( category->widget() ) ;
            connect( tmp, &Category_view::project_selected, this, [this](A_project* a){
                this->set_current_project(a);
            }) ;
        }
    }

};

#endif // PROJECT_PAGE_H

