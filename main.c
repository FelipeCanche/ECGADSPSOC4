/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================

EN ESTA VERSION SE APLICA UN FILTRO TIPO FIR PARA ELIMINAR LA FRECUENCIA DE 60HZ, SE OBTIENEN RESULDATOS BUENOS
SE OBTIENE UNA MEJOR RESPUESTA DEL SISTEMA AL ESTAR TRABAJANDO A UNA VELOCIDAD DE 533SPS
SE CONFIGURAN R2 Y R3 DEL ARCHIVO ADS1293.C
*/
#include "project.h"
#include "Config.h"

/*************************************/
///////////////VARIABLES///////////////
uint32 milis = 0;
uint32 ValorUmbral=0;

uint32 PrintOn=OFF;
uint32 arrayDataC1 = ZERO;
uint32 arrayDataC2 = ZERO;
uint32 arrayDataC3 = ZERO;

int32 LEAD_I   = ZERO;
int32 LEAD_II  = ZERO;
int32 LEAD_III = ZERO;
int32 LEAD_V   = ZERO;

int32 LEAD_I_250   = ZERO;
int32 LEAD_II_250  = ZERO;
int32 LEAD_III_250 = ZERO;
int32 LEAD_V_250   = ZERO;

int32 NEW_LEAD_I   = ZERO;
int32 NEW_LEAD_II  = ZERO;
int32 NEW_LEAD_III = ZERO;
int32 NEW_LEAD_V   = ZERO;
int32 OLD_LEAD_I   = ZERO;
int32 OLD_LEAD_II  = ZERO;
int32 OLD_LEAD_III = ZERO;
int32 OLD_LEAD_V   = ZERO;
int32 CUAD_LEAD_I   = ZERO;
int32 CUAD_LEAD_II  = ZERO;
int32 CUAD_LEAD_III = ZERO;
int32 CUAD_LEAD_V   = ZERO;

uint32 status=ZERO;
uint32 array[CH_DATA_SIZE];
uint8 read_buf[CH_DATA_SIZE+1];
uint8 read_buf2[CH_DATA_SIZE+1];
uint8 count = CH_DATA_SIZE;
////////////Filter variables////////////
//**************************Kalman Filter *********************************//
#define TotalDatos 100 //Numero de Taps para el filtro
#define TotalDatosProm 10
//#define TotalDatosProm 16// Numero de Taps para el filtro pasabajas
/*************************Variables del Filtro rechaza Banda*****************/
float VectorFiltro[TotalDatos]={};
float ValorFiltroActual=0;
int32 ValorFiltroAntiguo=0;
float FiltroProm=0;
float FiltroSprom=0;
int32 FirstTime=OFF;
/*************************Variables del Filtro rechaza Banda*****************/

/*************************Variables del Promediador*****************/
float VectorProm[TotalDatos]={};
float ValorActual=0;
int32 ValorAntiguo=0;
float Prom=0;
float Sprom=0;
/*****************VARIABLES BPMS**************************/

