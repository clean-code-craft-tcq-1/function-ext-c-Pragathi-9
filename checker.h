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
#define NumberOfBatteries 3
#define NumberOfParameters 3

int language=German;

enum BatteryParameters{
	Temperature,
	ChargeRate,
	StateofCharge	
};


float AttributeMaximumthreshold[]={MAXTEMP,MAXCHARGERATE,MAXSOC};
float AttributeMinimumthreshold[]={MINTEMP,MINCHARGERATE,MINSOC};

struct BatteryProperties
{
	int AttributeinRangeStatus[NumberOfBatteries][NumberOfParameters];
	enum BatteryParameters Attributes;
	float AttributeValue[NumberOfBatteries][NumberOfParameters];
	int BatteryStatus[NumberOfBatteries];
	int VerifiedResultfromBatteries;
};


struct BatteryProperties properties;


const char* BMS_AttributeDisplay[][NumberOfParameters]= {{" Temperatur ","Laderate "," Ladezustand "}, {"Temperature","Charge-rate","State-of-Charge"}};

const char* BMS_AttributeRangeStatusDisplay[][2] = {
			  {"Warnung: niedriger Pegel durchbrochen",
			    " ist normal"},
			  {" Warning: Limit is breached", 
			   "  is NORMAL"}
};

const char* BMS_StatusDisplay[][2]={
	{"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in einem schlechten Zustand. \n",
	"Das Batteriemanagementsystem ist unter Berücksichtigung der oben genannten Faktoren in gutem Zustand \n"},
	{"The Battery management system is in bad condition considering the above factors \n",
	"The Battery management system is in good condition considering the above factors \n"}
};


/****************************************************************************
Function declaration
***************************************************************************/
void BMS_ReportingController(struct BatteryProperties);
void BMS_Report(struct BatteryProperties);
BatteryProperties BMS_AttributeStatusAccumulator(float Input_Attribute[NumberOfBatteries][NumberOfParameters],  bool Expected_result[]);
