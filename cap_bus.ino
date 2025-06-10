#include <Wire.h>
#include <U8g2lib.h>
#include<Servo.h>
#include<avr/wdt.h>

const int relaypin = 5;
const int buzzer = 4;
int pos1 = 0;
int pos2 = 20;
bool increment = true;


const int INPUT_PIN_1 = 2;
const int INPUT_PIN_2 = 3;
const int SERVO_PIN = 9;
bool timebuzz = true;
unsigned long startime;
unsigned long duration = 2000;

Servo myServo;




// Initialize SH1106 OLED (I2C Mode)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void draw1()
 {
   u8g2.drawStr(60, pos1, "ON");
 }

 
void draw2()
{
  
  u8g2.drawStr(30, pos2, "BATTERY");
}

void setup() {
   
    u8g2.begin();
    pinMode(A2,INPUT);
    pinMode(relaypin,OUTPUT);
    pinMode(INPUT_PIN_1, INPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(INPUT_PIN_2, INPUT);
    myServo.attach(SERVO_PIN, 500, 2500);  // Use this for stable signals
    myServo.write(93);
    wdt_enable(WDTO_1S);
    startime = millis();


}


void loop() {
    
    float value = analogRead(A2)*2;
    float voltage = ((value*5.00)/1023.00) - 0.21;


    float soc = (voltage/5.00)*100;

    wdt_reset();
    

    bool LEFT = digitalRead(INPUT_PIN_1);
    bool RIGHT = digitalRead(INPUT_PIN_2);
    

   


    //SERVO

    if (LEFT && !RIGHT) 
    {
        myServo.write(120);
        delay(50);// Move servo to 120°
    } 
    
    else if (!LEFT && RIGHT)
    {
        myServo.write(60);
        delay(50);  // Move servo to 60°
    } 

    else if (LEFT && RIGHT)
    {
        myServo.write(90);
        delay(50);  // Move servo to 60°
    } 

    else {
        myServo.write(90);
        delay(50);  // No valid input, keep at 90°
    }

   
    //Display module & relay connection

    

   

    if(soc>=50.00)
    {

    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x13_tf);
    u8g2.drawStr(10, 10, "Capacitor Charge:");
    u8g2.setFont(u8g2_font_lubBI12_tf);
    char buffer[10];  
    dtostrf(soc, 4, 2, buffer); // Convert float to string with 2 decimal places
    strcat(buffer, " %");
    u8g2.drawStr(30, 30, buffer);


   
    float time = (50*(voltage-2.50))/0.200;
    float time_in_mins = time/60;


    u8g2.setFont(u8g2_font_7x13_tf);
    u8g2.drawStr(10, 45, "Time Remaining:");
    u8g2.setFont(u8g2_font_lubBI12_tf);
    char buffer1[10];  
    dtostrf(time_in_mins, 4, 2, buffer1); // Convert float to string with 2 decimal places
    strcat(buffer1, " mins");
    u8g2.drawStr(20, 62, buffer1);
 
    u8g2.sendBuffer();
    delay(100);
    
 

    

    }

    

    
   

    else
    {   
        
        u8g2.firstPage();
        u8g2.setFont(u8g2_font_t0_22b_mf);
        
        do
        {
         draw2();
         draw1();
        }
        while(u8g2.nextPage());

       

        if(increment)
        {
           pos1++;
           pos2++;
           if(pos1>=40 && pos2>=50)
           {
             increment = false;
           }
        
        }
        else
        {
           pos1--;
           pos2--;
           if(pos1<= 30 && pos2<= 40)
           {
             increment = true;
           }

        }

        u8g2.sendBuffer();

    
        
        delay(100);
        
        
    }

    if(soc>=50.00)
    {
      digitalWrite(relaypin,LOW);
      delay(500);
    }

    else
    {
      digitalWrite(relaypin,HIGH);
      delay(500);

      if(millis() - startime<=duration)
      {
        digitalWrite(buzzer,HIGH);
      }

      else
      {
        digitalWrite(buzzer,LOW);
      }
    }

    

    
    
    }

  



 








 




