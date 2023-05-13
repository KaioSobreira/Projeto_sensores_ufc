//HC-SR04
int tempPin = 0; 
const int p_trig = 7;
const int p_echo = 6;
//LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

// SENSOR DE GAS
#define sensorgas A1
float sensor_value;
float printable_value;

// Umidade do solo
int moisture = 0;
//_________________________________________________________

void setup() {
//HC-SR04
  pinMode(p_trig,OUTPUT);
  pinMode(p_echo,INPUT);
//LCD
  lcd.begin(16,2);
  lcd.clear();
// Umidade do solo
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}
 
//_________________________________________________________

void loop() {
// Umidade do solo
{
  digitalWrite(A2, HIGH);
  delay(10); 
  moisture = analogRead(A3);
  digitalWrite(A2, LOW);
  Serial.println(moisture);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  if (moisture < 218) {
    digitalWrite(5, HIGH);
  } else {
    if (moisture < 436) {
      digitalWrite(4, HIGH);
    } else {
      if (moisture < 654) {
        digitalWrite(3, HIGH);
      } else {
        if (moisture < 872+1) {
          digitalWrite(2, HIGH);
        }
      }
    }
  }
  delay(100);
}
//HC-SR04
  delay(100);
  Serial.begin(9600);
  long duration, cm;
  int reading = analogRead(tempPin);  
  digitalWrite(p_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(p_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(p_trig,LOW);
  duration = pulseIn(p_echo,HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm); Serial.print(" cm");
  Serial.println();
  delay(1000);
  
//LCD + HC-SR04
  lcd.setCursor(0,0);
  lcd.print(cm);
  lcd.setCursor(3,0);
  lcd.print("cm");

// TEMPERATURA
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ; 
  Serial.print(temperatureC); Serial.print(" Celsius");
  Serial.println();
  lcd.setCursor(6,0);
  lcd.print(temperatureC);
  lcd.setCursor(11,0);
  lcd.print('C'); 
  
//SENSOR DE GAS
  int sensor_value = analogRead(sensorgas);
  printable_value = analogRead(sensorgas);
  Serial.print(printable_value);
  Serial.print(" PPM");
  Serial.println();

// LCD + SENSOR DE GAS
  lcd.setCursor(0,1);
  lcd.print(printable_value);
  lcd.setCursor(6,1);
  lcd.print("PPM");
  
// LCD + SENSOR DE UMIDADE
  lcd.setCursor(10,1);
  lcd.print(moisture);
  lcd.setCursor(13,1);
  lcd.print("U");
  
  delay(1000);
}

//_________________________________________________________

//HC-SR04
long microsecondsToInches(long microseconds) {

  return microseconds / 74 / 2;
}

//HC-SR04
long microsecondsToCentimeters(long microseconds) {

  return microseconds / 29 / 2;
}
