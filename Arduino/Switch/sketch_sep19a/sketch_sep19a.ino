#define sw[9] = {3,4,5,6,7,8,9,10,11}
#define ledPin 12

void setup(){
  
  for(int i=0;i<8;i++)
  pinMode(sw[i],INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //int arr[3][3]={{3,4,5}, {6,7,8}, {9, 10, 11}};
   int arr[3][3]={{sw1,sw2,sw3}, {sw4,sw5,sw6}, {sw7, sw8, sw9}};

   if(int arr[1][3]==HIGH) {
    
   }
}
