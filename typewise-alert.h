#pragma once
#include <map>
typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;
map<string,int> lowerLimitMapper;
map<string,int> upperLimitMapper;

lowerLimitMapper.insert(pair<string,int>(PASSIVE_COOLING,0));
lowerLimitMapper.insert(pair<string,int>(HI_ACTIVE_COOLING,0));
lowerLimitMapper.insert(pair<string,int>(MED_ACTIVE_COOLING,0));

upperLimitMapper.insert(pair<string,int>(PASSIVE_COOLING,30));
upperLimitMapper.insert(pair<string,int>(HI_ACTIVE_COOLING,45));
upperLimitMapper.insert(pair<string,int>(MED_ACTIVE_COOLING,40));

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
