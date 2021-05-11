#ifndef DW_UTIL_H_
#define DW_UTIL_H_

#define PERIODE 20.0


// Offset for delay 1
float offset1;
// Offset for delay 2
float offset2;

/**
 * @brief Configure all the necessary registers for the microcontroller
 */
void setRegisters();

/** 
 * @brief Set the OCR1A-register based on the prescaling and the given delay
 * 
 * @param delay The amount of delay to wait in ms
*/
void setOCR(float delay);

#endif // DW_UTIL_H_