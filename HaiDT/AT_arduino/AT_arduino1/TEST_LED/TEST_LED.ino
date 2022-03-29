void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_PB4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_PB4, 1); delay(100);
  digitalWrite(PIN_PB4, 0); delay(100);
}
