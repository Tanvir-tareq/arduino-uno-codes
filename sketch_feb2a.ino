#include<Keypad.h>

 const byte rows=4;
 const byte colm=4;
 char keys [rows][colm]=
 {
  {'1','3','2','A'},
   {'4','6','5','B'},
    {'7','9','8','C'},
     {'*','#','0','D'}
 };

 byte rowpin [4]={10,9,8,7};
 byte colmpin [4]={A0,A1,A2,A3};

 Keypad mykey= Keypad(makeKeymap(keys),rowpin,colmpin,4,4);

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  char key=mykey.getKey();
  if (key)
  {
    Serial.print("PRESSED KEY  :   ");
    Serial.println(key);
  }

}
