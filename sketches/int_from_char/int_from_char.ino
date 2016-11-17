char message[6] = "14253";
char mes[2] = {message[2],message[3]};
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int nuo = atoi(mes)+5;
Serial.println(nuo);
}
