#include "typewise-alert.h"
#include <stdio.h>

map<CoolingType, int> lowerLimitMapper {
{PASSIVE_COOLING,0},
{HI_ACTIVE_COOLING,0},
{MED_ACTIVE_COOLING,0},
};
map<CoolingType, int> upperLimitMapper {
{PASSIVE_COOLING,35},
{HI_ACTIVE_COOLING,45},
{MED_ACTIVE_COOLING,40},
};

map<BreachType,const char*> temperatureBreachMapper {
{TOO_LOW,"Temperature is too low"},
{TOO_HIGH,"Temperature is too high"},
{NORMAL,"Temperature is normal"},
{INVALID,"Invalid Cooling type is given please check"},
};


BreachType inferTempBreachTypeUsingLimits(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL));
 
}

BreachType classifyTemperatureBreachType(
    CoolingType coolingType, double temperatureInC) {
  auto iterLower = lowerLimitMapper.find(coolingType);
  if(iterLower != lowerLimitMapper.end()){
    int upperLimit = upperLimitMapper.find(coolingType)->second;
    int lowerLimit = iterLower->second;
    return inferTempBreachTypeUsingLimits(temperatureInC, lowerLimit, upperLimit);
  }
    else
      return INVALID;
}

void checkBatteryTempForBreachAndAlertTarget(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreachType(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendBreachTypeToController(breachType);
      break;
    case TO_EMAIL:
      sendBreachTypeToEmail(breachType);
      break;
  }
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
