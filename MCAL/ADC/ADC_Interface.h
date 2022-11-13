#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



typedef enum
{

Not_OK,
OK,
NULL_Pointer,
Busy_Func
	
}ADC_Error_State;


typedef enum
{
	Idel,
	Running
	
}ADC_eBusyState;


void ADC_voidInit(void);



ADC_Error_State ADC_u8GetChannelReadingSynch(u8 Copy_u8Channel , u16 * Copy_u16Reading);

ADC_Error_State ADC_u8GetChannelReading_A_Synch(u8 Copy_u8Channel , u16 * Copy_u16Reading , void (* Copy_pvNotificationFunc)(void) );



#endif