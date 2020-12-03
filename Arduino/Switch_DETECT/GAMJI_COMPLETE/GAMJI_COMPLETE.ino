// int sw[9]={30,32,34,36,38,40,42,44,46}, sws[9]; 
 int sw[9]={23,24,26,28,30,32,34,36,38}, sws[9];

void setup()
{
  Serial.begin(9600);
 
  
 for(int i=0;i<9;i++)
 pinMode(sw[i],INPUT);
 
    
}

void loop()
{
  for(int i=0;i<9;i++)
  {
     if(digitalRead(sw[i])==LOW)
    {
      sws[i]=0;
      delay(20);
      
    }
    else{     
      sws[i]=1;
      delay(20);
    }
 }

/*    
  if(sws[0]+sws[1]+sws[2]+sws[3]+sws[4]+sws[5]+sws[6]+sws[7]+sws[8] >=4)
  {
    Serial.println("ALERT");
  
  }
*/  
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
