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
