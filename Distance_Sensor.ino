/*
VCC to +5V
GND to ground
TRIG to digital pin 12
ECHO to digital pin 13
*/

#include <LiquidCrystal.h>



const int TRIG_PIN = 12;
const int ECHO_PIN = 13;
const int LED_PIN = 8;
const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
boolean ledState = LOW;

char val;
double distanceCm, distanceIn;

void establishContact(){
  lcd.print("Connecting...");
  while( Serial.available() <= 0){
    Serial.println("A");
    delay(300);
  }
  lcd.clear();
  lcd.print("Success!");
  delay(5000);
  lcd.clear();
}
 
void setup() 
{
  // initialize serial communication:
  pinMode(LED_PIN, OUTPUT); // Set pin as OUTPUT
  lcd.begin(16, 2);
  //initialize serial communications at a 9600 baud rate
  Serial.begin(9600);
  establishContact();

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  // set up the LCD's number of columns and rows:

  
}

double getDistance(char metric = 'i'){
  double duration, distance;
 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  if (metric == 'c'){
  distance = duration / 29.1 / 2 ;
}
  else if (metric == 'i'){
  distance = duration / 74 / 2;
}
  return distance;
}

 
void loop()
{
  
  if(digitalRead(LED_PIN) == HIGH){
    distanceCm = getDistance('c');

    if(distanceCm < 445 && distanceCm > 3){
      lcd.print("In: ");
      lcd.print(getDistance('i'));

    }
    else{
      lcd.print("Out of Range");
    }
  }

  if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val

    if(val == '1') //if we get a 1
    {
       ledState = !ledState; //flip the ledState
       digitalWrite(LED_PIN, ledState); 
    }
  } 
    else {
    Serial.println("Hello, world!"); //send back a hello world
    }
  delay(150);
  lcd.clear();
}
