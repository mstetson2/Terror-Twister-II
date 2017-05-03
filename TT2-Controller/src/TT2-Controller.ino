#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
 * Terror Twister II
 * Controls
 * Updated: 4/26/2017
 */

/*
 * Pin Setup:
 * PIN  DESCRIPTION
 * 0:   RIDE STATUS CONNECTION
 * 1:   SONG 1
 * 2:   SONG 2
 * 3:   SONG 3
 * 4:   SONG 4
 * 5:   SONG 5
 * 6:   SONG 6
 * 7:   SONG 7
 * 8:   SONG 8
 * 9:   RANDOM SONG
 * 10:  STOP SIGNAL
 * 11:  SPARE
 * 12:  SPARE
 * 13:  RIDE STATUS INDICATOR (LED)
 */

const int rideStatusPin   = 0;
const int playSong1       = 1;
const int playSong2       = 2;
const int playSong3       = 3;
const int playSong4       = 4;
const int playSong5       = 5;
const int playSong6       = 6;
const int playSong7       = 7;
const int playSong8       = 8;
const int playSongRandom  = 9;
const int stopCyclePin    = 10;
const int rideStatusLed   = 13;
/*
const int spare11         = 11;
const int spare12         = 12;
const int spare13         = A0;
const int spare14         = A1;
const int spare15         = A2;
const int spare16         = A3;
const int spare17         = A4;
const int spare18         = A5;
*/

//Global Variables:
int connectionStatus = 0;    //Set true while rideStatusPin is HIGH
boolean cycleActive = false;
boolean cycleElapsed = false;
boolean rideWasStopped = false; //True when ride cycle stopped early

unsigned long currentTime = 0;
unsigned long cycleStartTime = 0;        //Is set when cycle begins
unsigned long cycleLengthTime = 150000;  //2.5 minutes
unsigned long startSignalDelay = 10;     //how many ms to send the signal to the pi

int songNumber = 0;             //Keeps track of current song


void setup() {
  Serial.begin(9600); //start serial

  //configure pins:
  //Inputs
  pinMode(rideStatusPin, INPUT);
  //Outputs
  pinMode(playSong1, OUTPUT);
  pinMode(playSong2, OUTPUT);
  pinMode(playSong3, OUTPUT);
  pinMode(playSong4, OUTPUT);
  pinMode(playSong5, OUTPUT);
  pinMode(playSong6, OUTPUT);
  pinMode(playSong7, OUTPUT);
  pinMode(playSong8, OUTPUT);
  pinMode(playSongRandom, OUTPUT);
  pinMode(stopCycle, OUTPUT);
  pinMode(rideStatusLed, OUTPUT);

  digitalWrite(rideStatusPin, HIGH);

  digitalWrite(rideStatusLed, HIGH);

  Serial.println("Controller Started.");
  Serial.print("RIDE STATUS PIN STATE: ");  //Check connection
  Serial.print(rideStatusPin);
  Serial.println(" ");                      //New line

  songNumber = 1;

  delay(1000);
  digitalWrite(rideStatusLed, LOW);
}

void loop() {
  // Engine Functions
  //connectionStatus = digitalRead(rideStatusPin);  //Check connection status //TODO: check to see if boolean works here
  currentTime = millis();       //Set current ms

  if(digitalRead(rideStatusPin) == LOW) {
    if(!cycleActive) {
      startCycle(); //start cycle with song songNumber;
    }
    else {
      //do nothing if ride has started, just means cycle is active
    }
  }
  else {  //if connection is false
    if(cycleActive) { //if ride cycle is set to active (in progress)
      //check if proper cycle or ride stop:
      if(cycleElapsed) {
        //PROPER CYCLE
        stopCycle(1);
        songChange();
        cycleActive = false;
      }
      else {  //ride cycle was stopped early
        //RIDE STOPPED CYCLE
        stopCycle(0);
      }
    }
    else {
      //do nothing while ride stopped
    }
  }

  //Check cycle time:
  if(currentTime - cycleStartTime > cycleLengthTime) {
    cycleElapsed = true;
  }


//Print info:
Serial.println(connectionStatus);
}

//Starts the cycle
//Chooses the song and send command to proper show
void startCycle() {
  //determine the song to play and send the signal
  if(songNumber == 1) {
    digitalWrite(playSong1, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong1, LOW);
  }
  else if(songNumber == 2) {
    digitalWrite(playSong2, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong2, LOW);
  }
  else if(songNumber == 3) {
    digitalWrite(playSong3, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong3, LOW);
  }
  else if(songNumber == 4) {
    digitalWrite(playSong4, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong4, LOW);
  }
  else if(songNumber == 5) {
    digitalWrite(playSong5, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong5, LOW);
  }
  else if(songNumber == 6) {
    digitalWrite(playSong6, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong6, LOW);
  }
  else if(songNumber == 7) {
    digitalWrite(playSong7, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong7, LOW);
  }
  else if(songNumber == 8) {
    digitalWrite(playSong8, HIGH);
    delay(startSignalDelay);
    digitalWrite(playSong8, LOW);
  }

  cycleStartTime = currentTime;
  cycleActive = true;
  rideWasStopped = false;

 Serial.println(" ");
 Serial.print("CYCLE STARTED WITH SONG: ");
 Serial.print(songNumber);
 Serial.println("\n");
}

//Stops the cycle
//Determines if ride was stopped early or not
void stopCycle(int wasProperCycle) {
  //  1 if proper
  //  0 if not (ride stop)
  if(wasProperCycle == 1) {
    //end cycle normally

  }
  else {
    //end cycle with ride stop
    digitalWrite(stopCyclePin, HIGH);
    delay(startSignalDelay);
    digitalWrite(stopCyclePin, LOW);

    rideWasStopped = true;

   Serial.println(" ");
   Serial.print("RIDE WAS STOPPED BY THE OPERATOR WITH SECONDS ELAPSED: ");
   Serial.print((currentTime - cycleStartTime)/1000);
   Serial.println("\n");
  }

  cycleStartTime = 0;
  cycleActive = false;
}

void songChange() {
  if(songNumber < 8) {  //check if reached final song
    songNumber++;       //since it has not, increment song
  }
  else {
    songNumber = 1;
    //this is where the random song selection will be handled
  }

 Serial.println(" ");
 Serial.print("NEXT SONG: ");
 Serial.print(songNumber);
 Serial.println("\n");
}
