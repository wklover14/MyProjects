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
};


#endif // PARAMETERS_H
