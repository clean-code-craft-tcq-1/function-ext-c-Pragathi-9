/* Include Headerfiles													*/
/* ===================													*/
#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
/* ===================													*/
/* Macros and define values */
/* ===================													*/
#define MAXCHARGERATE 0.5
#define MINCHARGERATE 0
#define MAXTEMP 45.0
#define MINTEMP 35.0
#define MAXSOC 80.0
#define MINSOC 20.0
#define German 0
#define English 1

int language=German;

enum BatteryParameters{
	Temperature,
	ChargeRate,
	StateofCharge	
};



#define NumberOfBatteries 3
#define NumberOfParameters 3

float maximumthreshold[]={MAXTEMP,MAXCHARGERATE,0.8};
float minimumthreshold[]={MINTEMP,MINCHARGERATE,0.2};

struct BatteryProperties
{
	int parameterbreachstatus[NumberOfBatteries][NumberOfParameters];
	enum BatteryParameters Attributes;
	float attributevalue[NumberOfBatteries][NumberOfParameters];
	int Status[NumberOfBatteries];	
};


struct BatteryProperties properties;


const char* BMSattributeEnglish[]= { "Temperature","Charge-rate","State-of-Charge"};
const char* BMSattributeGerman[]= {" Temperatur ","Laderate "," Ladezustand "};

const char* DisplayinGerman[] = {
"Warnung: niedriger Pegel durchbrochen", 
 " ist normal", 
};
const char* DisplayinEnglish[] = {
" Warning: Limit is breached", 
 "  is NORMAL", 
};

const char* DisplayStatusEnglish[]={
	
	"The Battery management system is in bad condition considering the above factors \n",
	"The Battery management system is in good condition considering the above factors \n"
};

const char* DisplayStatusGerman[]={
	
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in einem schlechten Zustand. \n",
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in gutem Zustand \n"
	
};
/****************************************************************************
Function declaration
***************************************************************************/
void BatteryReport();
int Accumulator(float array[NumberOfBatteries][NumberOfParameters], bool resultant[NumberOfBatteries]);
