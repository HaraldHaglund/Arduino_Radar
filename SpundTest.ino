#include <NewPing.h>
#include <Servo.h>

int triggerPin = 11;
int echoPin = 10;
int usDistance = 40; //in cm
int pirIn =  9;
int ledPin = 13;
int calibrationTime = 10;  //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int servo = 8;
NewPing sonar(triggerPin,echoPin,usDistance); 
Servo myservo;

void setup() {
pinMode(pirIn, INPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
myservo.attach(8);

//give the sensor some time to calibrate
  delay(500);
  Serial.print("calibrating sensor for " + calibrationTime);
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(i + 1);
      Serial.print(" ");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    //Calibration completed
}
void loop() { 
  if (digitalRead(pirIn) == HIGH){//Intrudor! Turn on motor and scan with US.
  for(int i = 0; i < 3; i++){ //How many times we want to scan the area
  scan();
  }
  }
}
void scan(){
  int pos = 15;
  for (pos = 15; pos <= 165; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //Send values to Serial
    Serial.print(pos);
    Serial.print(",");
    Serial.print(sonar.ping_cm());
    Serial.print(".");
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 165; pos >= 15; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print(pos);
    Serial.print(",");
    Serial.print(sonar.ping_cm());
    Serial.print(".");
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
