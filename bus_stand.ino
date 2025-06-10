#include<Servo.h>



Servo myservo;

 bool bus= true;



void setup() {
  pinMode(5,INPUT);
  myservo.attach(9);
  myservo.write(90);
  Serial.begin(9600);
 
}

void loop() {

 
   bool irsensor=digitalRead(5);

   if(irsensor==0 && bus==true)
   {

      delay(5000);
        for(int i = 90; i>=0 ; i--)
      {
        myservo.write(i);
        delay(5);
      }

      delay(30000);
      myservo.write(90);
      bus =false;

   }
   else
      {
          myservo.write(90);
         
      }


}
  

  




  
  

  

