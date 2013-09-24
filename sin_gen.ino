#include <EF_AD9850.h>

#define REST      11
#define FQUP      10
#define CLK        9
#define BitData    8

EF_AD9850 AD9850(CLK, FQUP, REST, BitData);
unsigned long value = 0;

void setup(){
  AD9850.init();
  AD9850.reset();
  
  Serial.begin(115200);
}


void loop(){
  if(Serial.available()) {
    delay(10);
    int buff;
    unsigned long new_value = 0;
        
    while(Serial.available()) {
      buff = Serial.read();
      if (buff == '-') {
        value = value / 2;
        break;
      } else if (buff == '+') {
        value = value * 2;
        break;
      }

      new_value = new_value * 10 + buff - '0';
    }

    if (new_value != 0) {
      value = new_value;
    }
    Serial.print("Setting frequency: ");
    Serial.print(value);
    Serial.println(" Hz");
    AD9850.wr_serial(0x00,value);
  }
}

