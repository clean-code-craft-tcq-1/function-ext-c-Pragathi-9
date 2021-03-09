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

/****************************************************************************
Function declaration
/***************************************************************************/
int batteryIsOk(float StateofHealth, float ChargeRate, float stateofcharge, float temperature);
