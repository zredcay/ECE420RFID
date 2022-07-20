#include <LiquidCrystal.h>

#define LCD_RS 13
#define LCD_EN 12
#define LCD_D4 11
#define LCD_D5 10
#define LCD_D6 9
#define LCD_D7 8
#define RFID_EN 7

#define START_BYTE 0x0A
#define STOP_BYTE  0x0D

#define BUFSIZE 10
#define NUM_OF_STUDENTS 12

struct student
{
  String name;
  char id[10]; 
  bool present;
  bool enrolled;
}; 

struct student students[NUM_OF_STUDENTS] = {
    
    {"TEAM LEADER", "0600118D97", false, false},
    {"Zach Redcay", "060012444F", false, false},
    {"Alex Doyle", "0600118D6C", false, false},
    {"BIG T", "06000E5C24", false, true},
    {"E BOSS", "06001227D1", false, true},
    {"Alina Endres", "0600124488", false, true},
    {"Issy Hoffman", "0600123F61", false, true},
    {"BUH'LAKE", "060011A751F", false, true},
    {"Karen", "0600123FB2", false, true},
    {"David Moore", "0600007EB7", false, true},
    {"Tyler McWilliams", "0600007713", false, true},
    {"PAPA GABE", "06000050B2", false, true},
    
  }; 


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
//  data[0] = 0; // Clear buffer

  if (Serial.available())
  {
    if (Serial.read() == START_BYTE)
    {
      char data[BUFSIZE] = {}; 
      charsRead = Serial.readBytesUntil(STOP_BYTE, data, BUFSIZE); 
      digitalWrite(RFID_EN, HIGH); // Put Reader in 'Idle' Mode - stop reading data 
//      Serial.print("Chars Read: ");
//      Serial.println(charsRead);
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
