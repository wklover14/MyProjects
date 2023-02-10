#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>
#include <map>
#include <list>
#include <QString>

using namespace std ;

enum COLORS {
    salmon, casablanca, lavender, quartz, purple_Mountains_majesty, light_white
} ;


class Parameters{
public:
     static map<int, QString> hexa_code_colors ;
     static map<int, QString> colors_name ;
     static int color_shape_weight  ;
     static int color_shape_height ;
     static int milestone_width ;
     static int milestone_height ;
     static int carrousel_width ;
     static int carrousel_height ;
     static int arrow_width ;
     static int arrow_height ;
     static int item_width ;
     static int item_height ;
     static int icon_width ;
     static int icon_height ;
     static int category_width ;
     static int label_width ;

     //all css
     static QString date_stylesheet ;
     static QString text_stylesheet_1 ;
     static QString text_stylesheet_2 ;
     static QString title_stylesheet ;
     static QString button_stylesheet ;
     static QString underline_stylesheet ;
     static QString icon_stylesheet ;
     static QString carrousel_stylesheet ;
     static QString milestone_stylesheet ;
     static QString text_edit_stylesheet ;
     static QString text_plain_edit_stylesheet ;

};


#endif // PARAMETERS_H
