#include <Servo.h>

int s1 = A0;  // right servo at pin A0
int s2 = A1;  //left servo at pin A1
int s3 = A2; // base servo at pin A2
int s4 = A3; // hand servo at pin A3
int s5 = A4;  // hand servo
int buzzer = 12;
int greenled = 10;   // led pins
int redled = 8;

//right servo min max position
int r_min = 40;
int r_max = 130;

//left Servo min and Max position
int l_min = 100;
int l_max = 10;

// min max angle for base servo
int b_min = 10;
int b_max = 160;
int h_min = 45;    // min position for hand servo
int h_max = 130;  // max posotion for hand servo

//variables for sccop positions
int b_scoop = 85;
int r_scoop = 80;
int l_scoop = 50;
int h_scoop = 90;

//variables for feed positions
int b_feed = 180;
int r_feed = 70;
int l_feed = 130;
int h_feed = 180;

Servo sr_R;  // create servo object to control a servo
Servo sr_L;
Servo sr_B;
Servo sr_H;
Servo sr5;

void setup()
{

  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);

  //connection of servos
  sr_R.attach(s1);
  sr_L.attach(s2);
  sr_B.attach(s3);
  sr_H.attach(s4);

  sr_R.write(r_min);   //setting initial position to minimun
  sr_L.write(l_min);
  sr_B.write(b_max);
  sr_H.write(h_feed); //this is horizontal position of spoon
  delay(200);

  Serial.print("Servo's Intialising : ");
  Serial.println(" ....   ");
  delay(200);
  Serial.println("Please Wait ");
  Serial.println(" ");

  delay(1000);

  Serial.println("Setting the Home Position for all The Servo's " );
  delay(1000);
  Serial.print("Home position for left servo is : " );
  Serial.println(l_min);
  Serial.print("Home position for Right Servo is : ");
  Serial.println(r_min);
  Serial.println(" ");


  Serial.print("Starting Main function ");
  for (int i = 0; i <= 4; i++)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(redled, HIGH);
    Serial.print("*");
    delay(600);// for moving right servo
    digitalWrite(buzzer, LOW);
    digitalWrite(redled, LOW);
    delay(600);
  }

  //base servo will move from home position to scoop position
  for (int i = 20; i <= b_scoop; i = i + 2)
  {
    //delay(30);
    sr_B.write(i);
    Serial.print("Base Servo: ");
    Serial.println(i);
    delay(30);
  }


  //moving left servo to scoop position
  for (int i = l_min; i >= l_scoop; i = i - 1)
  {
    sr_L.write(i);
    Serial.print("Left Servo: ");
    Serial.println(i);
    delay(50);
  }
  //moving rigth servo to scoop position
  for (int i = r_min; i <= r_scoop; i = i + 1)
  {
    sr_R.write(i);
    Serial.print("Right Servo: ");
    Serial.println(i);
    delay(50);
  }
  Serial.println(" ");
  Serial.print("       -------------------------Lets Fire it Up----------------------------");
}

void loop()
{
  feed();

}

void feed()
{
  digitalWrite(greenled,HIGH);
  scoop();
  digitalWrite(greenled,LOW);
  //scooping with the spoon

  /*sr_H.write(h_scoop);
    delay(50);
    Serial.print("Hand Scoop: ");
    Serial.println(h_scoop);

    //for scooping loop
    for (int i = h_scoop; i <= h_feed; i = i + 1)
    {
    sr_H.write(i);
    Serial.print("Hand Servo: ");
    Serial.println(i);
    delay(30);
    }*/

  //moving left servo to feed position
  for (int i = l_scoop; i <= l_feed; i = i + 1)
  {
    sr_L.write(i);
    Serial.print("Left Servo: ");
    Serial.println(i);
    delay(30);
  }

  //moving right servo to feed position
  for (int i = r_scoop; i >= r_feed; i = i - 1)
  {
    sr_R.write(i);
    Serial.print("Right Servo: ");
    Serial.println(i);
    delay(30);
  }
  //moving base servo to feed position
  for (int i = 110; i <= b_feed; i = i + 1)
  {
    sr_B.write(i);
    Serial.print("Base Servo: ");
    Serial.println(i);
    delay(30);
  }

  for (int i = 0; i <= 3; i++)
  {

    digitalWrite(redled, HIGH);
    delay(800);
    digitalWrite(redled, LOW);
    delay(800);
  }
  for (int i = b_feed; i >= 80; i = i - 2)
  {
    sr_B.write(i);
    Serial.print("Base Servo: ");
    Serial.println(i);
    delay(30);
  }

  //moving right and left servo to scoop pos from feed position
  for (int i = r_feed; i <= r_scoop; i = i + 1)
  {
    sr_R.write(i);
    delay(30);
  }
  for (int i = l_feed; i >= l_scoop; i = i - 1)
  {
    sr_L.write(i);
    delay(30);
  }
}

void scoop()
{
  for (int i = 0; i <= 180; i = i + 2)
  {
    //for baseservo
    float y = ((12. / 180.) * (i*1.3) ) + 80;
    sr_B.write(y);
    Serial.print(" Base : ");
    Serial.println(y);
    delay(1);
    float x = ((100. / 180.) * (i * 1.5)) + 80 ;
    sr_H.write(x);
    Serial.print(" scoop : ");
    Serial.println(x);
    delay(1);

  }
}
