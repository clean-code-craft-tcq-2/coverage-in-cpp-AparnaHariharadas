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

map<BreachType,std::string> temperatureBreachMapper {
{TOO_LOW,"Temperature is too low"},
{TOO_HIGH,"Temperature is too high"},
{NORMAL,"Temperature is normal"},
};


BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL));
 
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  auto iterLower = (lowerLimitMapper.find(coolingType));
  auto iterUpper = (upperLimitMapper.find(coolingType));
  int lowerLimit = iterLower->second;
  int upperLimit = iterUpper->second;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
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
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  auto iterTemp = (temperatureBreachMapper.find(breachType));
  std::string tempBreachMessage = iterTemp->second;
  printf("To: %s\n", recepient);
  printf("Hi,%s\n", tempBreachMessage);
}
