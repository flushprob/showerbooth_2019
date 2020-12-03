#include<Phpoc.h>
char server_name[]= "192.168.43.216";
PhpocClient client;

int sw[9]={22,24,26,28,30,32,34,36,38}, sws[9];
#define TRIG A0
#define ECHO A1
#define ENA 10
#define IN1 12
#define IN2 13
const byte OPT = 6;
int disum = 64;

void setup(){
  Serial.begin(9600);
  while(!Serial);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
   for(int i=0;i<9;i++)
  pinMode(sw[i],INPUT_PULLUP);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(OPT, INPUT);
  reset();
}
void loop(){
  unsigned long duration, sum,result;
  float distance;
  result = 0;
  sum = 0;
  int b = 0;
  

  for(int i = 0; i<20; i++)
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

  if(disum<result)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 75);
    disum=disum+1;
    Serial.println(disum);
  }
  else if(disum > result)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 75);
    disum = disum - 1;
    Serial.println(disum);
  }
  else if(disum == result)
  {
    analogWrite(ENA, 0);
  }
  delay(50);
  
   for(int i=0;i<9;i++){
      if(digitalRead(sw[i])==LOW) sws[i]=0;
      else sws[i]=1;}

      int warning = 0;
      for(int i = 0; i < 9; i++)
        warning += sws[i];
    
    if(warning >=4)
{
  
  Serial.println("ALERT");
  Serial.println(warning);
  if(client.connect(server_name, 80)){
    Serial.println("Connected to server");
    client.print("GET /insert_data.php?num=" + (String)warning);
    client.println(" HTTP/1.1");
    client.println();}
    else
    Serial.println("Connection Failed");
    delay(100);
}
if(client.available()){
   client.read();
  }
  client.stop();

for(int i = 0; i < 9; i++)
{
  Serial.print(sws[i]);
  Serial.print(" ");
  if(i % 3 == 2)
  {
    Serial.println();
  }
}
Serial.println("-----");

delay(200);
}


void reset(){  
  while(digitalRead(OPT)==HIGH)
  {
    if(digitalRead(OPT)==LOW){
      break;
    }
    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 75);
      delay(50);
    }
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
