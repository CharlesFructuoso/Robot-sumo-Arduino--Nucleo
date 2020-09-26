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
// Random initialization 
AnalogIn randomseed(A2);
// Random timer
Timer t;
// Interruption timer
Timer ti;
// Line sensors variable
int Cont_Ar_g = 0;
int Cont_Ar_d = 0;
int Cont_Av_g = 0;
int Cont_Av_d = 0;

void Random () // Random direction generator
{
    M1=rand()%2;
    M2=rand()%2;
}
void Vitesse() // Speed generator
{ 
    V1.write(1.0f);
    V2.write(1.0f);    
}

void Reculer_int () // Move backward (interrupt case)
{
    while(ti.read()< 2 && Cont_Ar_g == 0 && Cont_Ar_d == 0)
    {
		Cont_Ar_g= Ar_g.read();
		Cont_Ar_d= Ar_d.read();
    M1=0;
    M2=0;
    V1.write(1.0f);
    V2.write(1.0f);
    }
    ti.stop();
    ti.reset();
}
void Avancer_int () // Move forward (interrupt case)
{
    while(ti.read()< 2 && Cont_Av_g == 0 && Cont_Av_d == 0)
    {
		Cont_Av_g= Av_g.read();
		Cont_Av_d= Av_d.read();
    M1=1;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);
    }
    ti.stop();
    ti.reset();
}

void pressedAv_gi() // Interrupt front left line sensor
{
    ti.start();  
    Reculer_int();

}

void pressedAv_di () // Interrupt front right line sensor
{
    ti.start();  
    Reculer_int();
 
}
void pressedAr_gi () // Interrupt back left line sensor
{
    ti.start();  
    Avancer_int();
 
}
void pressedAr_di () // Interrupt back right line sensor
{
    ti.start();  
    Avancer_int();
 
}

int main() // Setup
{
		// Random initialization
    int rnds=randomseed.read()*1000;
    srand(rnds);
	
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
		// Call random direction generator
    Random();
		// Start time random
    t.start();
	
    while(1) { // Loop
		// Read line sensors	
    Cont_Av_g= Av_g.read();
    Cont_Av_d= Av_d.read();
		Cont_Ar_g= Ar_g.read();
    Cont_Ar_d= Ar_d.read();

if (Cont_Av_g == 1 || Cont_Av_d == 1) // Front line sensors security
  {
    ti.start();
    Reculer_int();
    }
	else if (Cont_Ar_g == 1 || Cont_Ar_d == 1) // Back line sensors security
  {
    ti.start();
    Avancer_int();
  }
else // Random cycle V2 strategy
{
    if (t.read()<2){ // Cycle of 2 sec
    Vitesse(); // Call speed generator
        }
    else // Reset cycle timer, generate a new random and a new cycle
    {
        t.stop();
        t.reset();
        Random();
        t.start();
    }    
    }
  }
            
}