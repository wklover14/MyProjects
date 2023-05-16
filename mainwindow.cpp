#include <QHBoxLayout>
#include <QWidget>

#include "mainwindow.h"

#include "database/connexion_db.h"
#include "view/pages/Add_page.h"
#include "view/pages/Project_page.h"
#include "view/pages/Stat_page.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //init
    connexion_db::init_connexion("gabby", "gabby");

    Project_page* page1 = new Project_page( ) ;
    Stat_page* page2 = new Stat_page() ;
    Add_project_page* page3 = new Add_project_page() ;

    //fetching data
    page1->get_data_from_database() ;

    pages->addWidget(page1);
    pages->addWidget(page2);
    pages->addWidget(page3);
    pages->setCurrentWidget(page1);


    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m);
    layout->addWidget(pages);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(layout) ;
    this->setCentralWidget(centralWidget);

    connect(m, &Menu::selected_item, pages,[this,page1,page2,page3](int number){
        switch(number){
            case 1 : pages->setCurrentWidget(page1);
                     break ;
            case 2 : pages->setCurrentWidget(page2);
                     break ;
            case 3 : pages->setCurrentWidget(page3);
                     break;
        }
    }) ;

    connect( page3, &Add_project_page::project_created ,this , [page1](A_project* a){
        //by default there is always a category name "c_defaut",
        page1->set_current_project(a) ;
    }) ;
}

MainWindow::~MainWindow()
{
}

