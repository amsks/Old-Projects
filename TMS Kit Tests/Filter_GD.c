/* 
  Description: Adaptive filter algorithm 
*/

#include<stdio.h>
#include<math.h>

// defining the parameters 

#define lrate 0.01                    // Learning Rate
#define N 44                         // Order of the filter 
#define NS 60                        // No. of sample 
#define Fs 8000                      // Sampling Rate 
#define pi 3.1415926                  
#define DESIRED 2*cos(2*pi*T*1000/Fs)
#define Noise   sin(2*pi*T*1000/Fs) 

float desired[NS], output[NS], error[NS] ;

void main ()
{ 
   long I,T ;                        // running variables for order and samples respectively 
   float Y,H,E ;
   float theta[N+1] = {0.0} ;
   float X[N+1] = {0.0} ;

   for ( T=0; T<NS; T++ ) 
   { 
      X[0] = Noise ;
      D = DESIRED ;
      Y=0; 


      for ( I=0; I<=N; I++ ) 
          H = H + theta[I]*X[I] ;               // weighted sum 

      E = Y - H ;
      
      for ( I=N; I>=0; I-- ) 
      {
            theta[I] += 2*E*lrate*X[I] ;
            if ( I!=0 ) X[I] = X[I-1] ;
      }

      desired[T] = Y ;
      output[T] = H ;
      error[T] = E ;
   }
}
