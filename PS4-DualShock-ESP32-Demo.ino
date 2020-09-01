#include "hid_server.h"

void setup() {
  Serial.begin(115200);

  // init bluetooth hid
  hid_init("ds4esp32");
}

void loop() {
  
  // update the bluetooth edr/hid stack
  hid_update(); 

  uint8_t buf[512];
  
  //read data from JoyStick
  int n = hid_get(buf,sizeof(buf));    // called from emulation loop

  //alt. read data from JoyStick
///  l2_recv(1, buf,sizeof(buf));

  //display data from JoyStick first 16 bytes
  for (uint8_t tmp=0;tmp<16;tmp++) {
     Serial.print(buf[tmp]);  
     Serial.print(".");  
  }  
  Serial.println(); 

}
