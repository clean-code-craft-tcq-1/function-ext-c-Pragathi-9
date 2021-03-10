/* Include Headerfiles													*/
/* ===================													*/
#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
/* ===================													*/
/* Macros and define values */
/* ===================													*/
#define MAXCHARGERATE 0.5
#define MAXTEMP 45.0
#define MINTEMP 0
#define MAXSOC 80.0
#define MINSOC 20.0

const char* StateofCharge[] = {
" Warning: State-of-Charge low level breahced", 
"Warning: State-of-Charge level low",
 " State-of-Charge level NORMAL", 
"Warning: State-of-Charge level High",
 "Warning: State-of-Charge high level breached"
};

const char* TemperatureStatus[] = {
	" Warning: Temperature low level breahced", 
"Warning: Temperature level low",
 " Temperature is NORMAL, and within the ideal range", 
"Warning: Temperature level High",
 "Warning: Temperature high level breached"
};
/****************************************************************************
Function declaration
/***************************************************************************/
int batteryIsOk(float ChargeRate, float stateofcharge, float temperature);
