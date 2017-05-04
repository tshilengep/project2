#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int tempSensor = 3;
int buzzer = 8;
int led = 7;
float temperature;
//B value of the thermistor
int B = 4275;
int R0 = 100000;
float resistance;

void setup() 
{
    
    pinMode(tempSensor, OUTPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(led,OUTPUT);
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");
    
    delay(1000);
}



void loop() 
{
    int a=analogRead(tempSensor);
    resistance= 1023.0/a-1.0;
    resistance = R0 * resistance;
    temperature = 1.0/(log(resistance/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet

    Serial.print(temperature);
    Serial.print("\n");
    lcd.setCursor(0, 1);

    lcd.print(temperature);
    if(temperature > 30){

      digitalWrite(led,HIGH);  //LED will turn on if temperature is above 30
      tone(buzzer,100,1000);   // Buzzer will turn on if temperature is above 30
    }

    digitalWrite(led,LOW);    // All other cases, LED will be turned off.
    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
