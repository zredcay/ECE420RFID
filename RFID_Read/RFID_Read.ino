#define ENABLE_PIN 7
#define BUFSIZE 10

#define START_BYTE 0x0A
#define STOP_BYTE  0x0D



char data[BUFSIZE]; 
int offset; 

void setup() 
{
  pinMode(ENABLE_PIN, OUTPUT); 
  digitalWrite(ENABLE_PIN, HIGH); // Put Reader in 'Idle' Mode
  delay(3000);
  digitalWrite(ENABLE_PIN, LOW); // Put Reader in 'Active' Mode


  Serial.begin(2400); 
  while(!Serial);           // Wait for Serial port to be ready
  Serial.println("RFID Reader"); 
  Serial.println("Setup complete");
  Serial.println();
  Serial.flush(); 
 

}

void loop() 
{
  
  data[0] = 0; // Clear buffer
  offset = 0;  // Reset offset

  if (Serial.available())
  {
    if (Serial.read() == START_BYTE)
    {
      Serial.print("ID: "); 
      Serial.readBytesUntil(STOP_BYTE, data, BUFSIZE); 
      Serial.println(data);
      Serial.flush(); 
    }
  }


  
//  while(Serial.available())
//  {
//    data[offset] = Serial.read(); 
//    if (data[offset] == START_BYTE)
//    {
//      Serial.print("ID: ");
//      // No need to print start byte
//      offset = -1; // Move offset back so that indices 0-9 are ID
//       
//    }
//    else if (data[offset] == STOP_BYTE)
//    {
//      data[offset] = 0; // Put null terminator at end of buffer
//      break; 
//    }
//
//    offset++;
//    
//    if (offset >= BUFSIZE)
//    {
//      offset = 0; 
//    }
//    
//  }
//
//  Serial.println(data); 
//  Serial.flush(); 

}
