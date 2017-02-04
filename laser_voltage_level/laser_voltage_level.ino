void setup() {

  //reading analog on 0 and 1, assumed to be 3.3v
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  //writing analog on 9 and 10, assumed to be 5v
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

int level(int val) {
  return max(min(val / 4, 255) - 1, 0);
}

void loop() {
  //read up to 1024, though this will max at 676 so scale it up
  int val_0 = analogRead(0) * 5 / 3.3;
  int val_1 = analogRead(1) * 5 / 3.3;
  analogWrite(9, level(val_0));
  analogWrite(10, level(val_1));
  digitalWrite(LED_BUILTIN, level(val_0));
}
