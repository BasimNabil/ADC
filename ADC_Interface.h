#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

/* ADC Multiplexer Selection Register - ADMUX*/
#define REFS1   7//ADC VREF
#define REFS0   6//ADC VREF
#define ADLAR   5//ADC ADJUST LEFT OR RIGHT
#define MUX4    4//ADC CHANNEL
#define MUX3    3//ADC CHANNEL
#define MUX2    2//ADC CHANNEL
#define MUX1    1//ADC CHANNEL
#define MUX0    0//ADC CHANNEL

/*ADC Control and Status Register A - ADCSRA*/
#define ADEN    7 //ADC ENABLE
#define ADSC    6 //ADC START CONVERSION
#define ADATE   5 //ADC AUTO TRIGGER ENABLE
#define ADIF    4 //ADC INTERRUPT FLAG
#define ADIE    3 //ADC INTERRUPT ENABLE
#define ADPS2   2 //ADC PRESCALER2
#define ADPS1   1 //ADC PRESCALER1
#define ADPS0   0 //ADC PRESCALER0

/*ADC CHANNELS*/
#define AN0    0
#define AN1    1
#define AN2    2
#define AN3    3
#define AN4    4
#define AN5    5
#define AN6    6
#define AN7    7

/*ADC ADC Auto Trigger Source - SFIOR */
#define ADTS0   5//SFIOR BIT 5
#define ADTS1   6//SFIOR BIT 6
#define ADTS2   7//SFIOR BIT 7



/*ADC AUTO TRIGGER MODES*/
#define SingleConversionMode       0
#define FreeRunningMode            1
#define AnalogComparator           32
#define ExternalInterrupt          3

/*ADC INTERRUPT*/
#define ISR_ADC()           void __vector_16(void)__attribute__((signal)); \
							void __vector_16(void)


#define SelectMode   FreeRunningMode
#define Clear_ADIF()    SET_BIT(ADCSRA,ADIF)

/*ADC RESULT MODE*/
#define POLLING       0
#define INTERRUPT     1

/*ADC FUNCTION PROTOTYPES*/
void ADC_VidInit(void);
u16 ADC_u16GetRes(u8 LOC_u8SelectChannel,u8 LOC_u8SelectStatus);
void ADC_VidStartConversion(void);
void ADC_VidSetCallBack(void (*LocalPfunc) (void));




#endif