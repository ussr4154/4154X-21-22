#pragma once

#include <string>

//selector configuration
#define HUE 230
#define DEFAULT 1
#define AUTONS "Right Goal + AWP Line", "Mid Goals", "Full AWP", "Do Nothing", "Mid Goals + Awp Line", "Left Goal + AWP Ring"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
