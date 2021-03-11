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

enum factor {factor_Chargerate, factor_StateofCharge, factor_temperature};

const char* BMSattributeEnglish[]= {"Charge-rate", "State-of-Charge", "Temperature"};
const char* BMSattributeGerman[]= {"Laderate "," Ladezustand "," Temperatur "};

const char* DisplayinGerman[] = {
"Warnung: niedriger Pegel durchbrochen", 
"Warnung: Stufe niedrig",
 " ist normal", 
"Warnung: Stufe hoch",
 "Warnung: High Level verletzt"
};
const char* DisplayinEnglish[] = {
" Warning: low level breahced", 
"Warning: level low",
 "  is NORMAL", 
"Warning: level High",
 "Warning:high level breached"
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
