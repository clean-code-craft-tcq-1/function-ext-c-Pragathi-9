/* Include Headerfiles													*/
/* ===================													*/

#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
#include "checker.h"



/********************************************************************************
 * A common function that checks the range of parameters.
 * input: parameter, Maximum and minimum range to be checked
 * returns: Check if the parameter is out of the given maximum and minimum range
 *********************************************************************************/

bool BMS_BreachRanges(float parameter, int index)

{	
	BatteryProperties boundary;
	
	if (parameter< boundary.minimumthreshold[index])
	  {		
		  return 0;
	  }
	else if (parameter>=boundary.maximumthreshold[index])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int Accumulator(float array[NumberOfBatteries][NumberOfParameters],  bool resultant[NumberOfBatteries])
{
	bool flag=0;
	BatteryProperties *properties;
	int Battery_status= 1;
	int BatteryIndex,ParameterIndex;
	for (BatteryIndex=0;BatteryIndex<NumberOfBatteries;BatteryIndex++)
	{
		for (ParameterIndex=0;ParameterIndex<NumberOfParameters;ParameterIndex++)
			
		{
			properties->Attributes=ParameterIndex;
			properties->attributevalue[BatteryIndex][ParameterIndex]= (array[BatteryIndex][ParameterIndex]);
			//returns 0 or 1 so comments will be in range and out of range
			properties-> parameterbreachstatus[BatteryIndex][ParameterIndex]= BMS_BreachRanges((array[BatteryIndex][ParameterIndex]),properties->Attributes);
			Battery_status= Battery_status & (properties-> parameterbreachstatus[BatteryIndex][ParameterIndex]);
		}
		
		properties-> Status[BatteryIndex]= Battery_status;
		if (properties-> Status[BatteryIndex]=resultant[BatteryIndex])
		{
			flag=1;
		}
		else
		{	
			flag=0;
		}
	}
	
	return flag;
}
	
void BatteryReport()
{	
	BatteryProperties *properties;
	int ParameterIndex,BatteryIndex;
	for (BatteryIndex=0;BatteryIndex<NumberOfBatteries;BatteryIndex++)
	{
		for (ParameterIndex=0;ParameterIndex<NumberOfParameters;ParameterIndex++)
			
		{	
		if (language=English)
			printf("%s = %f and %s", BMSattributeEnglish[ParameterIndex],properties->attributevalue[BatteryIndex][ParameterIndex], DisplayinEnglish[(properties-> parameterbreachstatus[BatteryIndex][ParameterIndex])]);
		else
			printf("%s = %f and %s", BMSattributeGerman[ParameterIndex],properties->attributevalue[BatteryIndex][ParameterIndex], DisplayinGerman[(properties-> parameterbreachstatus[BatteryIndex][ParameterIndex])]);
		}
		if (language=English)
		{
		printf ("Battery %d is %s",BatteryIndex,DisplayStatusEnglish[properties-> Status[BatteryIndex]]);
		}
		else
		printf ("Battery %d is %s",BatteryIndex,DisplayStatusGerman[properties-> Status[BatteryIndex]]);
		
	}
	
	
}
	
 
  
int main() 
{ 
    language=English;
    float arr[][NumberOfParameters] = {{40, 0.5, 0.3}, {46, 0.9,0.6}, {30, 0.7, 0.2}}; 
    bool resultant[NumberOfBatteries]={1,0,1};
    assert(Accumulator(arr,resultant));
    BatteryReport();
    return 0; 
}

