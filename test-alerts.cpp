#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,10) == NORMAL);
  
  BatteryCharacter BatteryChar;
  checkAndAlert(TO_EMAIL,BatteryChar,40);
  BatteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,BatteryChar,30);
  BatteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,BatteryChar,50);
  checkAndAlert(TO_EMAIL,BatteryChar,20);
  checkAndAlert(TO_EMAIL,BatteryChar,-20);
  BatteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,BatteryChar,45);
  checkAndAlert(TO_EMAIL,BatteryChar,20);
  checkAndAlert(TO_EMAIL,BatteryChar,-10);
  BatteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,BatteryChar,40);
  checkAndAlert(TO_EMAIL,BatteryChar,20);
  checkAndAlert(TO_EMAIL,BatteryChar,-20);
  BatteryChar.coolingType = NULL;
  checkAndAlert(TO_EMAIL,BatteryChar,40);
  checkAndAlert(TO_EMAIL,BatteryChar,20);
  checkAndAlert(TO_EMAIL,BatteryChar,-20);
  BatteryChar.coolingType = (CoolingType)3;
  checkAndAlert(TO_EMAIL,BatteryChar,40);
  
  sendToEmail(TOO_LOW);
  sendToEmail(TOO_HIGH);
  sendToEmail(NORMAL);
  
  
}
