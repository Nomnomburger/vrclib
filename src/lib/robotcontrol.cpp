#include "../../include/main.h"
#include "../globals/globals.hpp"
#include "robotcontrol.hpp"
#include "autoncontrol.hpp"

inline void runIntake(int power)
{
  intake = power;
  indexer = power;
}

inline void index(int power)
{
  indexer = power;
}