/*****************Coeficienes Filtro rechaza banda 50Hz **************************/
const float32 Hvector[TotalDatos]={ 
    //FS = 250Hz, No Taps = 100,CutOFF = 60Hz, BandWidth = 10Hz, Type = Hamming
-0.000297307968139648, 0.00079643726348877,-0.000340104103088379, 0.000555753707885742,-0.00109016895294189, 7.62939453125E-06,-0.00156974792480469, 0.000710010528564453,
    -0.000426530838012695, 0.00280082225799561, 0.00052034854888916, 0.00281250476837158,-0.00231516361236572,-0.000602483749389648,-0.00626027584075928,
    -0.000855803489685059,-0.00358355045318604, 0.0065147876739502, 0.00301122665405273, 0.0110847949981689,-0.000668168067932129, 0.00236821174621582,-0.0142834186553955,
    -0.00587749481201172,-0.0155038833618164, 0.0064692497253418, 0.00158250331878662, 0.0250439643859863, 0.00637698173522949, 0.0172284841537476,-0.0183364152908325,
    -0.00670993328094482,-0.0365370512008667,-0.000486016273498535,-0.0155436992645264, 0.0363651514053345, 0.00831079483032227, 0.0467175245285034,-0.0159997940063477, 
    0.0142133235931396,-0.0605170726776123, 0.00260984897613525,-0.0595602989196777, 0.0511507987976074,-0.0300189256668091, 0.105813264846802,-0.0609654188156128, 
    0.133893132209778,-0.230023503303528, 0.60128653049469, 0.60128653049469,-0.230023503303528, 0.133893132209778,-0.0609654188156128, 0.105813264846802,-0.0300189256668091,
    0.0511507987976074,-0.0595602989196777, 0.00260984897613525,-0.0605170726776123, 0.0142133235931396,-0.0159997940063477, 0.0467175245285034, 0.00831079483032227, 
    0.0363651514053345,-0.0155436992645264,-0.000486016273498535,-0.0365370512008667,-0.00670993328094482,-0.0183364152908325, 0.0172284841537476, 0.00637698173522949, 
    0.0250439643859863, 0.00158250331878662, 0.0064692497253418,-0.0155038833618164,-0.00587749481201172,-0.0142834186553955, 0.00236821174621582,-0.000668168067932129, 
    0.0110847949981689, 0.00301122665405273, 0.0065147876739502,-0.00358355045318604,-0.000855803489685059,-0.00626027584075928,-0.000602483749389648,-0.00231516361236572, 
    0.00281250476837158, 0.00052034854888916, 0.00280082225799561,-0.000426530838012695, 0.000710010528564453,-0.00156974792480469, 7.62939453125E-06,-0.00109016895294189, 
    0.000555753707885742,-0.000340104103088379, 0.00079643726348877,-0.000297307968139648
};


////////////////////////////////////////
/*********************************************************/
//void printChannel1(uint8 channel);
/*********************************************************/

//////////////////////// DRDY Data ready ////////////////////
CY_ISR(TimeUpdate)
{       
//    milis=milis+1;
    if(ValorUmbral>8000)
        LED_Write(ON);
    else
        LED_Write(OFF);
                
    Timer_ClearFIFO(); // Clear interruption flag 
//    DrdyLevel_ClearPending();
}
/*********************************************************/

//////////////////////// DRDY Data ready ////////////////////
CY_ISR(Sampling250)
{       
   LEAD_II_250 = LEAD_II; 
   Timer_250_ClearInterrupt(Timer_250_INTR_MASK_TC); 
//    DrdyLevel_ClearPending();
}
/*********************************************************/

//////////////////////// DRDY Data ready ////////////////////
CY_ISR(DRDY_READ)
{       
    status= CyEnterCriticalSection();
        DRDY_ClearInterrupt(); // Clear interruption flag 
        ADS1x9x_Stream_Reg_Read(read_buf,count); 
        LEAD_V =  ((uint32_t)read_buf[0] << 16) | ((uint16_t) read_buf[1]<<8) | read_buf[2]; //            
        LEAD_II = ((uint32_t)read_buf[3] << 16) | ((uint16_t) read_buf[4]<<8) | read_buf[5]; //
        LEAD_I =  ((uint32_t)read_buf[6] << 16) | ((uint16_t) read_buf[7]<<8) | read_buf[8]; //
        
        PrintOn=ON; //Turn on the flag      
    CyExitCriticalSection(status);
//    DrdyLevel_ClearPending();
}
/*********************************************************/


