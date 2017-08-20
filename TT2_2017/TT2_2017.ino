/*
 * © COPYRIGHT COASTERCUM.COM 2017 
 * MSTETSON@COASTERCUM.COM
 * 8/20/2017
 */


#import <Arduino.h>   //can delete this if u want
//#import for screen

const int ride_input = 24;  //From chubasco

const int show_start = 26;  //Pin to tell PI to start show
const int show_stop = 27;   //Pin to tell Pi to stop show
const int show_stop_early = 28; //Pin to tell Pi to stop (stopped by operator)

int writeDelay = 10;    //delay between sending the high and low signal (in ms)

unsigned long show_start_time = 0;     //Time that show was started
unsigned long cycle_time = 120000;   //2 minutes

boolean cycle_time_elapsed = false; //Has the cycle time elapsed (if false stopped early)
boolean cycle_active = false;       //Is cycle active?



void setup() {
  Serial.begin(9600);
  Serial.println("Sketch is starting...");
  //Inputs:
  pinMode(ride_input, INPUT);
  //Outputs:
  pinMode(show_start, OUTPUT);
  pinMode(show_stop, OUTPUT);
  pinMode(show_stop_early, OUTPUT);
  
  digitalWrite(ride_input, LOW);
}

void loop() {
  if(digitalRead(ride_input) == HIGH) {
    if(!cycle_active) {
      //start show!:
      digitalWrite(show_start, HIGH);
      delay(writeDelay);
      digitalWrite(show_start, LOW);
      
      //Start timer
      show_start_time = millis();
      
      cycle_active = true;
      Serial.println("Show start signal sent!");
    }
  }
  else {
    if(cycle_time_elapsed) {
      //Ride cycle was normal
      digitalWrite(show_stop, HIGH);
      delay(writeDelay);
      digitalWrite(show_stop, LOW);
      
      Serial.println("Show stop signal sent");
    }
    else {
      //Ride Stopped Early
      digitalWrite(show_stop_early, HIGH);
      delay(writeDelay);
      digitalWrite(show_stop_early, LOW);
      
      Serial.println("Show stop early signal sent");
    }
    cycle_active = false;
    cycle_time_elapsed = false;
  }
  
//run the time keeeeper
  if(cycle_active) {
    time_keeper();
  }
}

void time_keeper() {
    unsigned long current_time = millis();
    if((current_time - show_start_time) > cycle_time) {
      cycle_time_elapsed = true;
      Serial.println("Cycle Time Elapsed");
    }
    else {
      //cycle time has not elapsed
    }
}

