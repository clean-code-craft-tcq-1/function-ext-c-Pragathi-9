/* Include Headerfiles													*/
/* ===================													*/

#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
#include "checker.h"


/******************************************************************************/

float tolerance (float upperlimit)
{
	return((5/100)*upperlimit);
}
/********************************************************************************
 * A function that gives Charge rate of a Battery management system.
 * if the current Charge rating is above the threshold, then the battery is unacceptable.
 * input: Current charge rate in decimal (percentage converted to floating value)
 * returns: Check if the charge rate is out of boundary conditions
 *********************************************************************************/
int BMS_ChargeRateCheck(float charge_rate)
{
	int chargerate_check = (charge_rate > MAXCHARGERATE);
	 if(chargerate_check)
	   {
		printf("Charge Rate is %f and is out of range!\n", charge_rate);
		return 0;
	   }
	printf("Charge Rate is %f within the maximum threshold\n", charge_rate);  
	return 1;
}
/********************************************************************************
 * A common function that checks the range of parameters.
 * input: parameter, Maximum and minimum range to be checked
 * returns: Check if the parameter is out of the given maximum and minimum range
 *********************************************************************************/
bool BMS_RangeCheck(float parameter, float maxlimit, float minlimit)
{
	return((parameter >= minlimit) && (parameter < maxlimit));
}
/********************************************************************************
 * A common function that checks the warning for breach, low and normal ranges.
 * input: parameter, Maximum and minimum thresholds range to be checked
 * returns: Check if the parameter falls in normal or any warnings range
 *********************************************************************************/
int BMS_WarningRanges(float parameter, float maxrange, float minrange)
{
	
	float lowwarninglimit = (minrange + tolerance(maxrange));
	float highwaninglimit=  (maxrange - tolerance(maxrange));
	int ArrayIndex=0;
	int ranges[]= {minrange, lowwarninglimit, highwaninglimit, maxrange};
	 int numberofrange = ((sizeof(ranges))/(sizeof(ranges[0])));
	for (int index=0; index<(numberofrange-1); index++)
	{
			if (BMS_RangeCheck(parameter, ranges[index+1],ranges[index]))
			{
				ArrayIndex= index+1;
			}
	}
	 
 return (ArrayIndex);
}
	 

/********************************************************************************
 * A function that gives State-of-Charge parameter within boundary check of a Battery management system.
 * input: SOC in percentage
 * returns: Check if the SOC is inside boundary conditions, display the warnings or normal range messages
 *********************************************************************************/
 
bool BMS_StateOfChargeInRange(float soc)
{
  int soc_check=  BMS_WarningRanges(soc,MAXSOC,MINSOC);
  if (soc_check>0)
  {
	   DisplayStateofChargeCondition(soc, soc_check)
 	   return (1);
  }
  else
  {
	return 0;
  }
}
/********************************************************************************
 * A function that gives State-of-Charge parameter outside boundary check of a Battery management system.
 * if the current SOC is outside the boundary conditions, then the battery is unacceptable.
 * if the SOC exceeds the 80% threshold, that reduces the life span of the battery, and losses are incurred
 * Battery is charged above 80% only in outstation charging system.
 * input: SOC in percentage
 * returns: Check if the SOC is out of boundary conditions
 *********************************************************************************/			      
bool BMS_StateOfChargeOutofRange(float soc)
{
  if (soc<MINSOC)
  {
	  DisplayStateofChargeCondition(soc, 0)
	  return 0;
  }
if (soc>=MAXSOC)
{
	
	DisplayFactorCondition(soc,4);
	return 0;
}
return (0);
}
/********************************************************************************
 * A function that gives State-of-Charge parameter boundary check of a Battery management system.
 * input: SOC in percentage
 * returns: Check if the SOC is inside/outside boundary conditions. Return 1 if its within range.
 *********************************************************************************/			      
int BMS_StateOfCharge(float soc)
{
	bool OutofRangestatus= BMS_StateOfChargeOutofRange(soc);
	bool InRangeStatus=BMS_StateOfChargeInRange(soc);
	return (OutofRangestatus||InRangeStatus);
}
/********************************************************************************
 * Process: Display the battery SoC condtion
 *********************************************************************************/