int main(void)
{
    wait500Ms(); //wait 500 ms
    CyGlobalIntEnable; /* Enable global interrupts. */
    
/****************************Inicializar el Vector de Datos************************************/    
    for(uint32 init=0;init<TotalDatos;init++) // inicializar vectores de Filtro y Promedio Movil
    {
        VectorProm[init]=0.0;
        VectorFiltro[init]=0.0;
    }
/****************************Inicializar el Vector de Datos************************************/   
    Timer_Start();
    init_psoc(); // Initialization  psoc modules  
    Init_ADS1x9x();
    DrdyLevel_StartEx(DRDY_READ);//Interruption enable   
    isr_timer1_StartEx(TimeUpdate);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {    
        /* Place your application code here. */
        if(PrintOn==ON)
        {           
            
            VectorFiltro[0]=LEAD_II;
            
            for(uint32 P=0;P<TotalDatos;P++)
                FiltroProm=FiltroProm+(VectorFiltro[P]*Hvector[P]);
            
            FiltroSprom=FiltroProm/TotalDatos;
            ValorFiltroAntiguo=trunc(FiltroSprom); // Dato de salida del Filtro Notch 50-60HZ

                            
            for(uint32 C=TotalDatos;C>0;C--)
                VectorFiltro[C]=VectorFiltro[C-1];
            
            FiltroProm=0;
            FiltroSprom=0;    
//                                 
///**************************** Realiza el promedio del Vector de Datos*********************************/     
///**************************** Filtro PasaBajas *********************************/     
            
            NEW_LEAD_II=ValorFiltroAntiguo-OLD_LEAD_II;            
            OLD_LEAD_II=ValorFiltroAntiguo;                
            CUAD_LEAD_II = NEW_LEAD_II*NEW_LEAD_II;
                
            VectorProm[0]=CUAD_LEAD_II;
            
            for(uint32 P=0;P<TotalDatosProm;P++)
                Prom=Prom+(VectorProm[P]);
//                Prom=Prom+(VectorProm[P]*HPvector[P]);  //Filtro LP          
            Sprom=Prom/TotalDatosProm;
            ValorAntiguo=trunc(Sprom);  // Dato de salida del Filtro LP 
            
            
            for(uint32 C=TotalDatosProm;C>0;C--)
                VectorProm[C]=VectorProm[C-1];
            
            Prom=0;
            Sprom=0;                
//            LEAD_III = LEAD_II-LEAD_I;
               
//            sprintf(uartMessage, "%li\t",LEAD_I); // Print Channel 1
//            UART_UartPutString(uartMessage);             
//            sprintf(uartMessage, "%li\n",LEAD_II); // Print Channel 1
//            UART_UartPutString(uartMessage); 
//            sprintf(uartMessage, "%li\n",LEAD_V); // Print Channel 1
//            UART_UartPutString(uartMessage);  
            
//            /////////////////////FILTRO 60HZ BICUADRATICO /////////////////////////////////////
          
            ValorUmbral=ValorAntiguo*100;
                
            sprintf(uartMessage, "%ld\n",LEAD_II); // Print Filter LEAD I
            UART_UartPutString(uartMessage);  
//            
//            /////////////////////FILTRO 60HZ BICUADRATICO /////////////////////////////////////
            
            PrintOn=OFF; //Clear Flag            
        }       
    }
}
/**********************************************************************************************************/

/**********************************************************************************************************/
//void printChannel1(uint8 channel)
//{
//    /*******************
//    Cree esta funcion porque al momento de tratar de visualizar todos los canales debido a 
//    la magnitud de los valores obtenidos no se puede visualizar bien cada una de las señales
//    por lo que imprimo solo un canal para no tener problemas. 
//    *******************/
// switch (channel)
//    {
//    case 1:
//            arrayDataC1 = ((uint32_t)read_buf[0] << 16) | ((uint16_t) read_buf[1]<<8) | read_buf[2]; //    
//            sprintf(uartMessage, "%li\n",arrayDataC1); // Print Channel 1
//            UART_UartPutString(uartMessage);        
//        break;
//    case 2:
//            arrayDataC2 = ((uint32_t)read_buf[3] << 16) | ((uint16_t) read_buf[4]<<8) | read_buf[5]; //
//            sprintf(uartMessage, "%li\n",arrayDataC2); // Print Channel 1
//            UART_UartPutString(uartMessage);        
//        break;
//    case 3:
//            arrayDataC3 = ((uint32_t)read_buf[6] << 16) | ((uint16_t) read_buf[7]<<8) | read_buf[8]; //
//            sprintf(uartMessage, "%li\n",arrayDataC3); // Print Channel 1
//            UART_UartPutString(uartMessage);        
//        break;  
//            
//    default:break;    
//    }
//}
/**********************************************************************************************************/

/* [] END OF FILE */
