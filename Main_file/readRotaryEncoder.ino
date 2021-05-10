void readRotaryEncoder() 
{
  //value is updated according to the updates in the encoder position
  value += encoder->getValue();

  if (value / 2 < last)
  {
    last = value / 2;
    down = true;
    delay(150);
  }
  else if (value / 2 > last)
  {
    last = value / 2;
    up = true;
    delay(150);
  }
}
