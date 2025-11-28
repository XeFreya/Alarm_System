#include "mcc_generated_files/../mcc_generated_files/adc.h"
#include "ADC.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"

uint16_t ADC_Read(uint8_t channel){

    ADC_SelectChannel(channel);
    
    ADC_StartConversion();
    
    while (!ADC_IsConversionDone());
    
    return ADC_GetConversionResult();
    
}
