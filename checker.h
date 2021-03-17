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
#define MINTEMP 0
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



#define NumberOfBatteries 10
#define NumberOfParameters 3

float maximumthreshold[]={MAXTEMP,MAXCHARGERATE,MAXSOC};
float minimumthreshold[]={MINTEMP,MINCHARGERATE,MINSOC};

struct BatteryProperties
{
	int parameterbreachstatus[NumberOfBatteries][NumberOfParameters];
	enum BatteryParameters Attributes;
	float attributevalue[NumberOfBatteries][NumberOfParameters];
	int Status[NumberOfBatteries];	
};


struct BatteryProperties properties;


const char* BMSattribute[][NumberOfParameters]= {{" Temperatur ","Laderate "," Ladezustand "}, {"Temperature","Charge-rate","State-of-Charge"}};

const char* Display[][2] = {
			  {"Warnung: niedriger Pegel durchbrochen",
			    " ist normal"},
			  {" Warning: Limit is breached", 
			   "  is NORMAL"}
};

const char* DisplayStatus[][2]={
	{"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in einem schlechten Zustand. \n",
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in gutem Zustand \n"},
	{"The Battery management system is in bad condition considering the above factors \n",
	"The Battery management system is in good condition considering the above factors \n"}
};


/****************************************************************************
Function declaration
***************************************************************************/
void BatteryReport();
int Accumulator(int numberOfBatteries, int numberOfParameters, float array[][numberOfParameters],  bool resultant[]);
