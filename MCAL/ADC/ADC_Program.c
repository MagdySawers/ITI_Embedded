#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Register.h"

volatile static u16 * ADC_pu16Reading =NULL;
 static void (* ADC_pvCallBackNotificationFunc)(void) = NULL; 

volatile ADC_eBusyState ADC_eState =Idel;

void ADC_voidInit()
{
	
	   /*Voltage Selection*/
	
	#if  Voltage_Selection == RefVoltage
	
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
	
	#elif Voltage_Selection == AVCCVoltage
	
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
	
	#elif  Voltage_Selection == InternalVoltage
	
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
	
	#else
	
    #error "Undifiend Selection of Voltage_Selection"
 
	#endif
	
/**************************************************************/	

	    /*Data Adjust Direction*/
		
	#if    Data_ADJ_DIR == LeftAdj
	
	CLR_BIT(ADMUX,ADMUX_ADLAR);
	
	#elif Data_ADJ_DIR == RightAdj
	
	SET_BIT(ADMUX,ADMUX_ADLAR);
	
	#else
	
	#error "Undifiend Selection of Data_ADJ_DIR"
	
	#endif
	
/**************************************************************/
	

     	/*Prescaler Selection*/
		 
	#if    Prescaler == CLK_2
	
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	CLR_BIT(ADCSRA,ADCSRA_ADPS1);
	CLR_BIT(ADCSRA,ADCSRA_ADPS2);
	
	#elif   Prescaler == CLK_4
	
	CLR_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	CLR_BIT(ADCSRA,ADCSRA_ADPS2);
	
	#elif   Prescaler == CLK_8
	
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	CLR_BIT(ADCSRA,ADCSRA_ADPS2);
	
	#elif   Prescaler == CLK_16
	
	CLR_BIT(ADCSRA,ADCSRA_ADPS0);
	CLR_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);	
	
	#elif   Prescaler == CLK_32
	
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	CLR_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);	
	
	#elif   Prescaler == CLK_64
	
	CLR_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	
	#elif   Prescaler == CLK_128
	
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);	
	
	
	#else 
	
	#error "Undifiend Selection of Prescaler"
		
	#endif
	
/*******************************************************/	

        /* ADC Status */
		
	#if   ADC_Status == Enable
	
	SET_BIT(ADCSRA,ADCSRA_ADEN);
	
	#elif ADC_Status == Disable
	
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
	
	#else
	
	#error "Undifiend Selection of ADC_Status"
	
	#endif
	
/******************************************************/

         /* INTERUPT_Status */
		 
	#if     Interrupt == Disable
	
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
	
	#elif  Interrupt == Enable
	
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	
	#else
	
	#error "Undifiend Selection of Interupt_Status" 
		
    #endif
	
}


/*================================================================================*/


ADC_Error_State ADC_u8GetChannelReadingSynch(u8 Copy_u8Channel , u16 * Copy_u16Reading )
{
	ADC_Error_State Schy_state = OK ;
	
if(ADC_eState==Idel)
{
	if(Copy_u16Reading==NULL)
	{
		Schy_state=NULL_Pointer;
		
	}
	else
	{
		
		ADC_eState=Running;
	
	u32 Local_u32Counter=0;
	/*ADjust the Channel*/
	
	ADMUX&=0xE0;
	ADMUX|=Copy_u8Channel;
	
	/* Start Conversion */
	
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	
	
	while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0  && (Local_u32Counter != ADC_u32TimeoutAvl))
	{
		
		Local_u32Counter++;
		
	}
	if(Local_u32Counter == ADC_u32TimeoutAvl)
	{
		Schy_state=Not_OK;
	}
	else
	{
		/*Clear Flag of conversion complete Flag*/
		
		SET_BIT(ADCSRA,ADCSRA_ADIF);
		
		/*Return the Reading*/
		
		*Copy_u16Reading=ADCL | (u16)ADCH<<8;
		
		/*ADC finshed return it to IDEL state*/
		ADC_eState=Idel;
		
	}
	
	
  }
}
else
{
	Schy_state=Busy_Func;
	
}
	return Schy_state;
	
}


/*=======================================================================*/


ADC_Error_State ADC_u8GetChannelReading_A_Synch(u8 Copy_u8Channel , u16 * Copy_u16Reading , void (* Copy_pvNotificationFunc)(void) )
{
	ADC_Error_State Aschy_state=OK;
	
if(ADC_eState==Idel)
{
		
	
	if(Copy_u16Reading==NULL  ||  Copy_pvNotificationFunc==NULL)
	{
		Aschy_state=NULL_Pointer;
	}
	else
	{
		ADC_eState=Running;
		
		ADC_pu16Reading = Copy_u16Reading;
		
		ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;
		
		
		
		/*ADjust the Channel*/
		ADMUX&=0xE0;
		ADMUX|=Copy_u8Channel;
		
		/* Start Conversion */
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		
		/* Enable Interrupt of ADC */
		SET_BIT(ADCSRA,ADCSRA_ADIE);
			
		
	}
}

else
{
Aschy_state=Busy_Func;	
}
	
	
	
	return Aschy_state;
}






void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	
	/*Reading of ADC*/
	*ADC_pu16Reading=ADCL || (u16)ADCH<<8 ;
	
	
	/*ADC_state is Idel because ADC finshed conversion*/
	ADC_eState=Idel;
	
	/*Invoke the CAll back Func*/
	ADC_pvCallBackNotificationFunc();  //do any thing in this Func After the adc conversion finished 
	
	/*Disable ADC conversion complete*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
	
}
