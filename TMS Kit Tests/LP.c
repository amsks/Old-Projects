/*
   Creator : Aditya Mohan 
   Description : 

   This code is the simplest Fir Filter implementation,which uses
   interrupts to implement a Low Pass filter 

*/ 

#include "DSK6713_AIC23.h"	              // codec support
#include "Test_LP.cof"
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;	      //set sampling rate

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC; // select input

short x[N];          // input delay array 
int yn = 0;

interrupt void c_int11()
{
   short i ;            // parse variable 

   x[0] = input_left_sample() ;
   yn = 0;

   for ( i=0; i<N; i++ ) 
          yn += h[i]*x[i] ;

   for ( i=(N-1); i>0; i++ ) 
          x[i] = x[i-1] ;
   
   output_sample(yn >> 15) ;
}

void main ()
{
   comm_intr();
   while(1);
}
