#ifndef BLUETOOTH_BLUETOOTH_H_
#define BLUETOOTH_BLUETOOTH_H_


/**
 * @brief Wait until there is unread data in the data buffer and
 * return the data
 * 
 * @return 8 data bits 
 */
unsigned char Bluetooth_Receive();

/**
 * @brief Empty the data buffer (Deletes unread data!)
 * 
 */
void FlushBuffer();
#endif // BLUETOOTH_BLUETOOTH_H_