void execute_CMD(byte CMD, byte Par1, byte Par2);
void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}
