/* 
   Description : LMS Filter that adapts to cancel noise 
*/

#include "DSK6713_AIC23.h"
Uint32 fs = DSK6713_AIC23_FREQ_8KHZ ;

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource = DSK6713_AIC23_INPUT_MIC ; 

#define beta 1E-12                    // Learning Rate 
#define N 30                          // no of wts 
#define LEFT 0
#define RIGHT 1 

float w[N] ;
float x[N] ;
short output;

volatile union ( unsigned int uint; short channel[2]; ) AIC23_data ;

interrupt void c_int11()
{ 
  short i ;
  float yn = 0.0, E=0, dplusn = 0.0, noise = 0.0, desired = 0.0;

  AIC23_data.uint = input_sample();
  desired = (AIC23_data.channel[LEFT]) ;
  noise   = (AIC23_data.channel[LEFT]) ;

  dplusn = desired + noise  ;
  x[0] = noise ;

  for ( i=0; i<N; i++ ) 
     yn += w[i]*x[i] ;
 
  E = (desired + noise) - ybn ;
  
  for ( i=(N-1); i>0; i-- ) 
   { 
     w[i] += beta*E*x[i] ;
	 x[i] = x[i-1] ;
   }
    
  output_sample ( (short) yn ) ;
 
  return ;
}

void main () 
{ 
  short t = 0;

  for (t=0; t<N; t++ ) 
  {
     w[t] = 0 ;
	 x[t] = 0 ;
  }

  comm_intr() ;
  while (1) ;
}

