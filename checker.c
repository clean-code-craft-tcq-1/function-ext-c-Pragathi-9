/* Include Headerfiles													*/
/* ===================													*/

#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>
#include "checker.h"



/********************************************************************************
 * A common function that checks if the paramters are within the boundary conditions.
 * input: parameter value, Maximum and minimum range to be checked
 * returns: Check if the parameter is within in the given maximum and minimum range
 *********************************************************************************/

bool BMS_AttributeinRangeStatus(float parametervalue, int index)

{	bool InRange=true;
	
 if((AttributeMaximumthreshold[index])<=parametervalue<(AttributeMinimumthreshold[index]))
	  {		
		  return (InRange=false);
	  }
	return(InRange);
}

/********************************************************************************
 * This function accumulates the breach status for all the parameters of the BMS and stores in an array
 * Also, the accumulated result is verified against the expected results
 * input: Array which has parameter values of different batteries.
 * returns: Verification of the checked Battery status against the expected.
 *********************************************************************************/
properties BMS_AttributeStatusAccumulator(float Input_Attribute[NumberOfBatteries][NumberOfParameters],  bool Expected_result[])
{
	int VerifyResult=0;
	struct BatteryProperties properties;
	int BatteryIndex,ParameterIndex;
	for (BatteryIndex=0;BatteryIndex < NumberOfBatteries;BatteryIndex++)
	{
		int Battery_status= 1;
		VerifiedResult=1;
		for (ParameterIndex=0;ParameterIndex < NumberOfParameters;ParameterIndex++)
			
		{
			properties.Attributes=ParameterIndex;
			properties.AttributeValue[BatteryIndex][ParameterIndex]= (Input_Attribute[BatteryIndex][ParameterIndex]);
			properties.AttributeinRangeStatus[BatteryIndex][ParameterIndex]= BMS_AttributeinRangeStatus((Input_Attribute[BatteryIndex][ParameterIndex]),ParameterIndex);
			Battery_status= Battery_status & (properties.AttributeinRangeStatus[BatteryIndex][ParameterIndex]);
		}
		
		properties.BatteryStatus[BatteryIndex]= Battery_status;
		VerifiedResultfromBatteries= (!((properties.BatteryStatus[BatteryIndex]) ^ (Expected_result[BatteryIndex])));
		properties.VerifiedResultfromBatteries &= VerifyResult;
	}
	BMS_Report(properties);
	return (properties);
}

void BMS_Report( struct BatteryProperties Displayproperties)
{
	int ParameterIndex,BatteryIndex;
	for (BatteryIndex=0;BatteryIndex<NumberOfBatteries;BatteryIndex++)
	{
		for (ParameterIndex=0;ParameterIndex<NumberOfParameters;ParameterIndex++)
			
		{	
			printf("%s = %f, %s \n", BMS_AttributeDisplay[language][ParameterIndex],Displayproperties.AttributeValue[BatteryIndex][ParameterIndex], BMS_AttributeRangeStatusDisplay[language][(Displayproperties.AttributeinRangeStatus[BatteryIndex][ParameterIndex])]);
			
		}
		
		printf ("Battery %d -> %s \n",BatteryIndex,BMS_StatusDisplay[language][Displayproperties.BatteryStatus[BatteryIndex]]);
		
	}
}
	
/********************************************************************************
 * This function calls the controller to report the battery parameter status
 *  It also displays the overall status of a battery, both in German and English as requested.
 *********************************************************************************/	
void BMS_ReportingController(struct BatteryProperties PropertiesToController;)
{	
	
	
	printf("Reporting the BMS health results from Controller as follows:\n");
	BMS_Report(PropertiesToController);
	
	
}
 
  
int main() 
{ 
    struct BatteryProperties Accumulatedproperties;
    language=English;
    float SampleArray_1[][NumberOfParameters] = {{40, 0.2, 30}, {46, 0.3,80}, {30, 0.4, 40}}; 
    bool Expectedresultant_1[]={1,0,1};
    Accumulatedproperties=(BMS_AttributeStatusAccumulator(SampleArray_1,Expectedresultant_1));
    assert(Accumulateproperties.VerifiedResultfromBatteries);
    BMS_ReportingController(Accumulateproperties);
    
    language=German;
    float SampleArray_2[][NumberOfParameters] = {{50, 0.4, 60},{10, 0.6,25},{20, 0.25, 50}}; 
    bool Expectedresultant_2[]= {0,0,1};
    Accumulatedproperties=(BMS_AttributeStatusAccumulator(SampleArray_2,Expectedresultant_2));
    assert(Accumulatedproperties.VerifiedResultfromBatteries);
    BMS_ReportingController(Accumulatedproperties);
    return 0; 
}