void DisplayStateofChargeCondition(float soc, int statusarray)
{
	if (language=='German')
	{
		printf("BMS State-of-Charge is %f, and %s\n", soc, StateofChargeinGerman[array]);
	else
	{
		printf("BMS State-of-Charg is %f, and %s \n", soc, StateofChargeinEnglish[array]);
	}
}
/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * input: Temperature in degrees
 * returns: Check if the Temperature is within boundary conditions
 *********************************************************************************/
 bool BMS_TemperatureInRange(float temperature_deg)
{
  int temperature_check=  BMS_WarningRanges(temperature_deg,MAXTEMP,MINTEMP);
  if (temperature_check>0)
	{
	  DisplayTemperatureCondition(temperature_deg,temperature_check);
	  return (1);
	}
  else
	{
	  return 0; 
	}
}
/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * There could be loss of charge if the temperature is beyond the boundary conditions
 * input: Temperature in degrees
 * returns: Check if the Temperature is out of boundary conditions
 *********************************************************************************/			      
bool BMS_TemperatureOutofRange(float temperature_deg)
{
  if (temperature_deg<MINTEMP)
  {
	DisplayTemperatureCondition(temperature_deg,0);
	return 0;
  }
  if (temperature_deg>=MAXTEMP)
  {
	DisplayTemperatureCondition(temperature_deg,4);
	return 0;
  }
return (0);
}
/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * There could be loss of charge if the temperature is beyond the boundary conditions
 * input: Temperature in degrees
 * returns: Check if the Temperature is out/within of boundary conditions
 *********************************************************************************/
int BMS_TemperatureCheck(float temperature_deg)
{
        bool OutofRangeTemperatureStatus= BMS_TemperatureOutofRange(temperature_deg);
	bool InRangeTemperatureStatus= BMS_TemperatureInRange(temperature_deg);
	return (OutofRangeTemperatureStatus||InRangeTemperatureStatus);
  
}
/********************************************************************************
 * Process: Display the battery temperature condtion
 *********************************************************************************/
void DisplayTemperatureCondition(int factorarray, float temperature_deg, int statusarray)
{
	if (language=='German')
	{
		printf("BMS Temperatur is %f, and %s\n",   temperature_deg, TemperatureStatusGerman[statusarray]);
	else
	{
		printf("BMS Temperature is %f, and %s \n", temperature_deg, TemperatureStatusEnglish[statusarray]);
	}
}
/********************************************************************************
 * Process: Display the battery condition after all the factors are considered
 *********************************************************************************/
void BMS_DisplayBMSCondition(int condition)
{
  int array= ((language=='German')? 0:1);
  if (condition)
  {
    
    printf("%s",BMSGoodStatus[array]);
  
  }
  else
  {
   printf("%s",BMSPoorStatus[array])
  }
}

/********************************************************************************
 * A function that gives overall status of a Battery management system
 * Factors such as: Charging Temperature,Charge rate, SoH, SoC are considered to check if the BMS is good to function.
 * input: Fators to check the plausibility of BMS
 * returns: True is the factors meet the requirement
 *********************************************************************************/
 
int batteryIsOk(float ChargeRate, float stateofcharge, float temperature) 
{
  int status;
     status =  (BMS_ChargeRateCheck(ChargeRate)) & (BMS_StateOfCharge(stateofcharge)) & (BMS_TemperatureCheck(temperature));
     BMS_DisplayBMSCondition(status);
     return (status);
}



/********************************************************************************
 * Process: Main function that checks all possible test scenarios to check the BMS plausibility
 *********************************************************************************/

int main() {
  language='German';
  assert(batteryIsOk(0.4, 70, 30));
  assert(!batteryIsOk(0,85,50));
  language='English';
  assert(batteryIsOk(0.3, 25, 25));
  assert(!batteryIsOk(0.6,50,30));
  assert(!batteryIsOk(0.2,50,60));
}

