#include "mbed.h"

// Warning LED
DigitalOut myled(LED2);
// IR sensors (Opposing robot detection)
DigitalIn Ir1(D8);
DigitalIn Ir2(D9);
// Line sensors (Interrupt and digital security)
InterruptIn Av_gi(D11);
DigitalIn Av_g(D11);
InterruptIn Av_di(D10);
DigitalIn Av_d(D10);
InterruptIn Ar_gi(D12);
DigitalIn Ar_g(D12);
InterruptIn Ar_di(D13);
DigitalIn Ar_d(D13);

// Motor driver
// Direction
DigitalOut M1(D4);
DigitalOut M2(D7);
// Speed
PwmOut V1(D3);
PwmOut V2(D6);
// Ultrasonic sensor (Opposing robot detection)
AnalogIn sonar1(A1);
// Interruption timer
Timer t;
// Line sensors variable
int Cont_Ar_g = 0;
int Cont_Ar_d = 0;
int Cont_Av_g = 0;
int Cont_Av_d = 0;

int distance(AnalogIn sonar1) // Ultrasonic sensor distance calculation
{  
   float r= sonar1.read();
   double distance = ((r*1000)/512)*(2.54*100);
   if (distance < 15){
    return 0;
    }
    else{
    return distance;
    }
}
void Avancer () // Move forward
{
    M1=1;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);    
}
void Reculer_int () // Move backward (interrupt case)
{
    while(t.read()< 2 && Cont_Ar_g == 0 && Cont_Ar_d == 0)
    {
		Cont_Ar_g= Ar_g.read();
		Cont_Ar_d= Ar_d.read();
    M1=0;
    M2=0;
    V1.write(1.0f);
    V2.write(1.0f);
    }
     t.stop();
     t.reset();
}
void Avancer_int () // Move forward (interrupt case)
{
    while(t.read()< 2 && Cont_Av_g == 0 && Cont_Av_d == 0)
    {
		Cont_Av_g= Av_g.read();
		Cont_Av_d= Av_d.read();
    M1=1;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);
    }
     t.stop();
     t.reset();
}
void AV_Droite () // Turn right
{
    M1=1;
    M2=0;
    V1.write(1.0f);
    V2.write(1.0f); 
}
void AV_Gauche () // Turn left
{
    M1=0;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);
}

void pressedAv_gi() // Interrupt front left line sensor
{
    t.start();  
    Reculer_int();

}

void pressedAv_di () // Interrupt front right line sensor
{
    t.start();  
    Reculer_int();
 
}
void pressedAr_gi() // Interrupt back left line sensor
{
    t.start();  
    Avancer_int();

}
void pressedAr_di () // Interrupt back right line sensor
{
    t.start();  
    Avancer_int();
 
}

int main() // Setup
{
	
    wait(5); // Time before starting (rules)
		Av_g.mode(PullDown);
		Av_d.mode(PullDown);
		Ar_d.mode(PullDown);
		Ar_g.mode(PullDown);	
    myled = 1;
		// Line sensors interrupt on rising edge
    Av_gi.rise(&pressedAv_gi);
    Av_di.rise(&pressedAv_di);
	  Ar_gi.rise(&pressedAr_gi);
    Ar_di.rise(&pressedAr_di);
    while(1) { // Loop
		// Read IR sensors 	
    int Infr1= Ir1.read();
    int Infr2= Ir2.read();
		// Read line sensors
    Cont_Av_g= Av_g.read();
    Cont_Av_d= Av_d.read();
		Cont_Ar_g= Ar_g.read();
    Cont_Ar_d= Ar_d.read();
		// Read ultrasonic sensor
    int d=distance(A1);

  if (Cont_Av_g == 1 || Cont_Av_d == 1) // Front line sensors security
  {
    t.start();
    Reculer_int();
  }
	else if (Cont_Ar_g == 1 || Cont_Ar_d == 1) // Back line sensors security
  {
    t.start();
    Avancer_int();
  }
    else // Search and attack strategy
    {
    if (d>25){ // Opposing robot not found
    AV_Gauche(); // Turn on itself
        }   
    else if (d>15 && d<25){ // Opposing robot found by ultrasonic sensor 
    Avancer(); // Move forward on it
        }
    else if (d<15){ 
         if (Infr1 == 0 && Infr2 == 0){ // Opposing robot found by IR sensors 
            Avancer(); // Move forward on it
                }
        } 
        }   
    }
}