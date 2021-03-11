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
#define German 0
#define English 1

int language=German;

const char* StateofChargeinGerman[] = {
" Warnung: Der Ladezustand ist niedrig", 
"Warnung: Ladezustand niedrig",
 " Ladezustand NORMAL", 
"Warnung: Ladezustand hoch",
 "Warnung: High-Level des Ladezustands verletzt"
};
const char* StateofChargeinEnglish[] = {
" Warning: State-of-Charge low level breahced", 
"Warning: State-of-Charge level low",
 " State-of-Charge level NORMAL", 
"Warning: State-of-Charge level High",
 "Warning: State-of-Charge high level breached"
};

const char* TemperatureStatusEnglish[] = {
" Warning: Temperature low level breahced", 
"Warning: Temperature level low",
 " Temperature is NORMAL, and within the ideal range", 
"Warning: Temperature level High",
 "Warning: Temperature high level breached"
};
const char* TemperatureStatusGerman[] = {
" Warnung: Temperatur niedrig durchbrochen", 
"Warnung: Temperaturniveau niedrig ",
 " Die Temperatur ist NORMAL und liegt im idealen Bereich", 
"Warnung: Temperaturstufe hoch",
 "Warnung: Hohe Temperatur verletzt"
};

const char* BMSGoodStatus[]={
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in gutem Zustand \ n",
	"The Battery management system is in good condition considering the above factors \n"
};

const char* BMSPoorStatus[]={
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in einem schlechten Zustand. \n",	
	"The Battery management system is in bad condition considering the above factors \n"
};
/****************************************************************************
Function declaration
/***************************************************************************/
int batteryIsOk(float ChargeRate, float stateofcharge, float temperature);
