int count =0;

void setup() {
  Serial.begin(9600);
  Serial.println("setup OK");

}

void loop() {
  count = count + 1;
  Serial.print("count= ");
  Serial.println(count);
  delay(500);

}
