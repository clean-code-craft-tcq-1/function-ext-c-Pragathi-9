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

{	bool inrage=true;
	if ((parameter< (minimumthreshold[index]))||(parameter>= (maximumthreshold[index])))
	  {		
		  return (inrange=false);
	  }
	return(inrange);
}


int Accumulator(float array[NumberOfBatteries][NumberOfParameters],  bool resultant[NumberOfBatteries])
{
	int flag=1;
	int final_status=1;
	struct BatteryProperties properties;
	int BatteryIndex,ParameterIndex;
	for (BatteryIndex=0;BatteryIndex<NumberOfBatteries;BatteryIndex++)
	{
		int Battery_status= 1;
		final_status=1;
		for (ParameterIndex=0;ParameterIndex<NumberOfParameters;ParameterIndex++)
			
		{
			properties.Attributes=ParameterIndex;
			properties.attributevalue[BatteryIndex][ParameterIndex]= (array[BatteryIndex][ParameterIndex]);
			//returns 0 or 1 so comments will be in range and out of range
			properties.parameterbreachstatus[BatteryIndex][ParameterIndex]= BMS_BreachRanges((array[BatteryIndex][ParameterIndex]),ParameterIndex);
			Battery_status= Battery_status & (properties.parameterbreachstatus[BatteryIndex][ParameterIndex]);
		}
		
		properties.Status[BatteryIndex]= Battery_status;
		if ((properties.Status[BatteryIndex])==(resultant[BatteryIndex]))
		{
			flag=1;
		}
		else
		{	
			flag=0;
		}
		final_status &= flag;
	}
	
	return (final_status);
}
	
void BatteryReport()
{	
	struct BatteryProperties properties;
	int ParameterIndex,BatteryIndex;
	for (BatteryIndex=0;BatteryIndex<NumberOfBatteries;BatteryIndex++)
	{
		for (ParameterIndex=0;ParameterIndex<NumberOfParameters;ParameterIndex++)
			
		{	
			if (language==English)
			{
				printf("%s = %f and %s \n", BMSattributeEnglish[ParameterIndex],properties.attributevalue[BatteryIndex][ParameterIndex], DisplayinEnglish[(properties.parameterbreachstatus[BatteryIndex][ParameterIndex])]);
			}
			else
			{
				printf("%s = %f and %s \n", BMSattributeGerman[ParameterIndex],properties.attributevalue[BatteryIndex][ParameterIndex], DisplayinGerman[(properties.parameterbreachstatus[BatteryIndex][ParameterIndex])]);
			}
		}
		if (language==English)
			{
			printf ("Battery %d is %s \n",BatteryIndex,DisplayStatusEnglish[properties.Status[BatteryIndex]]);
			}
		else
			{
			printf ("Battery %d is %s \n",BatteryIndex,DisplayStatusGerman[properties.Status[BatteryIndex]]);
		}
	}
	
	
}
	
 
  
int main() 
{ 
    
    language=English;
    float array[][NumberOfParameters] = {{40, 0.2, 30}, {46, 0.3,80}, {30, 0.4, 40}}; 
    bool resultant[NumberOfBatteries]={1,0,1};
    assert(!(Accumulator(array,resultant)));
    BatteryReport();
    return 0; 
}

