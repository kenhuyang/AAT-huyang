#include "config.h"
#include "Arduino.h"
#include "functions.h"
#include "sensors.h"
#include <Wire.h>

char read_sensors = 0;

// Sensor_board,   x,y,z
int acc_raw[3]  = {1,2,3};  
int gyro_raw[3] = {4,5,6};
int mag_raw[3]  = {7,8,9};

unsigned char channel_mapping[13];
//unsigned char PpmIn_PpmOut[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

unsigned char PpmIn_PpmOut[13] = {0,
1,2,3,4,5,6,7,8,9,10,11,12};

unsigned int analog_readings[4];

extern unsigned long buttonDownTime;

int test =0;
int test2 =0;

long channel_value[13] ={2100,
2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100};

long PPMIn[13] ={2100,
2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100};

unsigned char channel_number =1;

// For PPM detection
signed long last_time = 0;
signed long this_time = 0;
signed long servo_time = 0;

unsigned char read_ppm_channel =1;

int temp2 =0;

int timeTest = 0;

char shift = 0;

char time_out =0;

void printPPM() {

  for (char j =1; j<13; j++) {
  Serial.print(channel_value[j]);
  Serial.print(",");
  }
  Serial.println();
  
}

void init_timer_interrupt() {
  
#if (DEBUG)    
    Serial.println("Timer interrupt initialised");
#endif
  
   TCCR0A = 
   (0<<WGM00) |
   (1<<WGM01) |
   (0<<COM0A1) |
   (0<<COM0A0) |
   (0<<COM0B1) |
   (0<<COM0B0);  
   
   // 61 hz update-rate:
    TCCR0B =
    (0<<FOC0A)| // 
    (0<<FOC0B)| // 
    (1<<CS00) | //Prescale 1024 
    (0<<CS01) | //Prescale 1024  
    (1<<CS02) | //Prescale 1024
    (0<<WGM02);
  
    TIMSK0 = 
    (0<<OCIE0B) |
    (1<<OCIE0A) |
    (1<<TOIE0);       

    OCR0B = 64*2; 
    OCR0A = 64*2; 



}

// ===========================
// Timer 0 compare A vector
// Sensor-interrupt
// ===========================

ISR(TIMER0_COMPA_vect) {
  
  /*
  for (unsigned char i = 0; i < 4; i++) {
    analog_readings[i]  = analogRead(i);
  }
  */
  
  // Reset counter - should be changed to CTC timer mode. 
  TCNT0= 0;

  // Used to check timing - have the previous calculations been done?
  // Will always show in start, but should stop when initialised. 
  if (shift == 1) {
//   digitalWrite(7,HIGH); 
   shift = 0;
  }
  else {
//   digitalWrite(7,LOW);
  shift = 1; 
  }
  

#if (DEBUG == 1)  
    if (read_sensors == 1) {
      time_out++;
      if (time_out > 10) {
//      Serial.println("Timing problem!!!"); 
      time_out = 0;  
    }
      
    }
#endif
       read_sensors = 1;
       buttonDownTime += 16; // every 16 milliseconds, at 61 hz.

  }
  

void get_data() {
}

void set_pwm() {
}


// ===========================
// Test function
// ===========================

void test_output() {
 Serial.print("Acc x: ");
 Serial.print(acc_raw[0]);
 Serial.print(" y: ");  
 Serial.print(acc_raw[1]);
 Serial.print(" z: ");  
 Serial.println(acc_raw[2]); 
 
}

