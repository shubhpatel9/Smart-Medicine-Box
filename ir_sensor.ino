/*  
 *   When the IR sensor detects an object it opens up the second servo motor
 */
  int ir_sensor() {
          for (pos = 0; pos <= 90; pos+= 1)
              {
                myservo2.write(pos);
                delay(15);
              }    
          for (pos = 90; pos >= 0; pos-= 1)
              {
                myservo2.write(pos);
                delay(15);
              }
              return 1;
  }
