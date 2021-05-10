/*
 * This function is called from the loop function to check if the set time is equal to the real time and it performs some functions based on that
 */
 
  void sendSMS();
  void playFirst();
  int alarmCheck() {
    
    t = rtc.getTime();
  
    for (int i = 1; i <= 2*total; i = i + 2)
      {
        if (t.hour == EEPROM.read(i) && t.min == EEPROM.read(i + 1) && t.sec == 0) //reading from the EEPROM to compare the real time
        {
          for (pos = 0; pos <= 90; pos += 1)
          {
             myservo1.write(pos);
             delay(15);
          }    
          delay (1000);
          for (pos = 90; pos >= 0; pos -= 1)
          {
             myservo1.write(pos);
             delay(15);
          }
          delay(1000);
          playFirst();      //MP3 function is called when the alarm time is equal to real time
          delay (100);
          sendSMS();        // Function to send a text message in the phone 
          return i;
        }
        else 
        {
          return;
        }
      }
  }
