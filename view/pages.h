#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

#include "parameters.h"
#include "project_picker_view.h"

class Project_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* overview = new QLabel("Overview") ;
    QVBoxLayout* overview_layout = new QVBoxLayout() ;
    QVBoxLayout* categories_layout = new QVBoxLayout() ; //layout for adding category_view
    QLabel* detail = new QLabel("Detail") ;
    QVBoxLayout* detail_layout = new QVBoxLayout() ;

public :
    Project_page(QWidget* parent= nullptr) : QWidget(parent)
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
    } ;
    ~Project_page(){} ;
};

class Stat_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* stats = new QLabel("Stats");
public :
    Stat_page(QWidget* parent= nullptr) : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout();

        stats->setStyleSheet( Parameters::title_stylesheet );
        layout->addWidget(stats) ;
        this->setLayout(layout);
    } ;
    ~Stat_page(){} ;
};

class Add_project_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* add_page = new QLabel("Add Project");
    Project_picker_view* picker = new Project_picker_view() ;
public :
    Add_project_page(QWidget* parent= nullptr) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        add_page->setStyleSheet( Parameters::title_stylesheet );
        layout->addWidget(add_page);
        layout->addWidget( picker );
        this->setLayout(layout);
    } ;
    ~Add_project_page(){} ;
};


#endif // PAGES_H
