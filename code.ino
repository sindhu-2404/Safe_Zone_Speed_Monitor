#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //SCL SDA

#define trig 2
#define echo 3
long distance,duration;
int value=0;
int speed;
#define motor 5

#define led 4

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}
void loop()
{
  distance_loop();
  if(distance >= 100)
  {
    digitalWrite(led,LOW);
    value=255;
  }
  else if(distance >= 20 && distance < 100)
  {
    digitalWrite(led,LOW);
    value=map(distance,20,100,100,255);
  }
  else if(distance < 20)
  {
    digitalWrite(led,HIGH);
    value=0;
  }

  speed=map(value,100,255,0,100);
  Serial.print("SPEED : ");Serial.println(speed);
  analogWrite(motor,value);

  lcd.clear();
  lcd.print("DIST: ");lcd.print(distance);
  lcd.setCursor(0,1);
  lcd.print("SPEED: ");lcd.print(speed);
  delay(500);
}
void distance_loop()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;

  Serial.print("Distance : ");Serial.println(distance);  
}
