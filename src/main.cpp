#include <Arduino.h>

const int TRIG_PIN = 10; 
const int ECHO_PIN = 9;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Function to get a stable reading
int getDistance() {
  long duration;
  int dist;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, 25000);
  dist = duration * 0.034 / 2;
  
  if (dist <= 0 || dist > 400) return 400;
  return dist;
}

void loop() {
  // Take 5 readings and use a simple sort to find the median (kills the "geeking" jumps)
  int readings[5];
  for(int i=0; i<5; i++) {
    readings[i] = getDistance();
    delay(10);
  }
  
  // Simple Sort
  for(int i=0; i<4; i++) {
    for(int j=i+1; j<5; j++) {
      if(readings[i] > readings[j]) {
        int temp = readings[i];
        readings[i] = readings[j];
        readings[j] = temp;
      }
    }
  }
  
  // Send the middle value (the most stable one)
  Serial.println(readings[2]);
  delay(30); 
}
