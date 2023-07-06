#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

#define LM35 A1

int fan = 9;
int relaypin = 8;
int photopin = A0;
float phx = 30.0;

void poweronrelay()
{
  digitalWrite(relaypin,HIGH);
  lcd.print("FAN ON");
  delay(1000);
  lcd.clear();
}

void poweroffrelay()
{
  digitalWrite(relaypin,LOW);
  analogWrite(fan,0);
  lcd.print("FAN OFF");
  delay(1000);
  lcd.clear();
}

void setup()
{ 
  pinMode(fan,OUTPUT);
  pinMode(relaypin,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("DIYfinalProject");
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Team 11");
  delay(1000);
  lcd.clear();
  lcd.print("Lets Get Started");
  delay(1000);
  lcd.clear();
  
  Serial.begin(9600);
  delay(10);
}

void loop()
{
  lcd.setCursor(3,0);
  lcd.print("Recording");
  lcd.setCursor(2,1);
  lcd.print("Temperature..");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,2);
  
  int lmvalue=analogRead(LM35);
  float voltage=lmvalue*(5.0/1023.0);
  float tempc=voltage*100;
  
  lcd.setCursor(0,0);
  lcd.print("Temperature=");
  lcd.setCursor(0,1);
  lcd.print(tempc); 
  lcd.setCursor(14,1);
  lcd.print(" C");
  delay(1000);
  lcd.clear();
  
  Serial.print("temp ");
  Serial.println(tempc);
  delay(10);
  
  if(tempc>=25)
  {
    poweronrelay();
    
    int fansp=map(tempc,0,35,0,255);
    analogWrite(fan,fansp);
    float fanspper=(fansp*100)/255;
    lcd.print("Fan Speed:");
    lcd.print(fanspper);
    lcd.print("%");
    delay(1000);
    lcd.clear();
  }
  else
  {
    poweroffrelay();
  }
  
  int ph=0;
  ph = analogRead(photopin);
  float phpercent = (ph/phx)*100.0;
  
  lcd.setCursor(0,0);
  lcd.print("brightness=");
  lcd.setCursor(2,1);
  lcd.print(phpercent);
  lcd.print("%");
  delay(1500);
  lcd.clear();
  
  Serial.print("bright ");
  Serial.println(ph);
  Serial.println("");
  delay(10);
  
  if(ph<=24)
  {
    lcd.print("Lights ON");
    delay(1000);
    lcd.clear();
    
    if(ph>20 && ph<=24)
    {
      digitalWrite(13,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
    }
    if(ph>13 && ph<=20)
    {
      digitalWrite(13,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
    }
    if(ph>6 && ph<=13)
    {
      digitalWrite(13,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
    }
    if(ph>=0 && ph<=6)
    {
      digitalWrite(13,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
    }
  }
  else
  {
    lcd.print("Lights OFF");
    delay(1000);
    lcd.clear();
    digitalWrite(13,LOW);
    digitalWrite(10,LOW);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
  }
}
