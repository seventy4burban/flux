// Created by RadBench: youtube.com/radbenchyt
// Made for a  Flux Capacitor with a 10 light NanoLed strip
// Modifications by seventy4burban: youtube.com/seventyburban include
// -Updated libaries and code 
// -Changes for DeLorean car install
// -Light Test Mode
// -Sound effects removed and electronic flux sound added
// -Full trilogy soundtrack added
// -Light colors modeified to closer match screen used cars
// -Time travel effect modified to be closer to screen used cars

// Current libaries
// DFRobotDFPlayerMini V1.0.6
// FastLED v3.10.3
// IRremote v4.7.01 

///////////////////////////////////////////////////////////////////////////////////////////

// DFPlayer Stuff
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// RX, TX Connections to DFRobotDFP Player
SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

///////////////////////////////////////////////////////////////////////////////////////////

// IR

uint32_t Previous;
#include <IRremote.hpp>

// Initialize pin 3 as the receiver pin
#define IR_RECEIVE_PIN 3
decode_results results;

// Remote Buttons
#define IR_BUTTON_POWER 0x45
#define IR_BUTTON_0 0x16
#define IR_BUTTON_1 0xC
#define IR_BUTTON_2 0x18
#define IR_BUTTON_3 0x5E
#define IR_BUTTON_4 0x8
#define IR_BUTTON_5 0x1C
#define IR_BUTTON_6 0x5A
#define IR_BUTTON_7 0x42
#define IR_BUTTON_8 0x52
#define IR_BUTTON_9 0x4A
#define IR_BUTTON_VOLUP 0x46
#define IR_BUTTON_VOLDN 0x15
#define IR_BUTTON_UP 0x9
#define IR_BUTTON_DN 0x7
#define IR_BUTTON_PAUSE 0x40
#define IR_BUTTON_PREV 0x44
#define IR_BUTTON_NEXT 0x43

///////////////////////////////////////////////////////////////////////////////////////////

// LEDS

uint8_t hue = 0;

#include <FastLED.h>
#define NUM_LEDS 22
#define DATA_PIN 5
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define VOLTS 5 // max voltage
#define MAX_AMPS 4500 //value in milliamps
#define BRIGHTNESS 60
#define MAX_BRIGHT 255 
#define ledColor Yellow

int delaySpeed = 80;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

  int timeTravel;
  int smoothChase;
  int movieChase;
  int movieSpeed = 34.45;
  int movieChaseSimple;
  int thirtyChase;
  int radChase;
  int radChase2;
  int rainbowChase;
  int testMode;


// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

// Speedometer Stuff
const int analogPin = A0;  //Defines the analog input pin
const int threshold = 982; //Defines the threshold value (approximately 4.8VDC)


