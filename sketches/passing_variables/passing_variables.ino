extern const char ssid[];

void setup()
{
  Serial.begin(9600);
}

void loop()
{
Serial.println(ssid);
}
