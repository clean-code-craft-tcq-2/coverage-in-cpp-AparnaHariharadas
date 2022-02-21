#include <vector>
#include <sstream>
#include <map>
using std::map;

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
map<AlertTarget, pfunc> alertTargetFuncFinder {
{TO_CONTROLLER, sendBreachTypeToController},
{TO_EMAIL, sendBreachTypeToEmail}
};
