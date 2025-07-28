#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H
#include "config.h"
void init_For_Auto(SETTING *want);
void Display_For_Auto(SETTING want);
void Handle_Auto(SETTING *current);
void Handle_Manual(SETTING *current);

#endif