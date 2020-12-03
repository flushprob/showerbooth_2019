#define ENA 6
#define IN1 7
#define IN2 8
int OPT = 9;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(OPT, INPUT);
}

void loop() {

if(digitalRead(OPT) == HIGH)
{
  Serial.println("1");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 150);
}
else{
  Serial.println("0");
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
analogWrite(ENA, 150);
}
delay(100);
}
