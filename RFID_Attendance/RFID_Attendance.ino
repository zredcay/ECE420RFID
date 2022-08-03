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
#define NUM_OF_STUDENTS 9

// Stuct set up for a student
struct student
{
  String name;
  char id[11]; 
  bool present;
  bool enrolled;
}; 

// Array of students
struct student students[NUM_OF_STUDENTS] = {
    {"BIG T", "06000E5C24", false, true},
    {"E BOSS", "06001227D1", false, true},
    {"Alina Endres", "0600124488", false, true},
    {"Issy Hoffmann", "0600123F61", false, true},
    {"BUH LAKE", "060011A751", false, true},
    {"Karen", "0600123FB2", false, true},
    {"David Moore", "0600007EB7", false, true},
    {"McWilliams", "0600007713", false, true},
    {"PAPA GABE", "06000050B2", false, true}
  }; 

int charsRead = 0;  // Keeps track of how many characters are read by the serial port
String garbage = "";  // Used to manually clear the serial port

//// initialize the library by associating any needed LCD interface pin
//// with the arduino pin number it is connected to
//const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void setup() 
{
  lcd.begin(16, 2); 
  lcd.print("Init"); 
  pinMode(RFID_EN, OUTPUT); 
  digitalWrite(RFID_EN, HIGH);              // Put Reader in 'Idle' Mode


  Serial.begin(2400); 
  while(!Serial);                           // Wait for Serial port to be ready
  Serial.println("RFID Reader"); 
  Serial.println("Setup complete");
  Serial.println(); 

  // Set up LCD for Operation
  lcd.setCursor(0,1); 
  lcd.print("Setup done");
  delay(2000);
}

void loop() 
{
  digitalWrite(RFID_EN, LOW); // Put Reader in 'Active' Mode
  lcd.clear(); 

  // While there is serial data to read
  if (Serial.available())
  {
    // Once the start byte is found
    if (Serial.read() == START_BYTE)
    {
      char data[BUFSIZE];   // Hold the data that is being read from the serial port
      charsRead = Serial.readBytesUntil(STOP_BYTE, data, BUFSIZE);  // Read data from the serial port until the stop byte is found 
      digitalWrite(RFID_EN, HIGH); // Put Reader in 'Idle' Mode - stop reading data 

      bool access = false;  // Access flag for each student
      int i = 0;            // Counter to keep track of which student has scanned

      // Check to see which student has swiped their card
      for(i = 0; i <= 8; i++)
      {
        for(int j = 0; j < BUFSIZE; j++)    // Compare swiped ID to current student, check to see if they match
        {
          if (students[i].id[j] == data[j])
          {
            // If ID's match, continue comparing
            access = true;
          }else
          {
            // If ID's do not match, break
            access = false;
            break;
          }
        }
        // If the student has been found, break
        if (access == true)
        {
          break;
        }
      }

      // This section is used to display the student name and current status
      if (access == true)
      {
        if (!students[i].enrolled)
        {
          
        }else
        {
          // Toggle the students present to either 'present' or 'has left'
          students[i].present = !students[i].present;
        }
        // Print the students name for 1 sec
        lcd.print(students[i].name);
        lcd.setCursor(0,1); 
        // Print the students status for 2 sec
        if (students[i].present)
        {
          lcd.print("IS PRESENT");
        }else
        {
          lcd.print("HAS LEFT");
        }
        // Print information to the serial port
        Serial.println(students[i].name);
        Serial.println(students[i].present);
      }else{
          // If the student is not enrolled, deny access
          lcd.setCursor(0,0); 
          lcd.print("ACCESS DENIED");
      }
  
      // Serial port printing for troubleshooting
      if (access == true)
      {
        Serial.println("ACCESS GRANTED");
      }else
      {
        Serial.println("ACCESS DENIED");
      }     

      Serial.println();
      delay(2000);
      lcd.clear();
    }

    // Used to clear the rest of the serial port data from the serial buffer
    // Serial.flush() does not actually clear the buffer, it merely waits for the buffer to read completely
    // Because of this, the serial buffer must be cleared manually
    while(Serial.available())
    {
      garbage = Serial.read();
      //Serial.print(garbage);
    }
  }
  
}
