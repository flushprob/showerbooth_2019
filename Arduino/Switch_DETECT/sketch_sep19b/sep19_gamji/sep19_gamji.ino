int sw[9]={3,4,5,6,7,8,9,10,11}, sws[9];
#define led 13
void setup() {
  Serial.begin(9600);
    pinMode(led, OUTPUT);
   for(int i=0;i<9;i++)
  pinMode(sw[i],INPUT_PULLUP);
}

void loop() {
   for(int i=0;i<9;i++){
      if(digitalRead(sw[i])==LOW) sws[i]=1;
      else sws[i]=0;}
    
    if(sws[0]+sws[1]+sws[2]+sws[3]+sws[4]+sws[5]+sws[6]+sws[7]+sws[8] >=4)
{
  
  Serial.println("ALERT");
  
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  
}
for(int i = 0; i < 9; i++)
{
  Serial.print(sws[i]);
  Serial.print(" ");
  if(i % 3 == 2)
  {
    Serial.println();
  }
}
Serial.println();
Serial.println("-----");
delay(200);
}
