#include <Servo.h> 
Servo myservo;
 
int pos = 0;    
boolean fire = false;
 
#define Left D0      // left sensor
#define Forward D1   //front sensor
#define Right D2    // right sensor


#define In1 D6       // left motor forward
#define In2 D5       // left motor back
#define In3 D4       // right motor forward
#define In4 D3       // right motor back

#define pump D7
#define servo D8
 
void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(servo);
  myservo.write(90); 
}
 
void fire_off()
{
    delay (300);
    //stop car start pump
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    
   digitalWrite(pump, HIGH);
   delay(500);
    
    for (pos = 30; pos <= 150; pos++) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 150; pos >= 30; pos--) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pump,LOW);
  myservo.write(90);
  
  fire=false;
}
 
void loop()
{
   myservo.write(90);  
 
    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    // stop 
    digitalWrite(In1, LOW); 
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
      //move forward
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH); 
    digitalWrite(In4, LOW); 
    fire = true;
    }
    
    else if (digitalRead(Left) ==0)
    {
      //turn left
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW); 
    digitalWrite(In4, LOW);
    }
    
    else if (digitalRead(Right) ==0) 
    {
      //turn right
    digitalWrite(In1, LOW); 
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    } 
    
    delay(200); //change this value to increase the distance
 
     while (fire == true)
     {
      fire_off();
     }
}
