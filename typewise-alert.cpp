#include "typewise-alert.h"
#include <stdio.h>

map<CoolingType,int> lowerLimitMapper {
{PASSIVE_COOLING,0},
{HI_ACTIVE_COOLING,0},
{MED_ACTIVE_COOLING,0},
};
map<CoolingType,int> upperLimitMapper {
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


BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL));
 
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  auto iterLower = (lowerLimitMapper.find(coolingType));
  if(iterLower != lowerLimitMapper.end()){
    int upperLimit = (upperLimitMapper.find(coolingType))->second;
    int lowerLimit = iterLower->second;
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
  }
    else
      return INVALID;
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
   default:
      printf("No Action ned to be taken");
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  const char* tempBreachMessage = (temperatureBreachMapper.find(breachType))->second;
  printf("To: %s\n", recepient);
  printf("Hi,%s\n", tempBreachMessage);
}
