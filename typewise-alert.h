#pragma once
#include <string>
#include <map>
using std::map;
typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  INVALID
} BreachType;

BreachType inferTempBreachTypeUsingLimits(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreachType(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkBatteryTempForBreachAndAlertTarget(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendBreachTypeTocontroller(BreachType breachType);
void sendBreachTypeToEmail(BreachType breachType);
