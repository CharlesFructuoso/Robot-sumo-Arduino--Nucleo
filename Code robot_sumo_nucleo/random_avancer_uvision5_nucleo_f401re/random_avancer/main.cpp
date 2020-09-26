#include "mbed.h"

// Warning LED
DigitalOut myled(LED2);
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

// Interruption timers
Timer t1;
Timer t2;
// Line sensors variable
int Cont_Ar_g = 0;
int Cont_Ar_d = 0;
int Cont_Av_g = 0;
int Cont_Av_d = 0;

void Avancer () // Move forward
{
    M1=1;
    M2=1; 
    V1.write(1.0f);
    V2.write(1.0f);    
}
void Reculer_int () // Move backward (interrupt case)
{
    while(t1.read()< 2 && Cont_Ar_g == 0 && Cont_Ar_d == 0)
    {
		Cont_Ar_g= Ar_g.read();
		Cont_Ar_d= Ar_d.read();
    M1=0;
    M2=0;
    V1.write(1.0f);
    V2.write(1.0f);
    }
    t1.stop();
    t1.reset();
    t2.start();
}
void Avancer_int () // Move forward (interrupt case)
{
    while(t1.read()< 2 && Cont_Av_g == 0 && Cont_Av_d == 0)
    {
		Cont_Av_g= Av_g.read();
		Cont_Av_d= Av_d.read();
    M1=1;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);
    }
     t1.stop();
     t1.reset();
		 t2.start();
}
void AV_Droite () // Turn right (interrupt case)
{
    while(t2.read()<2 && Cont_Av_g == 0 && Cont_Av_d == 0 && Cont_Ar_g == 0 && Cont_Ar_d == 0)
    {
		Cont_Ar_g= Ar_g.read();
		Cont_Ar_d= Ar_d.read();
		Cont_Av_g= Av_g.read();
		Cont_Av_d= Av_d.read();
    M1=1;
    M2=0;
    V1.write(1.0f);
    V2.write(1.0f);
    }
    t2.stop();
    t2.reset();
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
    t1.start();  
    Reculer_int();
		AV_Droite();

}

void pressedAv_di () // Interrupt front right line sensor
{
    t1.start();  
    Reculer_int();
		AV_Droite();
 
}
void pressedAr_gi () // Interrupt back left line sensor
{
    t1.start();  
    Avancer_int();
		AV_Droite();
 
}
void pressedAr_di () // Interrupt back right line sensor
{
    t1.start();  
    Avancer_int();
		AV_Droite();
 
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
		// Read line sensors
    Cont_Av_g= Av_g.read();
    Cont_Av_d= Av_d.read();
		Cont_Ar_g= Ar_g.read();
    Cont_Ar_d= Ar_d.read();

  if (Cont_Av_g == 1 || Cont_Av_d == 1) // Front line sensors security
  {
    t1.start();
    Reculer_int();
    AV_Droite();
    }
	 else if (Cont_Ar_g == 1 || Cont_Ar_d == 1) // Back line sensors security
  {
    t1.start();
    Avancer_int();
    AV_Droite();
    }
    else // Random move forward strategy
    {
    Avancer(); // Move forward
        }
    }
}