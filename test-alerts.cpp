#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferTempBreachTypeUsingLimits(12, 20, 30) == TOO_LOW);
  REQUIRE(inferTempBreachTypeUsingLimits(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferTempBreachTypeUsingLimits(25, 20, 30) == NORMAL);
}
TEST_CASE("Classify temperature breach type based on cooling type") { 
  REQUIRE(classifyTemperatureBreachType(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachType(HI_ACTIVE_COOLING,-20) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachType(HI_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreachType(MED_ACTIVE_COOLING,45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachType(MED_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreachType(MED_ACTIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachType(PASSIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreachType(PASSIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachType(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachType(PASSIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreachType((CoolingType)7,10) == INVALID);
}

TEST_CASE("Check Battery temperature for breach based on cooling type, and alert the respective target") {
  BatteryCharacter BatteryChar;
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,40);
  //checkBatteryTempForBreachAndAlertTarget((AlertTarget)7,BatteryChar,40);
  BatteryChar.coolingType = PASSIVE_COOLING;
  checkBatteryTempForBreachAndAlertTarget(TO_CONTROLLER,BatteryChar,30);
  BatteryChar.coolingType = HI_ACTIVE_COOLING;
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,50);
  /*checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,20);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,-20);
  BatteryChar.coolingType = MED_ACTIVE_COOLING;
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,45);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,20);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,-10);
  BatteryChar.coolingType = PASSIVE_COOLING;
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,40);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,20);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,-20);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,40);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,20);
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,-20);*/
  BatteryChar.coolingType = (CoolingType)7;
  checkBatteryTempForBreachAndAlertTarget(TO_EMAIL,BatteryChar,40);
}
TEST_CASE("Send breach type to controller if temperature breaches limits") {
  sendBreachTypeToController(TOO_LOW);
  sendBreachTypeToController(TOO_HIGH);
  sendBreachTypeToController(NORMAL);  
}

TEST_CASE("Send email if temperature breaches limits") {
  sendBreachTypeToEmail(TOO_LOW);
  sendBreachTypeToEmail(TOO_HIGH);
  sendBreachTypeToEmail(NORMAL);  
}
