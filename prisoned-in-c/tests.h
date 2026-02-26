#ifndef _TESTS_H_
#define _TESTS_H_

#include "parameters.h"

int temptatioUnparallel(ParamPtr (*parFun)());

int temptatioParallel(ParamPtr (*parFun)());

int memoryRationality(ParamPtr (*parFun)());

int debuggingMode(ParamPtr (*parFun)());

int percentSampling1(ParamPtr (*parFun)());

int percentSampling2(ParamPtr (*parFun)());

int betaVariation(ParamPtr (*parFun)());

#endif