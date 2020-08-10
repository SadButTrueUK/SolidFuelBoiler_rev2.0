#include <p18cxxx.h>
#include <adc.h>
#include "module_analog_inputs.h"


/* 
������� ����������� ��� �������������� 10 ��� � ��������������� �3950
�������� �� 0 �� 99 �������� � ����� 1 ������
������� � ��������� 10-������� ���
*/
const rom uint16_t M_AI_Table_thermoresistor[] =
{
789, 780, 770, 760, 749, 739, 728, 718, 707, 696, 685, 673, 662, 651, 639, 628, 616, 604, 593, 581,
570, 558, 546, 535, 523, 512, 501, 489, 478, 467, 456, 445, 435, 424, 414, 404, 394, 384, 374, 364,
355, 346, 336, 328, 319, 310, 302, 294, 286, 278, 270, 263, 256, 249, 242, 235, 228, 222, 216, 210,
204, 198, 193, 187, 182, 177, 172, 167, 162, 158, 153, 149, 145, 141, 137, 133, 129, 126, 122, 119,
115, 112, 109, 106, 103, 100, 98, 95, 92, 90, 87, 85, 83, 81, 78, 76, 74, 72, 70, 69
};


/* 
������� ����������� ��� ������� ����������� PT100
�������� �� 0 �� 850 �������� � ����� 10 ��������
������� � ��������� 10-������� ���
�������� ����������� ����� � ���� ����� �� 0 �� 85
*/
const rom uint16_t M_AI_Table_PT100[] = 
{
59, 71, 83, 95, 107, 119, 131, 143, 155, 167, 178, 190, 202, 213, 225, 236, 247, 259, 270, 281,
292, 303, 314, 325, 336, 347, 358, 369, 380, 390, 401, 412, 422, 433, 443, 453, 464, 474, 484,
495, 505, 515, 525, 535, 545, 555, 565, 574, 584, 594, 604, 613, 623, 632, 642, 651, 661, 670,
679, 689, 698, 707, 716, 725, 734, 743, 752, 761, 770, 779, 788, 796, 805, 814, 822, 831, 839, 
848, 856, 865, 873, 881, 890, 898, 906, 914
};

//#define ALL_ANALOG_CHANNELS_IN_USE

// ���������� �������� � ������� ����������� �������������� �� 0 �� 100 �������� � ��������� ��� (10 ���)
#define SIZE_TABLE_TERMO_RES  	sizeof(M_AI_Table_thermoresistor) / sizeof(M_AI_Table_thermoresistor[0])  

// ���������� �������� � ������� ����������� PT100 �� 0 �� 850 �������� � ��������� ��� (10 ���)
#define SIZE_TABLE_PT100	  	sizeof(M_AI_Table_PT100) / sizeof(M_AI_Table_PT100[0])     

#ifdef ALL_ANALOG_CHANNELS_IN_USE
    #define QUANTITY_ANALOG_CHANNELS    6U 	   		//����� ���������� ������� ���
    #define QUANTITY_TEMPER_CHANNELS    5U          //���������� ������� ��� ��������� �����������  
#else
    #define QUANTITY_ANALOG_CHANNELS    3U 	   		//����� ���������� ������� ���
    #define QUANTITY_TEMPER_CHANNELS    2U          //���������� ������� ��� ��������� �����������
#endif

#define QUANTITY_DC_CURRENT_CHANNELS    1U          //���������� ������� ��� ��������� ����������� ����         
#define QUANTITY_OF_SHR                 6 			//��� ���������� ���������� (���������� ������� ������)
#define QUANTITY_ELEMENTS_OF_SUMMARY  	1U << QUANTITY_OF_SHR  //�������� ������ �����			 
#define QUANTITY_TABLES_TEMPERATURE		2
#define ADC_CH0_TRIS                    TRISAbits.TRISA0
#define ADC_CH1_TRIS                    TRISAbits.TRISA1
#define ADC_CH2_TRIS                    TRISAbits.TRISA2
#define ADC_CH3_TRIS                    TRISAbits.TRISA3
#define ADC_CH4_TRIS                    TRISAbits.TRISA5
#define ADC_CH012_TRIS                  TRISHbits.TRISH4
#define ADC_MASK_CHANNELS               0b1110111111100000  //����� ���������� ������� (1 - �������� ����/�����, 0 - ���������� ����)



const rom uint8_t M_AI_Type_Table_Sorted[QUANTITY_TABLES_TEMPERATURE] = {TABLE_SORTED_UP, TABLE_SORTED_DOWN};

const rom uint8_t M_AI_Offset_in_table[QUANTITY_TABLES_TEMPERATURE][QUANTITY_TABLES_TEMPERATURE] = 
{
{0, SIZE_TABLE_PT100 - 1},
{SIZE_TABLE_TERMO_RES - 1, 0}
};

const rom uint16_t* M_AI_ptrTable [QUANTITY_TABLES_TEMPERATURE] = {M_AI_Table_PT100, M_AI_Table_thermoresistor};
#ifdef ALL_ANALOG_CHANNELS_IN_USE
    const rom uint8_t M_AI_Mask_ADC_channels [QUANTITY_ANALOG_CHANNELS] = 
                    { ADC_CH3, ADC_CH1, ADC_CH12, ADC_CH0, ADC_CH4, ADC_CH2 }; 
#else
    const rom uint8_t M_AI_Mask_ADC_channels [QUANTITY_ANALOG_CHANNELS] = 
                    { ADC_CH3, ADC_CH1, ADC_CH12 }; 
#endif
const rom uint8_t M_AI_Size_Table_temperature [QUANTITY_TABLES_TEMPERATURE] = {SIZE_TABLE_PT100, SIZE_TABLE_TERMO_RES};

