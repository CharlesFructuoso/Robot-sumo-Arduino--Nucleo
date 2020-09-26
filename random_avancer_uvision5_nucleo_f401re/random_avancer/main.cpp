#include "mbed.h"

// Warning LED
DigitalOut myled(LED2);
// Motor driver
// Direction
DigitalOut M1(D4);
DigitalOut M2(D7);
// Speed
PwmOut V1(D3);
PwmOut V2(D6);


void Avancer () // Move forward
{
    M1=1;
    M2=1;
    V1.write(1.0f);
    V2.write(1.0f);    
}
void Reculer () // Move forward
{
    M1=0;
    M2=0; 
    V1.write(1.0f);
    V2.write(1.0f);    
}
void Turn () // Move forward
{
    M1=0;
    M2=1; 
    V1.write(1.0f);
    V2.write(1.0f);    
}
int main() // Setup
{
    wait(5); // Time before starting (rules)
    myled = 1;
	
    while(1) { // Loop
    Avancer(); // Move forward
    }
}