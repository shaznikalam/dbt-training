
int mq3sens = 8;
int buzz = 2;

void setup() {
  Serial.begin(9600);
  pinMode(mq3sens, INPUT);
  pinMode(buzz, OUTPUT);

}

void loop() {
  int mq3sensstt = digitalRead(mq3sens);
  Serial.println(mq3sensstt);
  if (mq3sensstt == HIGH) {
    digitalWrite(buzz, HIGH);
  } else {
    digitalWrite(buzz, LOW);
  }
  delay(1); 
}
