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

int BMS_RangeStages(float parameter, float maxrange, float minrange)
{
	
	float lowwarninglimit = (minrange + tolerance(maxrange));
	float highwaninglimit=  (maxrange - tolerance(maxrange));
	
	bool lowwarning= (BMS_RangeCheck(parameter, lowwarninglimit,minrange));
	bool normalcondition= (BMS_RangeCheck(parameter, highwaninglimit,lowwarninglimit));
	bool highwarning= (BMS_RangeCheck(parameter, maxrange,highwaninglimit));
	bool highbreachwarning= (parameter >= maxrange)? 4:0;
	if (breachwarning)
	   {
		return (1);
	   }
        if (normalcondition)
	   {
		return (2);
	   }
	if(highwarning)
	   {
		return (3);
	   }
	 if(highbreachwarning)
	 {
		 return (4);
	 }
	 
 return (0);
}
		    
/********************************************************************************
 * A function that gives State-of-Charge parameter check of a Battery management system.
 * if the current SOC is outside the boundary conditions, then the battery is unacceptable.
 * if the SOC exceeds the 80% threshold, that reduces the life span of the battery, and losses are incurred
 * Battery is charged above 80% only in outstation charging system.
 * input: SOC in percentage
 * returns: Check if the SOC is out of boundary conditions
 *********************************************************************************/
 
int BMS_StateOfCharge(float soc)
{
  int soc_check=  BMS_RangeStages(soc,MAXSOC,MINSOC);
  printf("State of Charge is %f percent, and %s \n", soc, StateofCharge[soc_check]);
  if ((soc_check==0)|| (soc==4))
  { 
    return 0;
  }
  else
  {
    return 1;
  }
  
}

/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * There could be loss of charge if the temperature is beyond the boundary conditions
 * input: Temperature in degrees
 * returns: Check if the Temperature is out of boundary conditions
 *********************************************************************************/
 
int BMS_TemperatureCheck(float temperature_deg)
{
  int temperature_check= BMS_RangeStages(temperature_deg,MAXTEMP,MINTEMP);
  printf("Temperature is %f and  %s\n", temperature_deg, TemperatureStatus[temperature_check]);
  if((temperature_check==0)|| (temperature_check==4))
  {
    return 0;
  } 
  else
  {
    return 1;
  }
  
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

