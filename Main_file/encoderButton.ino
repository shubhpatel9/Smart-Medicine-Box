void encoderButton() //this is actually to set the time
{
    ClickEncoder::Button b = encoder->getButton();
     if (b != ClickEncoder::Open) 
     {
     switch (b) 
     {
        case ClickEncoder::Clicked:
           middle = !middle;
          break;
     }
     }
}
