#include "typewise-alert.h"
#include <stdio.h>
#include "tempBreachAlertmapper.h"

BreachType inferTempBreachTypeUsingLimits(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL));
 
}

BreachType classifyTemperatureBreachType(
    CoolingType coolingType, double temperatureInC) {
  //if (temperatureUpperAndLowerLimitsMapper.find(coolingType) != temperatureUpperAndLowerLimitsMapper.end())
  if (temperatureUpperAndLowerLimitsMapper.contains(coolingType))
    return inferTempBreachTypeUsingLimits(temperatureInC,temperatureUpperAndLowerLimitsMapper[coolingType].at(0), temperatureUpperAndLowerLimitsMapper[coolingType].at(1));
    else
      return INVALID;
}

void checkBatteryTempForBreachAndAlertTarget(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreachType(
    batteryChar.coolingType, temperatureInC
  );
  
  pfunc getTarget = alertTargetFuncFinder[alertTarget];
  (*getTarget)(breachType);
  
}

void sendBreachTypeToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendBreachTypeToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType != NORMAL){
  const char* tempBreachMessage = (temperatureBreachMapper.find(breachType))->second;
  printf("To: %s\n", recepient);
  printf("Hi,%s\n", tempBreachMessage);
  }
}
