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

     //all css
     static QString date_stylesheet ;
     static QString text_stylesheet_1 ;
     static QString text_stylesheet_2 ;
     static QString title_stylesheet ;
     static QString button_stylesheet ;
};


#endif // PARAMETERS_H
