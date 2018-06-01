
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
  //Medida da Velocidade Atual 
  if(id==0x412){
    calc_speed(len, data);
  }
  //Estado da chave
  else if(id==0x101){
    key_status(len, data);
  }
  //Travão posição
  else if(id==0x208){    
    brake_position(len, data);
  }
  //Acelarador posição
  else if(id==0x210){
    throttle_position(len, data);
    //sprintf(message, "%.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X ", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
  }
  //Estado do travão
  else if(id==0x231){
    brake_status(len, data);
  }
  //Posição Volante
  else if(id==0x236){
    str_wheel(len, data);
  }
  //Mudança Engatada
  else if(id==0x285){
    gear_position(len, data);
  }
  /*//Temp e rpm motor
  else if(id==0x298){
    printf("Temperatura do motor e rpm.\n");
  }*/
}

void MIEV_CAN::calc_speed(uint8_t len, uint8_t data[]){
  speed=data[1];
  odometer=(((data[2]*256)+data[3])*256)+data[4];
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
  int16_t aux=0;
  aux=data[2]|data[3]<<8;
  brake_pos=((aux-MIN_BRAKE)/(MAX_BRAKE-MIN_BRAKE))*100;
}

void MIEV_CAN::throttle_position(uint8_t len, uint8_t data[]){
  int16_t aux=0;
  aux=data[2];
  throttle_pos=(aux/(250))*100;
}

void MIEV_CAN::gear_position(uint8_t len, uint8_t data[]){
  char aux[23];
  sprintf(aux, "%.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
  if (aux == "07 D0 14 00 8E FE OC 10"){
    gear='P';
  }
  else if(aux == "07 D0 14 00 8E FE OE 30"){
    gear='R';
  }
  else if(aux == "07 D0 14 00 8E FE OE 10"){
    gear='D';
  }
  else if(aux == "07 D1 14 00 8E FE OE 10"){
    gear='B';
  }
  else if(aux == "07 D1 14 00 8E FE OE 10"){
    gear='C';
  }
}

void MIEV_CAN::str_wheel(uint8_t len, uint8_t data[]){
  steering_wheel=(((data[0]*256)+data[1])-4096)/2;
}