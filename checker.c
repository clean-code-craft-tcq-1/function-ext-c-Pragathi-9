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
 * input: parameter, aximum and minimum range to be checked
 * returns: Check if the parameter is out of the given maximum and minimum range
 *********************************************************************************/
bool BMS_RangeCheck(float parameter, float maxlimit, float minlimit)
{
	return((parameter >= minlimit) && (parameter < maxlimit));
}

int BMS_WarningRangeStages(float parameter, float maxrange, float minrange)
{
	
	float lowwarninglimit = (minrange + tolerance(maxrange));
	float highwaninglimit=  (maxrange - tolerance(maxrange));
	int ArrayIndex=0;
	int range[]= {minrange, lowwarninglimit, highwaninglimit, maxrange};
	 int numberofrange = ((sizeof(range))/(sizeof(range[0])));
	for (int index=0; index<(numberofrange-1); index++)
	{
			if (BMS_RangeCheck(parameter, range[index+1],range[index]))
			{
				ArrayIndex= index+1;
			}
	}
	 
 return (ArrayIndex);
}
	 

/********************************************************************************
 * A function that gives State-of-Charge parameter check of a Battery management system.
 * if the current SOC is outside the boundary conditions, then the battery is unacceptable.
 * if the SOC exceeds the 80% threshold, that reduces the life span of the battery, and losses are incurred
 * Battery is charged above 80% only in outstation charging system.
 * input: SOC in percentage
 * returns: Check if the SOC is out of boundary conditions
 *********************************************************************************/
 
bool BMS_StateOfChargeInRange(float soc)
{
  int soc_check=  BMS_WarningRangeStages(soc,MAXSOC,MINSOC);
  if (soc_check>0)
  {
  printf("State of Charge is %f percent, and %s \n", soc, StateofCharge[soc_check]);
  return (1);
  }
  else
  {
	return 0;
  }
}
			      
bool BMS_StateOfChargeOutofRange(float soc)
{
  if (soc<MINSOC)
  {
	  printf("State of Charge is %f percent, and %s \n", soc, StateofCharge[0]);
	  return 0;
  }
if (soc>=MAXSOC)
{
	printf("State of Charge is %f percent, and %s \n", soc, StateofCharge[4]);
	return 0;
}
return (0);
}
			      
int BMS_StateOfCharge(float soc)
{
	bool OutofRangestatus= BMS_StateOfChargeOutofRange(soc);
	bool InRangeStatus=BMS_StateOfChargeInRange(soc);
	return (OutofRangestatus||InRangeStatus);
}
/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * There could be loss of charge if the temperature is beyond the boundary conditions
 * input: Temperature in degrees
 * returns: Check if the Temperature is out of boundary conditions
 *********************************************************************************/
 bool BMS_TemperatureInRange(float temperature_deg)
{
  int temperature_check=  BMS_WarningRangeStages(temperature_deg,MAXSOC,MINSOC);
  if (temperature_check>0)
	{
	  printf("State of Charge is %f percent, and %s \n", temperature_deg, TemperatureStatus[temperature_check]);
	  return (1);
	}
  else
	{
	  return 0; 
	}
}
			      
bool BMS_TemperatureOutofRange(float temperature_deg)
{
  if (temperature_deg<MINTEMP)
  {
	printf("State of Charge is %f percent, and %s \n", temperature_deg, TemperatureStatus[0]);
	return 0;
  }
  if (temperature_deg>=MAXTEMP)
  {
	printf("State of Charge is %f percent, and %s \n", temperature_deg, TemperatureStatus[4]);
	return 0;
  }
return (0);
}
int BMS_TemperatureCheck(float temperature_deg)
{
        bool OutofRangeTemperatureStatus= BMS_TemperatureOutofRange(temperature_deg);
	bool InRangeTemperatureStatus= BMS_TemperatureInRange(temperature_deg);
	return (OutofRangeTemperatureStatus||InRangeTemperatureStatus);
  
}

/********************************************************************************
 * Process: Display the battery condition after all the factors are considered
 *********************************************************************************/
void BMS_DisplayCondition(int condition)
{
  if (condition)
  {
    printf(" The Battery management system is in good condition considering the above factors \n");
  }
  else
  {
   printf(" The Battery management system is in bad condition considering the above factors \n");
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
     BMS_DisplayCondition(status);
     return (status);
}



/********************************************************************************
 * Process: Main function that checks all possible test scenarios to check the BMS plausibility
 *********************************************************************************/

int main() {
  
  assert(batteryIsOk(0.4, 70, 30));
  assert(!batteryIsOk(0,85,50));
  assert(!batteryIsOk(0.6,50,30));
  assert(!batteryIsOk(0.2,50,60));
}

