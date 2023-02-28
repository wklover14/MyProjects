#include "parameters.h"

map<int, QString> Parameters::hexa_code_colors = {
    { COLORS::salmon , "#FC7869" },
    { COLORS::casablanca , "#F5AE52" },
    { COLORS::lavender, "#F7E7FB" },
    { COLORS::quartz, "#E0C2F2" },
    { COLORS::purple_Mountains_majesty, "#A478B8" },
    { COLORS::light_white, "#F5F5F5" }
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
int Parameters::milestone_height = 200 ;
int Parameters::carrousel_width = 407 ;
int Parameters::carrousel_height = 150 ;
int Parameters::arrow_width = 41 ;
int Parameters::arrow_height = 38 ;
int Parameters::item_width = 257 ;
int Parameters::item_height = 55 ;
int Parameters::icon_width = 46 ;
int Parameters::icon_height = 42 ;
int Parameters::category_width = 400 ;
int Parameters::label_width = 170 ;


QString Parameters::date_stylesheet =  "width: 127px;"
        "height: 34px;"
        "font-family: Arial;"
        "font-size: 14px;"
        "text-align: center;"
        "color: #000000;"
        "font-style: italic;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;"  ;
QString Parameters::text_stylesheet_1 = "font-family: Arial;"
        "font-size: 16px;"
        "color: #000000;"
        "text-decoration: none solid rgb(0, 0, 0);"
        "letter-spacing: 2px;";
QString Parameters::text_stylesheet_2 = "font-family: Arial;"
        "font-size: 14px;"
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
        "text-align: center;"
        "margin-bottom: 10px";
QString Parameters::underline_stylesheet = "max-height: 2px; "
        "background-color : #A478B8;";
QString Parameters::icon_stylesheet = "max-width: 46px;"
        "max-height: 42px;";

QString Parameters::carrousel_stylesheet = "border : solid 2px;"
        "border-color: gray" ;
QString Parameters::milestone_stylesheet = "border : solid 2px;"
        "border-color: black" ;

QString Parameters::text_edit_stylesheet = "max-height: 25px;"
        "max-width: 250px;"
        "border: 1px solid #8c8c8c;"
        "border-radius: 4px;"
        "background-color: #ffffff;"
        "font-family: Arial;"
        "font-size: 14px;"
        "color: #121212;"
        "font-style: italic;";

QString Parameters::text_plain_edit_stylesheet  = "max-height: 50px;"
          "max-width: 300px;"
          "border: 1px solid #8c8c8c;"
          "border-radius: 4px;"
          "background-color: #ffffff;"
          "font-family: Arial;"
          "font-size: 14px;"
          "color: #121212;"
          "font-style: italic;";

//path for images
QString Parameters::path_calendar = "../MyProjects/images/calendar.png";
QString Parameters::path_left_arrow = "../MyProjects/images/left_arrow.png";
QString Parameters::path_right_arrow = "../MyProjects/images/right_arrow.png";
QString Parameters::path_number = "../MyProjects/images/number.png" ;
QString Parameters::path_plus = "../MyProjects/images/plus.png";
QString Parameters::path_user = "../MyProjects/images/user.png";
