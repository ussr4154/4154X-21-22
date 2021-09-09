#pragma once

#include <string>

//selector configuration
#define HUE 230
#define DEFAULT 1
#define AUTONS "Goal + AWP Line", "Mid Goals", "Full AWP"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
