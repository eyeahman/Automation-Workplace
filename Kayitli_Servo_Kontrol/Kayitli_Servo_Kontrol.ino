#include <Servo.h>
#include <EEPROM.h> //Kayitlarin tutulacagi hafiza kutuphanesi.
Servo ServoMotor;
int resolution = 1000; //Cozunurluk, kaydedilecek veri noktasi sayisi; EEPROM.length()'ten az olmali.
int recordTime = 5; //Delay suresi.
bool recording = false;
int LedPin = 13, ButtonPin = 2, ServoPin = 3, Potansiyometre = 0;

void setup() 
{
  pinMode(LedPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  digitalWrite(ButtonPin, HIGH);
  ServoMotor.attach(ServoPin);
}

void loop() 
{
  if (recording == true) 
  {
    for (int i = 1; i <= resolution; i++) 
    {
      digitalWrite(LedPin, HIGH);
      int Veri = map(analogRead(Potansiyometre), 0, 1023, 0, 180); //Potansiyometrenin 0-1023 araligi, 180 derecelik servo motor calismasi icin 0-180 araligina olceklendiriliyor.
      EEPROM.write(i, Veri);
      ServoMotor.write(Veri);
      delay(recordTime);
    }
    digitalWrite(LedPin, LOW);
    delay(1000);
    recording = false;
  }
  else 
  {
    for (int i = 1; i <= resolution; i++) 
    {
      if (digitalRead(ButtonPin) == 0) 
      {
        recording = true;
        break;
      }
      int OkunanVeri = EEPROM.read(i);
      ServoMotor.write(OkunanVeri);
      delay(recordTime);
    }
    digitalWrite(LedPin, HIGH); //show a new repeat
    delay(100);
    digitalWrite(LedPin, LOW);
  }
}