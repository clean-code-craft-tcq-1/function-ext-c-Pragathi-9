/* Include Headerfiles													*/
/* ===================													*/

#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
#include "checker.h"

enum factor attribute;
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
int BMS_ChargeRateCheck(float chargerate_val)
{	printf("%f test in chargerate function /n", chargerate_val);
	int chargerate_check = (chargerate_val > MAXCHARGERATE);
	 if(chargerate_check)
	   {	printf("%f test in chargerate function if loop/n", chargerate_val);
		DisplayAttributeCondition(factor_Chargerate,chargerate_val, 4);
		return 0;
	   }
	else
	{
		printf("%f test in chargerate function else loop/n", chargerate_val);
	DisplayAttributeCondition(factor_Chargerate,chargerate_val, 2);  
	return 1;
	}
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
 
bool BMS_StateOfChargeInRange(float soc_val)
{
  int soc_check=  BMS_WarningRanges(soc_val,MAXSOC,MINSOC);
  if (soc_check>0)
  {
	   //DisplayAttributeCondition(factor_StateofCharge,soc_val, soc_check);
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
bool BMS_StateOfChargeOutofRange(float soc_value)
{
  if (soc_value<MINSOC)
  {
	  //DisplayAttributeCondition(factor_StateofCharge,soc_value, 0);
	  return 0;
  }
if (soc_value>=MAXSOC)
{
	
	//DisplayAttributeCondition(factor_StateofCharge,soc_value,4);
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
 * A function that gives Safe operating temperature during the charging of a Battery.
 * input: Temperature in degrees
 * returns: Check if the Temperature is within boundary conditions
 *********************************************************************************/
 bool BMS_TemperatureInRange(float temt_deg)
{
  int temperature_check=  BMS_WarningRanges(temt_deg,MAXTEMP,MINTEMP);
  if (temperature_check>0)
	{
	  //DisplayAttributeCondition(factor_temperature,temt_deg,temperature_check);
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
bool BMS_TemperatureOutofRange(float temp_deg)
{
 if (temp_deg<MINTEMP)
	
  {
	//DisplayAttributeCondition(factor_temperature,temp_deg,0);
	return 0;
  }
  if (temp_deg>=MAXTEMP)
  {
	//DisplayAttributeCondition(factor_temperature,temp_deg,4);
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
void DisplayAttributeCondition(int attribute, float value, int array)
{
	//float testvalue=5;
	if (language==German)
	{
		printf("%s ist %s und %f\n", BMSattributeGerman[attribute], DisplayinGerman[array],value);
	}
	else
	{
		//printf("%s is %f and %s \n", BMSattributeEnglish[attribute], 6, DisplayinEnglish[array]);
	}
}
/********************************************************************************
 * Process: Display the battery condition after all the factors are considered
 *********************************************************************************/
void BMS_DisplayBMSCondition(int condition)
{
  int array= ((language==German)? 0:1);
  if (condition)
  {
    
    printf("%s \n",BMSGoodStatus[array]);
  
  }
  else
  {
   printf("%s \n",BMSPoorStatus[array]);
  }
}

/********************************************************************************
 * A function that gives overall status of a Battery management system
 * Factors such as: Charging Temperature,Charge rate, SoH, SoC are considered to check if the BMS is good to function.
 * input: Fators to check the plausibility of BMS
 * returns: True is the factors meet the requirement
 *********************************************************************************/
 
int batteryIsOk(float ChargeRate_Value, float StateofCharge_Value, float Temperature_Value) 
{
  int status;
     //printf("%f",ChargeRate_Value);
     status =  (BMS_ChargeRateCheck(ChargeRate_Value)) & (BMS_StateOfCharge(StateofCharge_Value)) & (BMS_TemperatureCheck(Temperature_Value));
     BMS_DisplayBMSCondition(status);
     return (status);
}



/********************************************************************************
 * Process: Main function that checks all possible test scenarios to check the BMS plausibility
 *********************************************************************************/

int main() {
  language=German;
  assert(batteryIsOk(0.4, 70, 30));
  assert(!batteryIsOk(0,85,45));
  language=English;
  assert(batteryIsOk(0.3, 22, 5));
  assert(!batteryIsOk(0.6,80,46));
  assert(!batteryIsOk(0.2,19,44));
}

