#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "ADC_Register.h"
#include "ADC_Interface.h"

/*GLOBAL POINTER TO FUNCTION*/
 static void (*GlobalPfunc) (void)=NULL;
   
void ADC_VidInit(void)
{
	CLR_BIT(ADMUX,REFS1);//VREF1
	SET_BIT(ADMUX,REFS0);//VREF2
	CLR_BIT(ADMUX,ADLAR);//ADJUST RIGHT
	CLR_BIT(ADCSRA,ADPS0);//PRESCALER0
    SET_BIT(ADCSRA,ADPS1);//PRESCALER1
    SET_BIT(ADCSRA,ADPS2);//PRESCALER2
    SET_BIT(ADCSRA,ADEN);//ADC ENABLE
    CLR_BIT(ADCSRA,ADATE);//TRIGGER OFF
}

void ADC_VidSetCallBack(void (*LocalPfunc) (void))
{
	GlobalPfunc=LocalPfunc;
}


ISR_ADC()
{
	if(GlobalPfunc != NULL)
	{
		GlobalPfunc(ADC);
	}
	        
}


			        /*from AN0 TO AN7*/   /*POLLING OR INTERRUPT*/ 
u16 ADC_u16GetRes(u8 LOC_u8SelectChannel,u8 LOC_u8SelectStatus)
{

	
	
	#if  SelectMode==SingleConversionMode
	ADMUX=ADMUX&0b11100000; //CLEAR ADMUX
	ADMUX=ADMUX|LOC_u8SelectChannel; //SET CHANNEL
	SET_BIT(ADCSRA,ADSC);//START CONVERSION
  if(LOC_u8SelectStatus==POLLING)
	{
	while((GET_BIT(ADCSRA,ADIF))==0)
	{
		
	}
	Clear_ADIF(); //CLEAR ADC FLAG
	}
	else if(LOC_u8SelectStatus==INTERRUPT)
	{
	 SET_BIT(ADCSRA,ADIE);//ADC INTERRUPT ENABLE 
	}
	
	
	
	#elif  SelectMode==FreeRunningMode
	ADMUX=ADMUX&0b11100000; //CLEAR ADMUX
	ADMUX=ADMUX|LOC_u8SelectChannel; //SET CHANNEL
	SET_BIT(ADCSRA,ADSC);//START CONVERSION
	SET_BIT(ADCSRA,ADATE);//AutoTriggerEnable 
	
	CLR_BIT(SFIOR,ADTS0);
	CLR_BIT(SFIOR,ADTS1);
	CLR_BIT(SFIOR,ADTS2);/*FREE RUNNING MODE*/
	
	if(LOC_u8SelectStatus==POLLING)
	{
	while((GET_BIT(ADCSRA,ADIF))==0)
	{
		
	}
	Clear_ADIF();//CLEAR ADC FLAG
	}
	else if(LOC_u8SelectStatus==INTERRUPT)
	{
	 SET_BIT(ADCSRA,ADIE);//ADC INTERRUPT ENABLE 
	}
	
	
	
	
	
	#elif  SelectMode==AnalogComparator
	ADMUX=ADMUX&0b11100000; //CLEAR ADMUX
	ADMUX=ADMUX|LOC_u8SelectChannel; //SET CHANNEL
	SET_BIT(ADCSRA,ADATE);//AutoTriggerEnable
	
	SET_BIT(SFIOR,ADTS0);
	CLR_BIT(SFIOR,ADTS1);
	CLR_BIT(SFIOR,ADTS2);/*ANALOG COMPARATOR MODE*/
	
	if(LOC_u8SelectStatus==POLLING)
	{
	while((GET_BIT(ADCSRA,ADIF))==0)
	{
		
	}
	Clear_ADIF();//CLEAR ADC FLAG
   	
	}
	else if(LOC_u8SelectStatus==INTERRUPT)
	{
	 SET_BIT(ADCSRA,ADIE);//ADC INTERRUPT ENABLE 
 	 
	}
	
	

	#elif  SelectMode==ExternalInterrupt
	ADMUX=ADMUX&0b11100000; //CLEAR ADMUX
	ADMUX=ADMUX|LOC_u8SelectChannel; //SET CHANNEL
	SET_BIT(ADCSRA,ADATE);//AutoTriggerEnable
	
	CLR_BIT(SFIOR,ADTS0);
	SET_BIT(SFIOR,ADTS1);
	CLR_BIT(SFIOR,ADTS2);/*EXTERNAL INTERRUPT MODE*/
	
	if(LOC_u8SelectStatus==POLLING)
	{
	while((GET_BIT(ADCSRA,ADIF))==0)
	{
		
	}
	Clear_ADIF();//CLEAR ADC FLAG
	}
	else if(LOC_u8SelectStatus==INTERRUPT)
	{
	 SET_BIT(ADCSRA,ADIE);//ADC INTERRUPT ENABLE 
	}
	
	#else
	#error  "wrong choice"
	#endif
	return ADC;	
}





