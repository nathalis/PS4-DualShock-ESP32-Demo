#include "hid_server.h"

void setup() {
  Serial.begin(115200);

  // init bluetooth hid
  hid_init("ds4esp32");
}

uint8_t JOY_UP=0;
uint8_t JOY_DOWN=0;
uint8_t JOY_LEFT=0;
uint8_t JOY_RIGHT=0;

uint8_t JOY_CROSS=0;
uint8_t JOY_SQUARE=0;
uint8_t JOY_CIRCLE=0;
uint8_t JOY_TRIANGLE=0;

uint8_t JOY_SHARE=0; //(START)
uint8_t JOY_OPTIONS=0; //(SELECT)



void loop() {
  
  // update the bluetooth edr/hid stack
  hid_update(); 

  uint8_t buf[512];
  
  //read data from JoyStick
  int n = hid_get(buf,sizeof(buf));    // called from emulation loop

  //alt. read data from JoyStick
///  l2_recv(1, buf,sizeof(buf));


if (buf[0]==161) { // If connected read JoyStick

  uint8_t JOYBUTTON=buf[6];
  ///Serial.println(JOYBUTTON);

  if ( JOYBUTTON<8 && JOYBUTTON % 8 == 0) {JOY_UP=1;}
  if ( JOYBUTTON % 8 == 1) {JOY_UP=1; JOY_RIGHT=1;}
  if ( JOYBUTTON % 8 == 2) {JOY_RIGHT=1;}
  if ( JOYBUTTON % 8 == 3) {JOY_RIGHT=1; JOY_DOWN=1;}
  if ( JOYBUTTON % 8 == 4) {JOY_DOWN=1;}
  if ( JOYBUTTON % 8 == 5) {JOY_DOWN=1; JOY_LEFT=1;}
  if ( JOYBUTTON % 8 == 6) {JOY_LEFT=1;}
  if ( JOYBUTTON % 8 == 7) {JOY_LEFT=1; JOY_UP=1;}
  if (((JOYBUTTON>>3)&1) != 0) {
    JOY_UP=0;
    JOY_DOWN=0;
    JOY_LEFT=0;
    JOY_RIGHT=0;

    JOY_CROSS=0;
    JOY_SQUARE=0;
    JOY_CIRCLE=0;
    JOY_TRIANGLE=0;
  }  

  if ( JOYBUTTON>8 && ((JOYBUTTON>>4)&1) != 0) {JOY_SQUARE=1; }
  if ( JOYBUTTON>8 && ((JOYBUTTON>>4)&2) != 0) {JOY_CROSS=1; }
  if ( JOYBUTTON>8 && ((JOYBUTTON>>4)&4) != 0) {JOY_CIRCLE=1; }
  if ( JOYBUTTON>8 && ((JOYBUTTON>>4)&8) != 0) {JOY_TRIANGLE=1; }

  if (JOY_UP==1) Serial.println("JOY_UP");
  if (JOY_DOWN==1) Serial.println("JOY_DOWN");
  if (JOY_LEFT==1) Serial.println("JOY_LEFT");
  if (JOY_RIGHT==1) Serial.println("JOY_RIGHT");
  if (JOY_CROSS==1) Serial.println("JOY_CROSS");
  if (JOY_SQUARE==1) Serial.println("JOY_SQUARE");
  if (JOY_CIRCLE==1) Serial.println("JOY_CIRCLE");
  if (JOY_TRIANGLE==1) Serial.println("JOY_TRIANGLE");

}

  //display data from JoyStick first 16 bytes
/*  for (uint8_t tmp=0;tmp<16;tmp++) {
     Serial.print(buf[tmp]);  
     Serial.print(".");  
  }  
  Serial.println(); 
*/
}
