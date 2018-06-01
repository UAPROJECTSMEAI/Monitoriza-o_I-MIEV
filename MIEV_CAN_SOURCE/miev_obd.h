/*
  MIEV-ATLASCAR II - DECRYPTING ECU VIA CAN
  */
#ifndef _MIEV_OBD_H_
#define _MIEV_OBD_H_

#include <inttypes.h>

#define MAX_BRAKE 0x61BF
#define MIN_BRAKE 0x6000

class MIEV_CAN
{

public:
  float speed=0;
  float brake_pos=0;
  int brake_state=0;
  float throttle_pos=0; 
  float steering_wheel=0;
  float odometer=0;
  int key_state=0;
  char message[128];
  char gear='\0';
/*********************************************************************************************************
 *  metodos 
 *********************************************************************************************************/ 
private:
    void calc_speed(uint8_t len, uint8_t data[]);
    void key_status(uint8_t len, uint8_t data[]);
    void brake_status(uint8_t len, uint8_t data[]);
    void brake_position(uint8_t len, uint8_t data[]);
    void throttle_position(uint8_t len, uint8_t data[]);
    void gear_position(uint8_t len, uint8_t data[]);
    void str_wheel(uint8_t len, uint8_t data[]);

public:
 
    void receive_values(uint32_t id, uint8_t len, uint8_t data[]);

};
#endif
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