///////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  // Single LED
  pinMode(12, OUTPUT);

  // DFPlayer Setup
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online"));

  myDFPlayer.volume(15);  //Set volume value (0 to 30)
  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);

  // STARTUP SOUND AND CHASE
  myDFPlayer.playFolder(1, 1);  //Play flux capacitor sound
  delay(200);
  radChase2 = 1;
  //movieSpeed = 22.97;
  //movieChase = 1;
  // End DFPLayer Setup

  // IR setup
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  
  // LED Setup ///////////////////////////////////////////////////////
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void loop() {
  
  while (!IrReceiver.isIdle());  // if not idle, wait till complete

  unsigned long lastPressTime = 0;
  if (IrReceiver.decode()) {
    if (millis() - lastPressTime > 300) { // 300ms debounce
      // Remote Control Button Functions
      int command = IrReceiver.decodedIRData.command;
      switch (command) {
        case IR_BUTTON_POWER: 
          Serial.println("Pressed POWER");
          Serial.println("Power Off");
          myDFPlayer.stop();
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          FastLED.clear();
          FastLED.show();
          delaySpeed = 20;
          break;

        case IR_BUTTON_0: 
          Serial.println("Pressed 0");
          Serial.println("Playing Flux Sound");
          myDFPlayer.stop();
          myDFPlayer.volume(15);  //Set volume value (0 to 30)
          myDFPlayer.playFolder(1, 1);  //Play flux capacitor sound
          delaySpeed = 20;
          break;
          
        case IR_BUTTON_1: 
          Serial.println("Pressed 1");
          Serial.println("Time Travel");
          timeTravel = 1;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          // set delay speed for time travel
          delaySpeed = 113;
          break;
      
        case IR_BUTTON_2: 
          Serial.println("Pressed 2");
          Serial.println("Smooth Chase");
          timeTravel = 0;
          smoothChase = 1;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_3: 
          Serial.println("Pressed 3");
          Serial.println("30 FPS");
          // set movie speed
          movieSpeed = 33.33;
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 1;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_4: 
          Serial.println("Pressed 4");
          Serial.println("24 FPS");
          Serial.println("Imitating 6 LED from the A Car");
          // set movie speed
          movieSpeed = 22.97;
          // set loop
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 1;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_5: 
          Serial.println("Pressed 5");
          Serial.println("24 FPS Simple");
          // set movie speed
          movieSpeed = 34.45;
          // set loop
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 1;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_6: 
          Serial.println("Pressed 6");
          Serial.println("Rad Chase");
          // set movie speed
          movieSpeed = 66.66;
          // set loop
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 1;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_7: 
          Serial.println("Pressed 7");
          Serial.println("Rad Chase 2");
          //set movie speed
          movieSpeed = 66.66;
          // set loop
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 1;
          rainbowChase = 0;
          testMode = 0;
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_8: 
          Serial.println("Pressed 8");
          Serial.println("Test Mode");
          //set movie speed
          movieSpeed = 66.66;
          // set loop
          timeTravel = 0;
          smoothChase = 0;
          thirtyChase = 0;
          movieChase = 0;
          movieChaseSimple = 0;
          radChase = 0;
          radChase2 = 0;
          rainbowChase = 0;
          testMode = 1;
          delaySpeed = 20;
          break;

        case IR_BUTTON_9: 
          Serial.println("Pressed 9");
          Serial.println("Play Soundtrack");
          myDFPlayer.stop();
          myDFPlayer.volume(25);  //Set volume value (0 to 30)
          myDFPlayer.loopFolder(2);
          myDFPlayer.enableLoop();
          delaySpeed = 20;
          break;
      
        case IR_BUTTON_VOLUP: 
          Serial.println("Pressed Volume Up");
          myDFPlayer.volumeUp();
          break;
      
        case IR_BUTTON_VOLDN: 
          Serial.println("Pressed Volume Down");
          myDFPlayer.volumeDown();
          break;
      
        case IR_BUTTON_UP: { // button up pressed, decrease delay timers - go faster
          if (movieSpeed > 24) {
            movieSpeed = movieSpeed - 10;
          }
          if (delaySpeed > 20) {
            delaySpeed = delaySpeed - 20;
          }
          // Smaller increments for delay speeds under 20
          if (delaySpeed <= 20 && delaySpeed > 4) {
            delaySpeed = delaySpeed - 4;
          }

          Serial.println("Pressed Up");
          break;
        }

        case IR_BUTTON_DN: { // button down pressed increase delays - go slower
          if (movieSpeed < 200) {
            movieSpeed = movieSpeed + 10;
          }
          if (delaySpeed < 160) {
            delaySpeed = delaySpeed + 20;
          }
          
          Serial.println("Pressed Down");
          break;
        }

        case IR_BUTTON_PAUSE: 
          Serial.println("Pressed Play/Pause");
          myDFPlayer.pause();
          break;
        
        case IR_BUTTON_PREV: 
          Serial.println("Pressed Previous Track");
          myDFPlayer.previous();
          break;
      
        case IR_BUTTON_NEXT: 
          Serial.println("Pressed Next Track");
          myDFPlayer.next();
          break;
      }
      lastPressTime = millis();
    }
    IrReceiver.resume();
  }

  //Speedometer to Flux Capacitor Control  
  int sensorValue = analogRead(analogPin); //Read Speedometer Input Voltage

  if (sensorValue >= threshold) {
    for (int i = 0; i < 10; i++) {

        FastLED.setBrightness(MAX_BRIGHT);
        leds[i] = CHSV(28, 170, 100);
        leds[10] = CRGB::White;
        leds[11] = CRGB::White;
        leds[12] = CRGB::White;
        leds[13] = CRGB::White;
        leds[14] = CRGB::White;
        leds[15] = CRGB::White;
        leds[16] = CRGB::White;
        leds[17] = CRGB::White;
        leds[18] = CRGB::White;
        leds[19] = CRGB::White;
        leds[20] = CRGB::White;
        leds[21] = CRGB::White;
        
       FastLED.show();
      }
     
      // Single LED
      digitalWrite(12, HIGH);
      delay(300);
      FastLED.clear();
      FastLED.show();
      
      // Single LED
      digitalWrite(12, LOW);
      delay(400);

      // Second Burst
      for (int i = 0; i < 21; i++) {
        FastLED.setBrightness(MAX_BRIGHT);
        leds[i] = CHSV(28, 170, 100);
        leds[10] = CRGB::White;
        leds[11] = CRGB::White;
        leds[12] = CRGB::White;
        leds[13] = CRGB::White;
        leds[14] = CRGB::White;
        leds[15] = CRGB::White;
        leds[16] = CRGB::White;
        leds[17] = CRGB::White;
        leds[18] = CRGB::White;
        leds[19] = CRGB::White;
        leds[20] = CRGB::White;
        leds[21] = CRGB::White;
        FastLED.show();
      }
      
      // Single LED
      digitalWrite(12, HIGH);
      delay(1000);
      delaySpeed = 80;
      timeTravel = 0;
      radChase2 = 1;
      FastLED.clear();
      FastLED.show();
      
      // Single LED
      digitalWrite(12, LOW);
      FastLED.setBrightness(BRIGHTNESS);
      //          chase();
      //          exit(0);
      //          reset();    
  }
    Serial.println("88 MPH, initating Flux Capacitor");
  

  delay(100);

  //-----------------TimeTravel (Button 1)------------------------

  if (timeTravel == 1) {

    unsigned long currentTime = millis();

    FastLED.setBrightness(BRIGHTNESS);
    // Move LEDS
    for (int i = 0; i < 20; i = i + 1) {

      if (i - 6 >= 0) {
        leds[i - 6] = CHSV(28, 170, 60);
      }
      if (i - 5 >= 0) {
        leds[i - 5] = CHSV(28, 170, 100);
      }
      if (i - 4 >= 0) {
        leds[i - 4] = CHSV(28, 170, 160);
      }
      if (i - 3 >= 0) {
        leds[i - 3] = CHSV(28, 170, 220);
      }
      if (i - 2 >= 0) {
        leds[i - 2] = CHSV(28, 170, 160);
      }
      if (i - 1 >= 0) {
        leds[i - 1] = CHSV(28, 170, 100);
      }
      leds[i] = CHSV(28, 170, 60);
      leds[10] = CRGB::Black;
      leds[11] = CRGB::Black;
      leds[12] = CRGB::Black;
      leds[13] = CRGB::Black;
      leds[14] = CRGB::Black;
      leds[15] = CRGB::Black;
      leds[16] = CRGB::Black;
      leds[17] = CRGB::Black;
      leds[18] = CRGB::Black;
      leds[19] = CRGB::Black;
      leds[20] = CRGB::Black;
      leds[21] = CRGB::Black;


      // Show the leds

      FastLED.show();

      FastLED.clear();
      timeTravel = 1;

      // Wait a little bit
      delay(delaySpeed);

    }

    // Reduce delay time so each sequence is faster than the last
    delaySpeed = delaySpeed * .837;

    if (delaySpeed < 1) {
      // leds[5] = CRGB::Black;

      previousTime = millis();

      if (millis() < previousTime + 4000) {
        // ZIIIP!  Moment of time travel
                
        digitalWrite(12, HIGH);
        for(int y = 0; y < 22; y++) {
          FastLED.setBrightness(MAX_BRIGHT);
          leds[y] = CRGB::White;
          FastLED.show();
          }
                
          delay(3300);
          FastLED.clear();
          FastLED.show();
          //for(int x = 0; x < 9; x++) {
          //leds[x] = CRGB::Black;
          //FastLED.show();
          //}
          // Single LED
          digitalWrite(12, LOW);
          // Delay after white light
          delay(850);
        }
      // First Burst
      for (int i = 0; i < 10; i++) {
        FastLED.setBrightness(MAX_BRIGHT);
        leds[i] = CHSV(28, 170, 100);
        leds[10] = CRGB::White;
        leds[11] = CRGB::White;
        leds[12] = CRGB::White;
        leds[13] = CRGB::White;
        leds[14] = CRGB::White;
        leds[15] = CRGB::White;
        leds[16] = CRGB::White;
        leds[17] = CRGB::White;
        leds[18] = CRGB::White;
        leds[19] = CRGB::White;
        leds[20] = CRGB::White;
        leds[21] = CRGB::White;
        
       FastLED.show();
      }
     
      // Single LED
      digitalWrite(12, HIGH);
      delay(300);
      FastLED.clear();
      FastLED.show();
      // Single LED
      digitalWrite(12, LOW);
      delay(400);

      // Second Burst
      for (int i = 0; i < 21; i++) {
        FastLED.setBrightness(MAX_BRIGHT);
        leds[i] = CHSV(28, 170, 100);
        leds[10] = CRGB::White;
        leds[11] = CRGB::White;
        leds[12] = CRGB::White;
        leds[13] = CRGB::White;
        leds[14] = CRGB::White;
        leds[15] = CRGB::White;
        leds[16] = CRGB::White;
        leds[17] = CRGB::White;
        leds[18] = CRGB::White;
        leds[19] = CRGB::White;
        leds[20] = CRGB::White;
        leds[21] = CRGB::White;
        FastLED.show();
      }
      
      // Single LED
      digitalWrite(12, HIGH);
      delay(1000);
      delaySpeed = 80;
      timeTravel = 0;
      radChase2 = 1;
      FastLED.clear();
      FastLED.show();
      // Single LED
      digitalWrite(12, LOW);
      FastLED.setBrightness(BRIGHTNESS);
      //          chase();
      //          exit(0);
      //          reset();
    }
  } 
  // ----------------- END timeTravel ------------------------------

  //-----------------SMOOTH CHASE (Button 2)------------------------

  if (smoothChase == 1) {
    timeTravel = 0;

    // delaySpeed = 80;
    FastLED.setBrightness(BRIGHTNESS);
    delay(100);

    // Move LEDS
    for (int i = 0; i < 16; i = i + 1) {

      if(i - 6 >= 0) {
        leds[i - 6] = CHSV(32, 128, 20);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 5 >= 0) {
        leds[i - 5] = CHSV(32, 128, 40);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 4 >= 0) {
        leds[i - 4] = CHSV(32, 128, 70);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 3 >= 0) {
        leds[i - 3] = CHSV(32, 128, 180);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 2 >= 0) {
        leds[i - 2] = CHSV(32, 128, 70);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 1 >= 0) {
        leds[i - 1] = CHSV(32, 128, 40);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      leds[i] = CHSV(32, 128, 20);
      leds[10] = CRGB::Black;
      leds[11] = CRGB::Black;
      leds[12] = CRGB::Black;
      leds[13] = CRGB::Black;
      leds[14] = CRGB::Black;
      leds[15] = CRGB::Black;
        

      // Show the leds

      FastLED.show();
      delay(delaySpeed);
      FastLED.clear();
      FastLED.show();
      smoothChase = 1;
      timeTravel = 0;
    }
  }

  //-----------------THIRTY FPS CHASE (Button 3) - For shooting at 30fps------------------------

  if (thirtyChase == 1) {

    timeTravel = 0;
    smoothChase = 0;

    FastLED.setBrightness(BRIGHTNESS);
    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      if(i = 1) {
        leds[0] = CHSV(32, 128, 100);
        leds[1] = CHSV(32, 128, 100);
        leds[2] = CHSV(32, 128, 15);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[2] = CHSV(32, 128, 15);
        leds[3] = CHSV(32, 128, 100);
        leds[4] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[5] = CHSV(32, 128, 100);
        leds[6] = CHSV(32, 128, 100);
        leds[7] = CHSV(32, 128, 15);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[7] = CHSV(32, 128, 15);
        leds[8] = CHSV(32, 128, 100);
        leds[9] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      thirtyChase = 1;

    }
    
  }

  //----------------- MOVIE CHASE (Button 4) - imitates 6 LEDs - matches 24FPS speed from the movie------------------------

  if (movieChase == 1) {
    timeTravel = 0;
    smoothChase = 0;
    FastLED.setBrightness(BRIGHTNESS);

    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      // LED 1
      if(i = 0) {
        leds[0] = CHSV(28, 170, 100);
        leds[1] = CHSV(28, 170, 100);
        
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 2
      if(i = 1) {
        leds[1] = CHSV(28, 170, 100);
        leds[2] = CHSV(28, 170, 100);

        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 3
      if(i = 2) {
        leds[2] = CHSV(28, 170, 100);
        leds[3] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 4
      if(i = 3) {
        leds[4] = CHSV(28, 170, 15);
        leds[5] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 5
      if(i = 4) {
        leds[6] = CHSV(28, 170, 100);
        leds[7] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 6
      if(i = 5) {
        leds[8] = CHSV(28, 170, 100);
        leds[9] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      movieChase = 1;
      smoothChase = 0;
      timeTravel = 0;
    }
  }

  //----------------- MOVIE CHASE SIMPLE (Button 5)------------------------

  if (movieChaseSimple == 1) {

    timeTravel = 0;
    smoothChase = 0;
 
    FastLED.setBrightness(BRIGHTNESS);
    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      if(i = 1) {
        leds[2] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[4] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[6] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[8] = CHSV(28, 170, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      movieChaseSimple = 1;

    }
  }

  //-----------------RAD CHASE (Button 6)------------------------

  if (radChase == 1) {

    timeTravel = 0;
    smoothChase = 0;

    FastLED.setBrightness(BRIGHTNESS);
    // Move LEDS
    for (int i = 0; i < 6; i = i + 1) {

      if(i = 1) {
        leds[0] = CHSV(32, 128, 100);
        leds[1] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[2] = CHSV(32, 128, 100);
        leds[3] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[4] = CHSV(32, 128, 100);
        leds[5] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[6] = CHSV(32, 128, 100);
        leds[7] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 5) {
        leds[8] = CHSV(32, 128, 100);
        leds[9] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      radChase = 1;

    }
  }

  //-----------------RAD CHASE 2 (Button 7)------------------------

  if (radChase2 == 1) {

    timeTravel = 0;
    smoothChase = 0;

    FastLED.setBrightness(BRIGHTNESS);
    // Move LEDS
    for (int i = 0; i < 10; i = i + 1) {

      if(i < 9) {
        leds[i] = CHSV(28, 170, 120);
        leds[i - 1] = CHSV(28, 170, 30);
        leds[i + 1] = CHSV(28, 170, 30);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      radChase2 = 1;

    }
  }

  //-----------------RAINBOW CHASE (Button 8)------------------------

  if (rainbowChase == 1) {

  
      for (int i = 0; i < 10; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 150);
      }
      for (int y = 10; y > 9 && y < 22; ++y) {
        leds[y] = CHSV(hue + (y * 10), 255, 250);
      }
    
      //You can change the pattern speed here
      EVERY_N_MILLISECONDS(1){
        hue++;
      }
      
      FastLED.show();
      rainbowChase = 1;
    }

  //-----------------Test Mode (Button 8)------------------------
  // Test 3 Parallel strips of 10 LEDS (relays) and 4 blocks of 3 LEDs (Door) and 4 Center LEDs in series
  
  if (testMode ==1) {
  FastLED.setBrightness(MAX_BRIGHT);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  /*
  leds[0] = CRGB(204, 47, 0);
  leds[1] = CRGB(219, 102, 0);
  leds[2] = CRGB(227, 158, 0);
  leds[3] = CRGB(118, 184, 13);
  leds[4] = CRGB(0, 118, 104);
  leds[5] = CRGB(0, 100, 134);
  leds[6] = CRGB(0, 124, 181);
  leds[7] = CRGB(70, 90, 178);
  leds[8] = CRGB(109, 71, 177);
  leds[9] = CRGB(135, 59, 156);
  leds[10] = CRGB::Red;
  leds[11] = CRGB::Green;
  leds[12] = CRGB::Blue;
  leds[13] = CRGB::Red;
  leds[14] = CRGB::Green;
  leds[15] = CRGB::Blue;
  leds[16] = CRGB::Red;
  leds[17] = CRGB::Green;
  leds[18] = CRGB::Blue;
  leds[19] = CRGB::Red;
  leds[20] = CRGB::Green;
  leds[21] = CRGB::Blue;
  */
  
  FastLED.show();

  testMode = 1;
  }

}
