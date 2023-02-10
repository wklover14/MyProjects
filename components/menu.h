#ifndef MENU_H
#define MENU_H

#include "components/menu_item.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>

class Menu : public QWidget
{
    Q_OBJECT
private :
    Item_menu* option1 = new Item_menu("../MyProjects/images/calendar.png","My projects") ;
    Item_menu* option2 = new Item_menu("../MyProjects/images/number.png","My stats");
    Item_menu* option3 = new Item_menu("../MyProjects/images/plus.png","add projects");

    Item_menu* users = new Item_menu("../MyProjects/images/user.png","user");
    int selected_option = 1 ;

public :
   explicit Menu(QWidget* parent = nullptr):QWidget(parent)
    {
        QVBoxLayout* item_layout = new QVBoxLayout() ;
        item_layout->addWidget(option1);
        item_layout->addWidget(option2);
        item_layout->addWidget(option3);
        users->toggle_active() ;

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addLayout(item_layout) ;
        layout->addStretch() ;
        layout->addWidget(users) ;
        layout->setAlignment(Qt::AlignBaseline) ;

        this->setLayout(layout) ;
        option1->toggle_active(); //the initial option
        connect(option1 , &Item_menu::mousePressEvent, this, [this](QMouseEvent*){
            option1->toggle_active() ;
            switch_selected_item() ;
            emit selected_item(1) ;
        }) ;
        connect(option2 , &Item_menu::mousePressEvent, this, [this](QMouseEvent*){
            option2->toggle_active() ;
            switch_selected_item() ;
            emit selected_item(2) ;
        }) ;
        connect(option3 , &Item_menu::mousePressEvent, this,[this](QMouseEvent*){
            option3->toggle_active() ;
            switch_selected_item() ;
            emit selected_item(3) ;
        }) ;
        connect(this, &Menu::selected_item, this, [this](int number){ selected_option = number; }) ;
    }
    ~Menu(){};
    void switch_selected_item(){
        switch(selected_option) {
            case 1 : option1->toggle_active() ;
                     break ;
            case 2 : option2->toggle_active() ;
                    break;
            case 3 : option3->toggle_active();
                    break ;
        }
    }

signals :
    void selected_item(int number);//this signal will be emit when a item is selected


};

#endif // MENU_H
