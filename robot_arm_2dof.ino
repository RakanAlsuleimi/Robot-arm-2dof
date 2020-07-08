#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;
LiquidCrystal lcd(5, 4, 3, 2, A4, A5);
double theta1,theta2,x,y,costheta2;
int L1 = 25;
int L2 = 10;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7,6}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.setCursor(1, 0);
   servo1.attach(12);  // attaches the servo on pin 12 to the servo object
   servo2.attach(13);  // attaches the servo on pin 13 to the servo object
   }
int integer();
void forward();
void loop(){ 
int c = kinematic(); // user choose the type of kinematic
  
  if (c==1){ // forward 
   lcd.clear();
   lcd.print("Enter angle 1"); 
   lcd.setCursor (0, 1);
   lcd.print("Enter any letter to end");
   theta1 = integer(); // convert the number from char to integer
   lcd.clear();
   delay(500);         
   lcd.clear();
   lcd.print("Enter angle 2"); 
   lcd.setCursor (0, 1);
   lcd.print("Enter any letter to end");
   theta2 = integer();
   lcd.clear();
   lcd.print("angle 1 = ");
   lcd.print(theta1);
   lcd.setCursor (0, 1);
   lcd.print("angle 2 = ");
   lcd.print(theta2);
   delay(2000);
   forward(); // call forward function
  }
             
  else if (c==2){ // inverse
   lcd.clear();
   lcd.print("Enter X cord."); 
   lcd.setCursor (0, 1);
   lcd.print("Enter any letter to end");
   x = integer();
   lcd.clear();
   delay (500);         
   lcd.clear();
   lcd.print("Enter Y cord."); 
   lcd.setCursor (0, 1);
   lcd.print("Enter any letter to end");
   y = integer(); 
   lcd.clear();
   lcd.print("X = ");
   lcd.print(x);
   lcd.setCursor (0, 1);
   lcd.print("Y = ");
   lcd.print(y);
   delay (2000);
   inverse(); // call inverse function
  }
}


// start of function
int kinematic(){ 
  char key=0;
  lcd.clear();
  lcd.print("Enter A for forward");
  lcd.setCursor (0, 1);
  lcd.print("Enter B for inverse");

  while(key==0){key = keypad.getKey();}
  if (key=='A'){
    lcd.clear();
    lcd.print("forward");
    delay(2000);
   return 1;
  }
  else if(key=='B'){
    lcd.clear();
    lcd.print("inverse");
    delay(2000);
   return 2;
  }
}// end the function


int integer() // convert the input from keypad to integer
{
  int value = 0;                                // the number accumulator
  int keyval;                                     // the key press
  int isnum;
  do
  {
    keyval = keypad.getKey();                          // input the key
    isnum = (keyval >= '0' && keyval <= '9');         // is it a digit?
    if (isnum)
    {
      
      value = value * 10 + keyval - '0';               // accumulate the input number
    }

  } while (isnum || !keyval);                          // until not a digit or while no key pressed
  Serial.println(" "); Serial.print("Returning "); Serial.println(value);
  return value;

}//end of function

void forward() // start of function
{
  lcd.clear();
  servo1.write(theta1);
  servo2.write(theta2);
  theta1=theta1*PI/180;
  theta2=theta2*PI/180;
  x=(L1*cos(theta1))+(L2*cos(theta1+theta2));
  y=(L1*sin(theta1))+(L2*sin(theta1+theta2));
  lcd.print("X = ");
  lcd.print(x);
  lcd.setCursor (0, 1);
  lcd.print("Y = ");
  lcd.print(y);
  delay (5000);
} // end of function

void inverse()
{ 
  lcd.clear();
  
  theta2=acos((pow(x,2)+pow(y,2)-pow(L1,2)-pow(L2,2))/(2*L1*L2));
  theta1=atan(y/x)-atan((L2*sin(theta2))/(L1+L2*cos(theta2)));
  theta1=theta1*180/PI;
  theta2=theta2*180/PI;
  servo1.write(theta1);
  servo2.write(theta2);
  lcd.print("theta1 = ");
  lcd.print(theta1);
  lcd.setCursor (0, 1);
  lcd.print("theta2 = ");
  lcd.print(theta2);
  delay (5000);
}
             
