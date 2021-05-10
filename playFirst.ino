void setVolume(int volume);
void execute_CMD(byte CMD, byte Par1, byte Par2);
void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(15);
  delay(500);
  execute_CMD(0x11,0,1); 
  delay(500);
}
