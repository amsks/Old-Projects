  /* 
    Description : IIR filter implementation using second order cascading 
 */
// 16-bit integer coefficients read from .cof file 
 

#include "DSK6713_AIC23.h"	        //codec-DSK interface support
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;	//set sampling rate

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC;
#include "bs1800int.cof"

short w[SECTIONS][2] = {0};


interrupt void c_int11()	 //interrupt service routine
{
  short section;                 // index for section number
  short xn ;                     // input to each section
  int wn,yn;                     // intermediate and output values in each stage

  xn= input_left_sample();
  
  for (section=0 ; section< NUM_SECTIONS ; section++)
  {
    wn = xn- ((a[section][0]*w[section][0])>>15) - ((a[section][1]*w[section][1])>>15);
    yn = ((b[section][0]*wn)>>15) + ((b[section][1]*w[section][0])>>15) + ((b[section][2]*w[section][1])>>15);
    w[section][1] = w[section][0];
    w[section][0] = wn;        
    xn = yn;                     // output of current section will be input to next
  }

  output_sample((short)(yn)); // before writing to codec

  return;                       //return from ISR
}

void main()
{
  comm_intr();                  //init DSK, codec, McBSP
  
  while(1);                     //infinite loop
}
