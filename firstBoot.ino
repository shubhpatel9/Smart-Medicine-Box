/*
 * The purpose of this function is to set the Number of Doses that the User wants to enter, then set the time for each of those doses.
 */
  void medTime();
  void DozeNo();
  
  void firstBoot()
  { 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome New User");
    delay(3000);
    lcd.clear();
    delay(300);
    
    DozeNo();     // this function is for setting the number of doses

    // after the dose number is selected, we have to set time for each dose. Therefore a loop is used to set the time and write the data in the SD card 
  
    for (int i = 0; i < total; i++)
    {
      lcd.setCursor(0,0);
      lcd.print("Set time");
      lcd.setCursor(0,1);
      lcd.print("Doze ");
      lcd.print(i+1);
      medTime(i);    // this function is called to set the time for each dose
    }
  }
