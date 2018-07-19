/*
  MIEV-ATLASCAR II - DECRYPTING ECU VIA CAN

  Luis Cristovão Nº80886
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
    float steering_moment=0;
    int odometer=0;
    int key_state=0;
    char message[128];
    char gear='\0';
    float temp_charge_onboard=0;
    float temp_motor=0;
    int rpm_motor=0;
    int autonomy_km=0;
    float volt_battery=0;
    float amp_battery=0;
    float perc_battery=0;
    float volt_ac_charger=0;
    float amp_ac_charger=0;
    float power_ac_charger=0;
    int state_bt_temp=0;
    int state_bt_fan=0;
    struct bt_air_state_st{
             bool ac_on=0;
             bool heater_max_on=0;
             bool air_recycle=0;
             int air_point=0;
           }bt_air_state;
    struct bt_lights_st{
             bool right_blink=0;
             bool left_blink=0;
             bool highbeams=0;
             bool mediumbeams=0;
             bool park_light=0;
             bool door_open=0;
             bool ac_plug=0;
           }bt_lights;

/*********************************************************************************************************
 *  metodos 
 *********************************************************************************************************/ 
private:
    void key_status(uint8_t len, uint8_t data[]);
    void brake_status(uint8_t len, uint8_t data[]);
    void brake_position(uint8_t len, uint8_t data[]);
    void throttle_position(uint8_t len, uint8_t data[]);
    void gear_position(uint8_t len, uint8_t data[]);
    void str_wheel(uint8_t len, uint8_t data[]);
    void onboard_charge(uint8_t len, uint8_t data[]);
    void temp_rpm_motor(uint8_t len, uint8_t data[]);
    void autonomy(uint8_t len, uint8_t data[]);
    void battery_value(uint8_t len, uint8_t data[]);
    void battery_percentage(uint8_t len, uint8_t data[]);
    void charge_value(uint8_t len, uint8_t data[]);
    void buttons_state_air(uint8_t len, uint8_t data[]);
    void odometry(uint8_t len, uint8_t data[]);
    void light_state(uint8_t len, uint8_t data[]);
public:
 
    void receive_values(uint32_t id, uint8_t len, uint8_t data[]);

};
#endif
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
