#include <LiquidCrystal.h>

#define RFID_EN 7
#define BUFSIZE 10

#define LCD_RS 13
#define LCD_EN 12
#define LCD_D4 11
#define LCD_D5 10
#define LCD_D6 9
#define LCD_D7 8


#define START_BYTE 0x0A
#define STOP_BYTE  0x0D



char data[BUFSIZE]; 
int charsRead = 0; 

//// initialize the library by associating any needed LCD interface pin
//// with the arduino pin number it is connected to
//const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void setup() 
{
  lcd.begin(16, 2); 
  lcd.print("Init"); 
  pinMode(RFID_EN, OUTPUT); 
  digitalWrite(RFID_EN, HIGH); // Put Reader in 'Idle' Mode


  Serial.begin(2400); 
  while(!Serial);           // Wait for Serial port to be ready
  Serial.println("RFID Reader"); 
  Serial.println("Setup complete");
  Serial.println();
  Serial.flush(); 

  lcd.setCursor(0,1); 
  lcd.print("Setup done");
  delay(2000);

  
 

}

void loop() 
{
  digitalWrite(RFID_EN, LOW); // Put Reader in 'Active' Mode
  lcd.clear(); 
  data[0] = 0; // Clear buffer

  if (Serial.available())
  {
    if (Serial.read() == START_BYTE)
    {
      charsRead = Serial.readBytesUntil(STOP_BYTE, data, BUFSIZE); 
      digitalWrite(RFID_EN, HIGH); // Put Reader in 'Idle' Mode - stop reading data  
      Serial.print("Chars Read: ");
      Serial.println(charsRead);
      Serial.flush(); 
      Serial.print("ID: "); 
      lcd.print("ID:");
      //lcd.print(data);
      
      for (int i=0; i < BUFSIZE; i++)
      {
        lcd.print(data[i]); 
        Serial.print(data[i]);
      }
      Serial.println();
      Serial.flush();
      delay(5000);
    }
  }


}
