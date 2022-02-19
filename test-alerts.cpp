#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  BatteryCharacter BatteryChar;
  BatteryChar.coolingType = PASSIVE_COOLING;
  //REQUIRE(
  checkAndAlert(TO_CONTROLLER,BatteryChar,30);
  BatteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,BatteryChar,50);
}
