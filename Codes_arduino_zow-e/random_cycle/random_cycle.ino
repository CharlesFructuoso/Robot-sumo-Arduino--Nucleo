#define IR1 8
#define IR2 9
#define Li_av1 10
#define Li_av2 11

#define E1 5    //M1 Speed Control
#define E2 6    //M2 Speed Control
#define M1 4    //M1 Direction Control
#define M2 7    //M2 Direction Control

#define Sonar 3
#define randomseed A2

int IRstate1 = 0;
int IRstate2 = 0;
int IRstate_Li_av1 = 0;
int IRstate_Li_av2 = 0;

//Sonar variable
long sensor = 0;
long pulse = 0;
long dist = 0;

int test=0;
unsigned long previousMillis = 0;
const long rand_interval = 2000;

void stop(void)                    //Stop
{
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);    
}   
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}  
void back_off_int (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
  delay(2000);
}
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void setup() {
  for(int i=4;i<=7;i++)
  pinMode(i, OUTPUT);  
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(Li_av1, INPUT);
  pinMode(Li_av2, INPUT);
  randomSeed(analogRead(randomseed));
  test=random(4);
  delay(5000);
}
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= rand_interval) 
  {
    previousMillis = currentMillis;
    test=random(4);
  }
  
  //sonar distance
  pulse = pulseIn(Sonar, HIGH);
  sensor = pulse / 147;
  dist = sensor * 2,54;
  
  IRstate1=digitalRead(IR1);
  IRstate2=digitalRead(IR2);
  IRstate_Li_av1=digitalRead(Li_av1);
  IRstate_Li_av2=digitalRead(Li_av2);

  if(IRstate_Li_av1 == 1 || IRstate_Li_av2 == 1)
  {
    back_off_int(100,100);
  }
  else
  {
    switch(test)
    {
      case 0:
      advance(100,100);
      break;
      case 1:
      back_off(100,100);
      break;
      case 2:
      turn_R(100,100);
      break;
      case 3:
      turn_L(100,100);
      break;
    }
  } 
}