//���������� �������� ���������� � ����������� ����
ADC_Data  M_AI_ADC_Data[QUANTITY_ANALOG_CHANNELS] = {0};


/*������� ���������� ����� ������� �������� ������ ��� */
ADC_Data* M_AI_Get_ADC_Data(uint8_t index)
{
	return (ADC_Data*)&M_AI_ADC_Data[index];
}  

//������������� ������ ���
void M_AI_ctor( void )
{
    OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_12_TAD,  
            ADC_CH0 & ADC_CH1 & ADC_CH2 & ADC_CH3 &  
            ADC_CH4 & ADC_CH12 & ADC_INT_OFF & ADC_REF_VDD_VSS, ADC_MASK_CHANNELS);
    ADC_CH0_TRIS   = IN;   
    ADC_CH1_TRIS   = IN;  
    ADC_CH2_TRIS   = IN;  
    ADC_CH3_TRIS   = IN;  
    ADC_CH4_TRIS   = IN;  
    ADC_CH012_TRIS = IN;      
}



//����� � ������� �������� ����������� �� ������ ������ ��� (������� ��������� ������)
//� ����������� �� ���� ������� (������������� �� ����������� ��� �� �������� � ����������� ��  ��������� uint8_t sort_direction)
uint8_t M_AI_Search(uint16_t value, const rom uint16_t* table, const uint8_t length, uint8_t sort_direction)
{
	uint8_t U, L, M;
	
	U = length;
	L = 0;

	while(1)
	{
		 M = (L + U) / 2;
		 if(sort_direction) //������� ������� ��� �������, ��������������� �� �������� (������������� NTC)
		 {
		 	if (value > table[M]) 
		 	U = M; /*- 1*/
		 else
		 	if (value < table[M]) 
		 		L = M; /*+ 1*/
		 	else 
		 		return M;
		 } 
		else  //��� ����� ����������� ��� �������, ��������������� �� ����������� (������ PT100)
		{
			if (value < table[M]) 
		 	U = M; /*- 1*/
		 else
		 	if (value > table[M]) 
		 		L = M; /*+ 1*/
		 	else 
		 		return M;
		 }
		if ((U - L) == 1U) 
		 	return L;
	}
} 


/*
����� Run ������ ��������� ���
*/
void M_AI_Run (void)
{
	static uint8_t index_channel = 0;
	
	M_AI_Processing_ADC (index_channel); //�������������� ���, ���������� �����������
	if( ++index_channel == QUANTITY_ANALOG_CHANNELS ) 
		index_channel = 0; //����� ��� ������ ��������, �������� ����� � ������ �������
	
	SetChanADC(M_AI_Mask_ADC_channels[index_channel]); //����� ���������� ������ ���������
}

/* 
��������� ��� � ��������� ����������� ���������
*/
void M_AI_Processing_ADC (uint8_t index)
{
	if(M_AI_ADC_Data[index].quantity++ < QUANTITY_ELEMENTS_OF_SUMMARY) //��������� � ������������ � �����
	{
		ConvertADC( );
		while( BusyADC( ) );
        M_AI_ADC_Data[index].sum_discr += ReadADC();	//���������� ����� �������� ���������� ������ ���	
		
	}
	else
	{
		M_AI_ADC_Data[index].data_value = M_AI_ADC_Data[index].sum_discr >> QUANTITY_OF_SHR; //���������� ����������
		M_AI_ADC_Data[index].sum_discr = 0;
		M_AI_ADC_Data[index].quantity = 0;
		
        switch(index)
        {    
            case CHN_T_GAS: //��������� �����������
            case CHN_T_WATER:
                if (M_AI_ADC_Data[index].data_value < SHORT_CIRCUIT_SENSOR_THRESHOLD) // �������� �� �� ������� �����������
                {
                    M_AI_ADC_Data[index].param = SHORT_CIRCUIT_SENSOR_VALUE; 
                    return;
                }
                else if (M_AI_ADC_Data[index].data_value > BREAK_SENSOR_THRESHOLD) // �������� �� ����� ������� �����������
                {
                     M_AI_ADC_Data[index].param = BREAK_SENSOR_VALUE;
                    #ifndef NO_SENSOR_GAS
                        return;
                    #else
                        if(index == CHN_T_GAS)	
                        {
                            M_AI_ADC_Data[index].param = 2;  //���� ��������� 20 ��������
                            return;
                        }	
                    #endif
                }
                else if (M_AI_ADC_Data[index].data_value >= SHORT_CIRCUIT_SENSOR_THRESHOLD && 
                         M_AI_ADC_Data[index].data_value < *(M_AI_ptrTable[index] + M_AI_Offset_in_table[index][0])) 
                            M_AI_ADC_Data[index].data_value = *(M_AI_ptrTable[index] + M_AI_Offset_in_table[index][0]);
                else if (M_AI_ADC_Data[index].data_value <= BREAK_SENSOR_THRESHOLD && 
                         M_AI_ADC_Data[index].data_value > *(M_AI_ptrTable[index] + M_AI_Offset_in_table[index][1])) 
                            M_AI_ADC_Data[index].data_value = *(M_AI_ptrTable[index] + M_AI_Offset_in_table[index][1]);

                        //���������� ����������� ������� �� �������
                        M_AI_ADC_Data[index].param = M_AI_Search(M_AI_ADC_Data[index].data_value, M_AI_ptrTable[index],
                                                                 M_AI_Size_Table_temperature[index], M_AI_Type_Table_Sorted[index]); 
                break;
        
            case CHN_I_SUPPLY_12V:
                break;
        }
    }
}
