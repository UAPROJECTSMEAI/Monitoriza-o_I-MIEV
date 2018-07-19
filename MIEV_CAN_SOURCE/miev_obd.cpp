
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "miev_obd.h"
#include <fstream>
using namespace std;

typedef uint8_t byte;

void MIEV_CAN::receive_values(uint32_t id, uint8_t len, uint8_t data[])                                      
{
  switch (id){
  //Estado da chave
    case 0x101:
      key_status(len, data);
      break;
    //Travão posição
    case 0x208:    
      brake_position(len, data);
      break;
    //Acelarador posição
    case 0x210:
      throttle_position(len, data);
      break;
    //Estado do travão
    case 0x231:
      brake_status(len, data);
      break;
    //Posição Volante
    case 0x236:
      str_wheel(len, data);
      break;
    //Mudança Engatada
    case 0x285:
      gear_position(len, data);
      break;
    case 0x286:
      onboard_charge(len, data);
      break;
    case 0x298:
      temp_rpm_motor(len, data);
      break;
    case 0x346:
      autonomy(len, data);
      break;
    case 0x373:
      battery_value(len, data);
      break;
    case 0x374:
      battery_percentage(len, data);
      break;
    case 0x389:
      charge_value(len, data);
      break;
    case 0x3A4:
      buttons_state_air(len, data);
      break;
    case 0x412:
      odometry(len, data);
      break;
    case 0x424:
      light_state(len, data);
      break;
  }
}

void MIEV_CAN::key_status(uint8_t len, uint8_t data[]){
  if(data[0]==0x04){
    key_state=1;
  }
  else{
    key_state=0;
  }
}

void MIEV_CAN::brake_status(uint8_t len, uint8_t data[]){
  if(data[4]==0x02){
    brake_state=1;
  }
  else{
    brake_state=0;
  }
}

void MIEV_CAN::brake_position(uint8_t len, uint8_t data[]){

  brake_pos=(((data[2] * 256 + data[3]) - 24576.0) / 640) * 100.0;
}

void MIEV_CAN::throttle_position(uint8_t len, uint8_t data[]){
  
  throttle_pos=float((data[2]/(250))*100);
}

void MIEV_CAN::gear_position(uint8_t len, uint8_t data[]){
  if (data[0]==0x50){
    gear=0;
  }
  else if(data[0]==0x52){
    gear=1;
  }
  else if(data[0]==0x20){
    gear=8;
  }
  else if(data[0]==0x4E){
    gear=2;
  }
  else if(data[0]==0x44){
    gear=3;
  }
  else{
    gear=data[0];
  }
}

void MIEV_CAN::str_wheel(uint8_t len, uint8_t data[]){
  
  steering_wheel=(((data[0]*256)+data[1])-4096)/2;
  steering_moment=(((data[2]*256)+data[3])-4096)/2;
}

void MIEV_CAN::onboard_charge(uint8_t len, uint8_t data[]){

  temp_charge_onboard=data[3]-40;
}

void MIEV_CAN::temp_rpm_motor(uint8_t len, uint8_t data[]){
  
  temp_motor=data[3]-40;
  rpm_motor=((data[6]*256)+data[7])-10000;
} 

void MIEV_CAN::autonomy(uint8_t len, uint8_t data[]){

  autonomy_km=data[7];
}

void MIEV_CAN::battery_value(uint8_t len, uint8_t data[]){
  //Valor varia entre 343.2 V && 389.7 V
  volt_battery=((data[4]*256)+data[5])/10;
  //Valor varia entre -164.18 Amp até 76.54 Amp 
  amp_battery=((data[2]*256)+((data[3]-128)*256))/100;
}

void MIEV_CAN::battery_percentage(uint8_t len, uint8_t data[]){

  perc_battery=(data[1]-10)/2;
}

void MIEV_CAN::charge_value(uint8_t len, uint8_t data[]){
  volt_ac_charger=data[1];
  amp_ac_charger=data[6]/10;
  power_ac_charger=(amp_ac_charger*volt_ac_charger*0.9);
}

void MIEV_CAN::buttons_state_air(uint8_t len, uint8_t data[]){
  state_bt_temp=data[0]&&0x0F;
  state_bt_fan=data[1]&&0x0F;
  bt_air_state.ac_on=(data[0]>>7)&&0x01;
  bt_air_state.heater_max_on=(data[0]>>6)&&0x01;
  bt_air_state.air_recycle=(data[0]>>5)&&0x01;
  bt_air_state.air_point=(data[1]>>5)&&0x07;
}

void MIEV_CAN::odometry(uint8_t len, uint8_t data[]){
  speed=data[1];
  odometer=(((data[2]*256)+data[3])*256)+data[4];
}

void MIEV_CAN::light_state(uint8_t len, uint8_t data[]){
    if((data[1]&&0x01)!=0){
      bt_lights.right_blink=1;
    }
    else{
      bt_lights.right_blink=0;
    }

    if((data[1]&&0x02)!=0){
      bt_lights.left_blink=1;
    }
    else{
      bt_lights.left_blink=0;
    }

    if((data[1]&&0x04)!=0){
      bt_lights.highbeams=1;
    }
    else{
      bt_lights.highbeams=0;
    }

    if((data[1]&&0x20)!=0){
      bt_lights.mediumbeams=1;
    }
    else{
      bt_lights.mediumbeams=0;
    }

    if((data[1]&&0x40)!=0){
      bt_lights.park_light=1;
    }
    else{
      bt_lights.park_light=0;
    }

    if((data[2]&&0x01)!=0){
      bt_lights.door_open=1;
    }
    else{
      bt_lights.door_open=0;
    }

    if((data[2]&&0x80)!=0){
      bt_lights.ac_plug=1;
    }
    else{
      bt_lights.ac_plug=0;
    }
}