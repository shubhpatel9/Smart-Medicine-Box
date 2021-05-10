/*  
 *   This function is called from the firstBoot to set the number of doses
 *   For the convinience of the project the highest number of doses is set to 4. It can be changed, but we would need bigger EEPROM to store the data 
 */
  void readRotaryEncoder();
  void encoderButton();
  
  void DozeNo() {
    int temp = 1;
    lcd.setCursor(0, 0);
    lcd.print("Dose:");
    while (temp == 1)           //hour is set
    {
      readRotaryEncoder();
      encoderButton();
  
      if (up)
      {
        total++;
        up = false;
        if (total > 10) total = 0;
        if (total < 0) total = 10;
        Serial.println(total);
      }
      else if (down)
      {
        total--;
        down = false;
        if (total > 10) total = 0;
        if (total < 0) total = 10;
        Serial.println(total);
      }
  
      lcd.setCursor(5, 0);
      lcd.print(total);
  
      if (middle == true)   //checks if button is pressed
      {
        Serial.print("middle pressed: ");
        Serial.println(total);
        middle = false;
        temp = 0;
      }
    }
    if (temp == 0)
    {
      lcd.clear();
    }
  }
