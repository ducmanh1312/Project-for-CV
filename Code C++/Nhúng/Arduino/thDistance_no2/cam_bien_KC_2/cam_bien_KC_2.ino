const int triggerPin = 10; 
const int echoPin = 11;    

void setup() {
  // Khai báo chế độ INPUT/OUTPUT cho chân kết nối
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 10^6);
  

  float distance = duration * 0.017150; // 0.017150 = 34300 / 2 
  
  // In kết quả ra Serial Monitor
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500); 
}
