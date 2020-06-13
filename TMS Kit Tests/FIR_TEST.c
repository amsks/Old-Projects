/*
   
     Description : Four FIR filters: LP, HP, BS, BP implemented through .COF files

*/


#include "DSK6713_AIC23.h"
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;
#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_LINE;  
#include "lp500.cof"		 		 //coeff file LP @  500 Hz 
#include "hp2200.cof"				 //coeff file HP @ 2200 Hz 
#include "bp1600.cof"				 //coeff file BP @ 1600 Hz 
#include "bs1250.cof"				 //coeff file BS @ 1250 Hz
short FIR_number = 0; 		      	 //start with 1st LP filter
int yn = 0;					 		 //initialize filter's output
short x[N];            		       //delay samples
short h[4][N];  	    			       //filter characteristics 3xN

interrupt void c_int11()			 //ISR
   {
	short i;
 
	x[0] = input_left_sample();     		 //newest input @ top of buffer
	yn = 0;                          	 //initialize filter output
	
        for (i = 0; i< N; i++)
		yn +=(h[FIR_number][i]*x[i]); //y(n) += h(LP#,i)*x(n-i)
	for (i = N-1; i > 0; i--)         	 //starting @ bottom of buffer
		x[i] = x[i-1];           	 //update delays with data move
 	output_left_sample(yn >> 15);		 //output filter
 	return;					 	//return from interrupt
   }

void main()
{
 	short i;
	\
        for (i=0; i<N; i++)
         { 
		x[i] = 0;                       //initialize buffer
  		h[0][i] = hlp[i];  		//address of lp1500 coeff
   		h[1][i] = hhp[i];  		//address of hp2200 coeff
   		h[2][i] = hbp[i]; 		//address of bp1750 coeff
		h[3][i] = hbs[i];		//address of bs790 coeff
         }
    
         comm_intr();                           //init DSK, codec, McBSP
    
         while(1);    		   		//infinite loop
}
