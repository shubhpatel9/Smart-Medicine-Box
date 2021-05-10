/*
 * This is the first function when the program starts. It gets the real date and time from the RTC module and display it on the LCD.
 */
  void displayTime() {
      
      t = rtc.getTime();
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(t.mon, DEC);
      
      lcd.setCursor(1,0);
      lcd.print("/");
      lcd.setCursor(2,0);
      lcd.print(t.date, DEC);
  
      lcd.setCursor(4,0);
      lcd.print("/");
      lcd.setCursor(5,0);
      lcd.print(t.year, DEC);
  
      lcd.setCursor(11,0);
      lcd.print(t.hour, DEC);
      lcd.setCursor(13,0);
      lcd.print(":");
      lcd.setCursor(14,0);
      lcd.print(t.min, DEC);
      
      lcd.setCursor(0,1);
      lcd.print(rtc.getDOWStr());
  }
