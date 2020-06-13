/*
   Description: generation of echo with fixed delay 
*/ 

#include "DSK6713_AIC23.h"	                // codec support
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;	         // set sampling rate

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC;     // select input

#define GAIN 0.6                // output feed back
#define SIZE 2000           // length of delay

short buffer[SIZE];         // storage for previous samples
short x,y,delay;
int i;                          

interrupt void c_int11()	    // interrupt service routine
{
  x = input_left_sample();  // read new input sample from ADC 
  
  delay = buffer[i];          // read delayed value from buffer
  
  y = input + delay;     // output sum of input and delayed values
  output_left_sample(y);
       
  
  buffer[i] = x + delay*GAIN; // store new input and a fraction 
                                // of the delayed value in buffer
  if (++i >= SIZE) 
               i=0;      // test for end of buffer
  
  return;                       
}

void main()
{
  comm_intr();                  // init DSK, codec, McBSP
  
  for(i=0 ; i<SIZE ; i++)   // clear buffer
    buffer[i] = 0;
  
  while(1);                     //infinite loop
}

