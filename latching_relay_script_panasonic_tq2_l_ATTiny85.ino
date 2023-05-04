#include <Bounce2.h>
// Bounce 2 library initialized, this will come in handy for debouncing switch. All debouncing does is make sure that when the switch is pushed
// the microcontroller doesnt get confused, when a connection is made there can be noise within the circuit, this delay time stops the
// microcontroller from seeing the noise as further inputs.
// This library can be downloaded through the Arduino IDE. 


// Use Variables to give names to pins for later reference, makes it easier to follow what's happening in the circuit.
// Using the "const int," is setting variables that cannot be changed once declared, we're not going to change our pins in a circuit otherwise would use just "int" 
const int relay_pos = 2;
const int relay_neg = 3;
const int led_pin = 4;
const int switch_pin = 1;

// Using #define to seperate the two sets of variables, just so it's easier to follow. 
#define switch_on LOW
#define switch_off HIGH
#define relay_on LOW
#define relay_off HIGH

// When powered on this sets the mode to "off" state 
byte mode = 0;

// Setting up bounce library to be used further down. 
Bounce bouncer = Bounce();

// Sets pin names up with their function, inputs are to be read, outputs are to be written. 
void setup() 
{ pinMode(switch_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(relay_pos, OUTPUT);
  pinMode(relay_neg, OUTPUT);
 // What do we want debouncing, the switch pin of course. 
  bouncer .attach(switch_pin);
 // With an interval of 50ms, this can be a bit overkill for some people but I like it like this, feel free to change it to whatever you like,
 //most people use 35ms or over. 
  bouncer .interval(50);
}

//The main event! So here we start at "mode 0" which means the relay is set to the off position which means it's bypassing the circuit, going from your guitar's
//input straight the output. This loop is going to be running the entire time the pedal is powered on and will be cycling through these pieces of code every time
//the button is pushed 

void loop() {
//We are telling bouincer to update every time the switch gets pushed to run the bouncer code in the background. 
  bouncer.update ( );
//Here we are initializing "switch states" in C++, this is essentially a deck of 4 cards, the one on the top is being moved to the bottom every time the mode is 
//changed and will constantly run almost like a conveyor belt.   
  switch(mode)
  {
    case 0: //The pedal is currently off and we want to turn it on so when the button is pushed... 
      if (bouncer.read() == LOW) // When the switch is hit it completes a connection to ground so the chip will see "LOW" 
      { digitalWrite(relay_pos, relay_on); 
       // As latching relays are usually "LOW" activated it means that they will need a low reading on the positive terminal
       //and a high reading on the negitive terminal in order to switch       
        digitalWrite(relay_neg, HIGH);
        digitalWrite(led_pin, HIGH); // This sends charge to the LED to show that the pedal is now "on" to the user. 
        mode = 1;
      }
      break; //Telling the chip to not do anything further. 
    case 1: //Telling the chip not to do anything when the switch is released after pushing. 
      if ( bouncer.read() == HIGH){
        mode = 2;        
      }
      break;
    case 2: // This part is telling the chip to switch the pedal off, it's just the opposite of what happened to turn it on. 
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
