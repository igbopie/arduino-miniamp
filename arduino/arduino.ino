#include <IRremote.h>
#include <IRremoteInt.h>
#include <SimpleTimer.h>

// Install library https://github.com/z3t0/Arduino-IRremote
//const int LED_PIN = 4;
//const int IR_PIN = 2;
//const int BTN_PIN = 3;
//
//const int MODE_NORMAL = 0;
//const int MODE_LEARN_UP = 1;
//int buttonState = 0; 
//int mode = 0;
//
//long upVolume = 0;
//long downVolume = 0;
//
//int LED_TIME_EXTENDED = 2000;
//int LED_TIME = 200;
//int currentLedTime = 0;
//int blinkLed = HIGH;
//
//IRrecv irrecv(IR_PIN);
//decode_results results;

SimpleTimer timer;

//-------------
// START SPDIF
//-------------
const int PIN_SPDIF = A3;
const int SPDIF_THRESHOLD = 5;
const int SPDIF_STATUS_OFF = 0;
const int SPDIF_STATUS_ON = 1;
const long SPDIF_STATUS_TIMEOUT = 10000;
int spdifStatus = SPDIF_STATUS_OFF;
int spdifValue = 0;
int spdifTimerId = 0;

void setupSPDIF() {
  pinMode(PIN_SPDIF, INPUT);
}

void spdifOff() {
  Serial.println("OFF"); 
  spdifStatus = SPDIF_STATUS_OFF;
}

void processSPDIF() {
  
  //SPDIF
  spdifValue = analogRead(PIN_SPDIF);
  if (spdifStatus != SPDIF_STATUS_ON && spdifValue > SPDIF_THRESHOLD) {
    Serial.println("ON"); 
    spdifStatus = SPDIF_STATUS_ON;
  } else if (spdifStatus != SPDIF_STATUS_OFF && spdifTimerId == 0) {
    spdifTimerId = timer.setTimeout(SPDIF_STATUS_TIMEOUT, spdifOff);
  }

  if (spdifValue > SPDIF_THRESHOLD && spdifTimerId > 0) {
    timer.deleteTimer(spdifTimerId);
    spdifTimerId = 0;
  }
}
//-------------
// END SPDIF
//-------------

//-------------
// START DAC
//-------------
const int PIN_DAC_LED = 13;
const int PIN_DAC = 2;


void setupDAC() {
  pinMode(PIN_DAC, OUTPUT);
}

void processDAC() {
  if (spdifStatus == SPDIF_STATUS_ON) {
    digitalWrite(PIN_DAC_LED, HIGH);
    digitalWrite(PIN_DAC, HIGH);
  } else {
    digitalWrite(PIN_DAC_LED, LOW);
    digitalWrite(PIN_DAC, LOW);
  }
}

//-------------
// END DAC
//-------------

//-------------
// START RELAYS
//-------------
const int PIN_RELAYS = 3;


void setupRelays() {
  pinMode(PIN_RELAYS, OUTPUT);
}

void processRelays() {
  if (spdifStatus == SPDIF_STATUS_ON) {
    digitalWrite(PIN_RELAYS, LOW);
  } else {
    digitalWrite(PIN_RELAYS, HIGH );
  }
}

//-------------
// END RELAYS
//-------------

// the setup routine runs once when you press reset:
void setup() {
  setupSPDIF();
  setupDAC();
  setupRelays();
//  
//  pinMode(LED_PIN, OUTPUT);
//  pinMode(BTN_PIN, INPUT);
//  irrecv.enableIRIn(); 
//  
//  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);

  Serial.begin(9600); 
}

// the loop routine runs over and over again forever:
void loop() {
  timer.run();
  
  processSPDIF();
  processDAC();
  processRelays();
  
  // print out the value you read:
  //Serial.println(sensorValue);
  //delay(1);        // delay in between reads for stability
  
   // read the state of the pushbutton value:
//  buttonState = digitalRead(BTN_PIN);
//  
//  if (buttonState == HIGH) {
//    // turn LED on:
//    mode = MODE_LEARN_UP;
//  } else {
//    // turn LED off:
//  }
//
//  if (irrecv.decode(&results)) {
//    irrecv.resume(); // Receive the next value
//
//    if (results.value == upVolume) {
//      currentLedTime = LED_TIME;
//      Serial.println(results.value, HEX);
//    }
//
//    if (mode == MODE_LEARN_UP) {
//      currentLedTime = LED_TIME_EXTENDED;
//      upVolume = results.value;
//      
//      Serial.println(upVolume, HEX);
//      Serial.println(results.value, HEX);
//    }
//    mode = MODE_NORMAL;
//  }
//
//  if (mode == MODE_LEARN_UP) {
//    digitalWrite(LED_PIN, blinkLed);
//    blinkLed = blinkLed == HIGH? LOW: HIGH;
//  } else if (currentLedTime > 0) {
//    currentLedTime -= 100;
//    digitalWrite(LED_PIN, HIGH);
//  } else {
//    digitalWrite(LED_PIN, LOW);
//  }
//  delay(100);
}
