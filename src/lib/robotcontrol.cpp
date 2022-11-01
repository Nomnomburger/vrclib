#include "../../include/main.h"
#include "../globals/globals.hpp"
#include "robotcontrol.hpp"
#include "autoncontrol.hpp"

void runIntake(int power)
{
  intake = power;
  indexer = power;
}

void index(int power)
{
  indexer = power;
}