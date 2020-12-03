#include <Phpoc.h>

char server_name[]= args[0];
PhpocClient client;

#define TRIG A1
#define ECHO A0
#define OPT A2
#define ENA 6
#define IN1 29
#define IN2 31
int relay = 5;


int sw[9]={23,24,26,28,30,32,34,36,38}, sws[9];


void setup() {
  Serial.begin(9600);
  while(!Serial);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
  
  for(int i=0;i<9;i++)
  pinMode(sw[i],INPUT_PULLUP);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(OPT, INPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(
  firststart();
  

}

unsigned long duration, sum, result;
unsigned long distance=0;
unsigned long x = 0;
int disum=1;

void loop() {
  
  Serial.println("Loop Start");

  int iEmegency = iEmegency_Check();
  Serial.println("EMG : " + iEmegency);
  if (iEmegency > 0 && iEmegency < 4)
  {
    Serial.println("PUMP ON");
    
  
    result = 0;
    result = uUltraSonic();
    
  
    Serial.print("\nDistance : ");
    Serial.print(result); 
    Serial.println(" cm");

  if(disum != x)
    if (distance != result)
    {
      if(result >= 20 && result < 25){
        Serial.println("disum=0");
        disum=getDisum(0);
      }
      else if(result >= 25 && result < 40)
      {
        Serial.println("disum=1");
        disum= getDisum(1);
      }
      else if(result >= 41 && result < 50)
      {
        Serial.println("disum=2");
        disum=getDisum(2);
      }
      else if(result >= 50)
      {
        Serial.println("disum=3");
        disum=getDisum(3);
      }
  
      distance = result;
      disum=x;
    }
  }
  else
    firststart();
    
  Serial.println(distance + "/" + result);

       if(iEmegency >=4)
        {
            Serial.println("ALERT");
            Serial.println(iEmegency);
  
        if(client.connect(server_name, 80)){
            Serial.println("Connected to server");
            client.print("GET /insert_data.php?num="+(String)iEmegency);
            client.print("1");
            client.println(" HTTP/1.1");
            client.println("Host: 61.81.54.127");
            client.println();
            }
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
  delay(1000);
}


int uUltraSonic()
{
  Serial.println("UltraSonic Start");
  sum = 0;
  int b = 0;
  int count[20];
  int iCnt = 0;

  for(int i = 0; i<20; i++)
  {
    
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    
    duration = pulseIn(ECHO, HIGH); 
    distance = ((float)(340 * duration) / 10000) / 2; 

    if (distance > 10)
    {
      if(distance<100|distance>21)
      { 
          count[i] = distance;
          //Serial.print("\t\tdis:");
          //Serial.println(distance);
          iCnt++;
      }
    }
  } 

  for (int i = 0 ; i < iCnt; i++)
  {
    sum += count[i];    
  }
  b = sum /iCnt;
  
  Serial.print("CNT:" + (String)iCnt);
  Serial.print(" / AVG:");
  Serial.println(b);
  Serial.println("UltraSonic Stop");
  return b;
  
}


int firststart(){  
  while(digitalRead(OPT)==HIGH)
  {
    if(digitalRead(OPT)==LOW){
      break;
    }
    else
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 120);
      delay(50);
    }
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  Serial.println("firststart");
  disum=0;
  x=1;
}



int reset(){
  for(int i=0; i<9; i++)
  {
    if(digitalRead(sw[i])==LOW)
    firststart();
    Serial.println("RESET");
  }
}


int getDisum(int idisum)
{
  switch(idisum)
  {
    case 0:
    Serial.println("LEVEL_1");
    delay(500);
    Serial.println("DOWN");
    digitalWrite(IN1, LOW);          
    digitalWrite(IN2, HIGH);          
    analogWrite(ENA, 155);   
    delay(500);       
    Serial.println("MOVE_DONE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    Serial.println("STOP");
    break;
  case 1:
  
    Serial.println("LEVEL_2");
    delay(500);
    Serial.println("DOWN");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 155);
    delay(900);
    Serial.println("MOVE_DONE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    Serial.println("STOP");
    //reset();
    break;
  case 2:
    Serial.println("LEVEL_3");
    delay(500);
    Serial.println("DOWN");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 155);
    delay(1350);
    Serial.println("MOVE_DONE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    Serial.println("STOP");
    //reset();
   case 3:
     Serial.println("MAX");
      while(digitalRead(OPT)==HIGH)
  {
    if(digitalRead(OPT)==LOW){
      break;
    }
    else
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 80);
      delay(50);
    }
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
    
   default:
    
     break;
  }

  return idisum;
}


int alert()
{
  for(int i=0;i<9;i++){
      if(digitalRead(sw[i])==LOW) 
      sws[i]=0;
      else 
      sws[i]=1;}

      int warning = 0;
      for(int i = 0; i < 9; i++)
      warning += sws[i];

       if(warning >=4)
        {
  
  Serial.println("ALERT");
  Serial.println(warning);
  
  if(client.connect(server_name, 80)){
    Serial.println("Connected to server");
    client.print("GET /insert_data.php?num="+(String)warning);
    client.print("1");
    client.println(" HTTP/1.1");
    client.println("Host: 61.81.54.127");
    client.println();
    
      }
    
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
//  delay(1000);
}

int iEmegency_Check()
{
  int iCnt = 0;
  for(int i=0;i<9;i++){
    if(digitalRead(sw[i])==LOW) 
      sws[i]=0;
    else 
      sws[i]=1;
    
    iCnt += sws[i]; 
    delay(50);   
  }
  return iCnt;
}
