#include "typewise-alert.h"
#include <stdio.h>
#include <vector>
#include <sstream>

/*map<CoolingType, int> lowerLimitMapper {
{PASSIVE_COOLING,0},
{HI_ACTIVE_COOLING,0},
{MED_ACTIVE_COOLING,0},
};
map<CoolingType, int> upperLimitMapper {
{PASSIVE_COOLING,35},
{HI_ACTIVE_COOLING,45},
{MED_ACTIVE_COOLING,40},
};*/
map<CoolingType, std::vector<int>> temperatureUpperAndLowerLimitsMapper {
{PASSIVE_COOLING, {0, 35}},
{HI_ACTIVE_COOLING, {0, 45}},
{MED_ACTIVE_COOLING, {0,40}}
};

map<BreachType,const char*> temperatureBreachMapper {
{TOO_LOW,"Temperature is too low"},
{TOO_HIGH,"Temperature is too high"},
{NORMAL,"Temperature is normal"},
{INVALID,"Invalid Cooling type is given please check"},
};
 using pfunc = void (*)(BreachType);
map<AlertTarget, pfun> alertTargetFuncFinder {
{TO_CONTROLLER, sendBreachTypeToController},
{TO_EMAIL, sendBreachTypeToEmail}
};

BreachType inferTempBreachTypeUsingLimits(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit ? TOO_LOW : (value > upperLimit ? TOO_HIGH : NORMAL));
 
}

BreachType classifyTemperatureBreachType(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  //int upperLimit = 0;
  //auto iterLower = lowerLimitMapper.find(coolingType);
  if (temperatureUpperAndLowerLimitsMapper.find(coolingType) != temperatureUpperAndLowerLimitsMapper.end())
  if(iterLower != lowerLimitMapper.end()){
    //lowerLimit = iterLower->second;
    return inferTempBreachTypeUsingLimits(temperatureInC,temperatureUpperAndLowerLimitsMapper[coolingType].at(0), temperatureUpperAndLowerLimitsMapper[coolingType].at(1));
    //return inferTempBreachTypeUsingLimits(temperatureInC, temperatureUpperAndLowerLimitsMapper[coolingType].at[0], upperLimitMapper.find(coolingType)->second);
  }
    else
      return INVALID;
}

void checkBatteryTempForBreachAndAlertTarget(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreachType(
    batteryChar.coolingType, temperatureInC
  );

  /*switch(alertTarget) {
    case TO_CONTROLLER:
      sendBreachTypeToController(breachType);
      break;
    case TO_EMAIL:
      sendBreachTypeToEmail(breachType);
      break;
  }*/
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
