
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/*1- ADC Enable
 * Selection 1 :Enable
 * Selection 2:Disable
 * */
#define ADC_Status Enable

/*2- Reference Voltage selection
 * Selection 1: External_Ref_Voltage
 * Selection 2: AVCC_Ref_Voltage
 * Selection 3:Internal_Ref_Voltage
 * */
#define Voltage_Selection  RefVoltage

/* 3- Data Adjustment Direction
 * Selection 1: Left Adjust
 * Selection 2: Right Adjust
 * */
#define Data_ADJ_DIR   LeftAdj

/* 4- Prescaler Selection
 * Selection 1: Prescaler2
 * Selection 2: Prescaler4
 * Selection 3: Prescaler8
 * Selection 4: Prescaler16
 * Selection 5: Prescaler32
 * Selection 6: Prescaler64
 * Selection 7: Prescaler128

 * */
#define Prescaler CLK_128



/*5- Interrupt Enable *
 * Selection 1: Enable
 * Selection 2:Disable
 * */

#define Interrupt Disable


#define ADC_u32TimeoutAvl  10000000000

#endif