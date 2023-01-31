#include "parameters.h"

map<int, QString> Parameters::hexa_code_colors = {
    { COLORS::salmon , "#FC7869"},
    { COLORS::casablanca , "#F5AE52"},
    { COLORS::lavender, "#F7E7FB" },
    { COLORS::quartz, "#E0C2F2"},
    { COLORS::purple_Mountains_majesty, "#A478B8"},
    { COLORS::light_white, "#F5F5F5"}
};

map<int, QString> Parameters::colors_name = {
    { COLORS::salmon , "salmon"},
    { COLORS::casablanca , "casablanca"},
    { COLORS::lavender, "lavender" },
    { COLORS::quartz, "quartz"},
    { COLORS::purple_Mountains_majesty, "purple_Mountains_majesty"},
    { COLORS::light_white, "light_white"}
};

int Parameters::color_shape_weight = 24 ;
int Parameters::color_shape_height = 24 ;
int Parameters::milestone_width = 277 ;
int Parameters::milestone_height = 84 ;

QString Parameters::date_stylesheet =  "width: 127px;"
        "height: 34px;"
        "font-family: Arial;"
        "font-size: 20px;"
        "color: #000000;"
        "font-style: italic;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;"  ;
QString Parameters::text_stylesheet_1 = "width: 203px;"
        "height: 32px;"
        "font-family: Arial;"
        "font-size: 20px;"
        "color: #000000;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;" ;
QString Parameters::text_stylesheet_2 = "width: 203px;"
        "height: 32px;"
        "font-family: Arial;"
        "font-size: 18px;"
        "color: #000000;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;" ;
QString Parameters::button_stylesheet = "max-width: 147px;"
        "max-height: 19px;"
        "background-color: #121212;"
        "font-family: Arial;"
        "font-size: 16px;"
        "color: #ffffff;"
        "font-style: italic;"
        "text-decoration: none solid rgb(255, 255, 255);"
        "text-align: center;" ;
        //"background-size: cover;"
QString Parameters::title_stylesheet = "width: 315px;"
        "height: 37px;"
        "font-family: Ubuntu;"
        "font-size: 24px;"
        "color: #000000;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;"
        "text-align: center;" ;
