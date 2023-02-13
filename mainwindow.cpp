#include <QHBoxLayout>
#include <QWidget>

#include "view/pages.h"
#include "logic/category.h"
#include "view/category_view.h"
#include "mainwindow.h"
#include "parameters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //init
    Category* c_defaut = new Category("Default", Parameters::hexa_code_colors[COLORS::quartz]) ;
    Project_page* page1 = new Project_page( ) ;
    Stat_page* page2 = new Stat_page() ;
    Add_project_page* page3 = new Add_project_page() ;

    pages->addWidget(page1);
    pages->addWidget(page2);
    pages->addWidget(page3);
    pages->setCurrentWidget(page1);

    page1->add_category(c_defaut) ;

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

    //handle creation of a new project
    connect( page3, &Add_project_page::project_created ,this , [c_defaut](A_project* a){
        //by default there is always a category name "c_defaut",
        c_defaut->add_project(a) ;
    }) ;

    //binding categories with their
    Category_view* tmp = dynamic_cast<Category_view*>( c_defaut->widget() ) ;
    connect( tmp, &Category_view::project_selected, this, [page1](A_project* a){
        page1->set_current_project(a);
    }) ;

}

MainWindow::~MainWindow()
{
}

