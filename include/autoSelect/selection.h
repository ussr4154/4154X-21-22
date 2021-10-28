#pragma once

#include <string>

//selector configuration
#define HUE 230
#define DEFAULT 1
#define AUTONS "Mid Goal", "Right Goal", "Left Goal"
namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
