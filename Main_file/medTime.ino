/* 
 *  This function if called from the firstBoot after the dose number is set. 
 *  This function will run based on the dose number to set the Hour and Minute for each dose
 *  The data is saved in the EEPROM
 */
  void readRotaryEncoder();
  void encoderButton();
  
  void medTime(int j) {
  
    t = rtc.getTime();    // Get data from the DS3231
  
    int temp = 1;
    setHour = 0;
    setMin = 0;
    while (temp == 1)           //hour is set
    {
      readRotaryEncoder();
      encoderButton();
      if(up)                  //checks if the encoder is rotated in upwards direction
      {
        setHour++;
        up = false;
        if (setHour > 23) setHour = 0;
        if (setHour < 0) setHour = 23;
      }
      else if(down)           //checks if the encoder is rotated in downwards direction            
      {
        setHour--;
        down = false;
        if (setHour < 0) setHour = 23;
        if (setHour > 23) setHour = 0;
      }
      lcd.setCursor(7,1);
      lcd.print(setHour);
      lcd.setCursor(9,1);
      lcd.print(":");
      lcd.print(setMin);
      if(middle == true)    //checks if button is pressed
      { 
        EEPROM.write(hourAddr, setHour); //time is set for the doze
        hourAddr += 2;
        Serial.print("Set Time for Doze");
        Serial.print(j+1);
        Serial.print("->  ");
        Serial.print(setHour);
        temp = 2;
        middle = false;
      }
    }
    while (temp == 2)           //minutes are set
    {
      readRotaryEncoder();
      encoderButton();
      if(up)
      {
        setMin++;
        up = false;
        if (setMin > 59) setMin = 0;
        if (setMin < 0) setMin = 59;
      }
      else if(down)
      {
        setMin--;
        down = false;
        if (setMin < 0) setMin = 59;
        if (setMin > 59) setMin = 0;
      }
      if (setHour >= 0 or setHour <= 9)
      {
        lcd.setCursor(10,1);
        lcd.print(setMin);   
  
            if(middle == true)
            {
              EEPROM.write(minAddr, setMin);
              minAddr += 2;
              Serial.print(":");
              Serial.print(setMin);
              Serial.println(" ");
              temp = 0;
              middle = false;
            }
      }
      else if (setHour > 9 or setHour <= 23)
      {
        lcd.setCursor(11,1);
        lcd.print(setMin);   
  
            if(middle == true)
            {
              EEPROM.write(minAddr, setMin);
              minAddr += 2;
              Serial.print(":");
              Serial.print(setMin);
              Serial.println(" ");
              temp = 0;
              middle = false;
            }
      }
    }
    while (temp == 0)
    {
              file = SD.open ("file.txt", FILE_WRITE);
            if (file) 
            {
                String dataString = "Set Time for Doze" + String (j+1) + "->  " + String(setHour) + ":" + String(setMin) + "." ;
                file.print(dataString);
                file.close();
       
            }
    }
  }
