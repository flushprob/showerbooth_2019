#define TRIG A0
#define ECHO A1

void setup(){
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop(){
  unsigned long duration, sum,result;
  float distance;
  result = 0;
  sum = 0;
  int b = 0;

  for(int i = 0; i<10; i++)
  {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
 duration = pulseIn(ECHO, HIGH); 
 distance = ((float)(340 * duration) / 10000) / 2; 

  if(distance>300|distance<21)
  {
    
  }
  else {
  sum=sum+distance;
  b++;
  }

  }
  result = sum/b;
  
  Serial.print("\nDistance : ");
  Serial.print(result); 
  Serial.println(" cm");
  delay(100);
}
