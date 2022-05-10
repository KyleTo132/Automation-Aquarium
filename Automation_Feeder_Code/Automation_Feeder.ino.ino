#include <Servo.h>
Servo servo;
int angle = 40;
//---- start point is 1 MIN
//---- each rotation is 40+
//---- end point is 160 MAX
//---- which means that with the limited 180 mg90s servo 
//---- we have approximately 5 feeding time

void setup() {
  // put your setup code here, to run once:
  servo.attach(8);
  servo.write(angle);
}

void loop() 
{
//-------------------- 
//--- Experiment 1 ---
//--------------------
//--- code below use to test the degree of the rotation
// // scan from 0 to 180 degrees
//  for(angle = 10; angle < 180; angle++)  
//  {                                  
//    servo.write(angle);               
//    delay(15);                   
//  } 
//  // now scan back from 180 to 0 degrees
//  for(angle = 180; angle > 10; angle--)    
//  {                                
//    servo.write(angle);           
//    delay(15);       
//  } 

//servo.write(160);
//-------------------- 
//--- Experiment 2 ---
//-------------------
//----- code below use to test 5 feeding time
 for(angle = 1; angle < 161; angle = angle +40)  
  {                                  
    servo.write(angle);               
    delay(1500);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 161; angle > 1; angle = angle - 40)    
  {                                
    servo.write(angle);           
    delay(1500);       
  } 

}
