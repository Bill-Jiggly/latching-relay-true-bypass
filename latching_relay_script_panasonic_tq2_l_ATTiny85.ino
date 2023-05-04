#include <Bounce2.h>

const int relay_pos = 2;
const int relay_neg = 3;
const int led_pin = 4;
const int switch_pin = 1;

#define switch_on LOW
#define switch_off HIGH
#define relay_on LOW
#define relay_off HIGH

byte mode = 0;

Bounce bouncer = Bounce();

void setup() 
{ pinMode(switch_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(relay_pos, OUTPUT);
  pinMode(relay_neg, OUTPUT);
  bouncer .attach(switch_pin);
  bouncer .interval(50);
}

void loop() {
  bouncer.update ( );
  switch(mode)
  {
    case 0: 
      if (bouncer.read() == LOW)
      { digitalWrite(relay_pos, relay_on);
        digitalWrite(relay_neg, HIGH);
        digitalWrite(led_pin, HIGH);
        mode = 1;
      }
      break;
    case 1:
      if ( bouncer.read() == HIGH){
        mode = 2;        
      }
      break;
    case 2:
      if ( bouncer.read() == LOW )
      {
        digitalWrite(relay_pos, relay_off);
        digitalWrite(relay_neg, LOW);
        digitalWrite(led_pin, LOW);
        mode = 3;
      }
      break;
    case 3:
      if ( bouncer.read() == HIGH )
        mode = 0;
      break;
  }


}