#include<Phpoc.h>
char server_name[]= "192.168.43.216";
PhpocClient client;
int sw[9]={40,41,42,43,44,45,46,47,48}, sws[9];
#define led 13
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
    pinMode(led, OUTPUT);
   for(int i=0;i<9;i++)
  pinMode(sw[i],INPUT);
}

void loop() {
  digitalWrite(led, LOW);
  
   for(int i=0;i<9;i++){
      if(digitalRead(sw[i])==HIGH) sws[i]=1;
      else sws[i]=0;}

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
  digitalWrite(led, HIGH);
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
