#include <IRremote.h>
#include <IRremoteInt.h>

/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
const int LED_PIN = 4;
const int IR_PIN = 2;
const int BTN_PIN = 3;

const int MODE_NORMAL = 0;
const int MODE_LEARN_UP = 1;

// variables will change:
int buttonState = 0; 
int mode = 0;

long upVolume = 0;
long downVolume = 0;

int LED_TIME_EXTENDED = 2000;
int LED_TIME = 200;
int currentLedTime = 0;
int blinkLed = HIGH;

IRrecv irrecv(IR_PIN);
decode_results results;


// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  irrecv.enableIRIn(); 
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // print out the value you read:
  //Serial.println(sensorValue);
  //delay(1);        // delay in between reads for stability
  
   // read the state of the pushbutton value:
  buttonState = digitalRead(BTN_PIN);
  
  if (buttonState == HIGH) {
    // turn LED on:
    mode = MODE_LEARN_UP;
  } else {
    // turn LED off:
  }

  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value

    if (results.value == upVolume) {
      currentLedTime = LED_TIME;
      Serial.println(results.value, HEX);
    }

    if (mode == MODE_LEARN_UP) {
      currentLedTime = LED_TIME_EXTENDED;
      upVolume = results.value;
      
      Serial.println(upVolume, HEX);
      Serial.println(results.value, HEX);
    }
    mode = MODE_NORMAL;
  }

  if (mode == MODE_LEARN_UP) {
    digitalWrite(LED_PIN, blinkLed);
    blinkLed = blinkLed == HIGH? LOW: HIGH;
  } else if (currentLedTime > 0) {
    currentLedTime -= 100;
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(100);
}
