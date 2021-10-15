#pragma once

#include <string>

//selector configuration
#define HUE 230
#define DEFAULT 1
#define AUTONS "Two Goal", "1 Goal + Awp", "Do Nothing"
namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
