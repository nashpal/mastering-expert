/*
  ==============================================================================

    BiQuad.h
    Created: 6 Oct 2015 4:49:28pm
    Author:  Anthony Nash

  ==============================================================================
*/

#ifndef BIQUAD_H_INCLUDED
#define BIQUAD_H_INCLUDED

#include "Settings.h"

class BiQuad
{
public:
    BiQuad(void) {};
    virtual ~BiQuad(void) {};
    
protected:
    float Xz_1; // x z-1 delay element
    float Xz_2; // x z-2 delay element
    float Yz_1; // y z-1 delay element
    float Yz_2; // y z-2 delay element

    
public:
    
    float a0;
    float a1;
    float a2;
    float b1;
    float b2;

    
    // flush Delays
    void flushDelays()
    {
        Xz_1 = 0;
        Xz_2 = 0;
        Yz_1 = 0;
        Yz_2 = 0;
    }
    
    // Do the filter: given input xn, calculate output yn and return it
    float doBiQuad(float xn)
    {
        // just do the difference equation: y(n) = a0x(n) + a1x(n-1) + a2x(n-2) - b1y(n-1) - b2y(n-2)
        float yn = a0*xn + a1*Xz_1 + a2*Xz_2 - b1*Yz_1 - b2*Yz_2;
        
        // underflow check	
        if(yn > 0.0 && yn < FLT_MIN_PLUS) yn = 0;
        if(yn < 0.0 && yn > FLT_MIN_MINUS) yn = 0;
        
        // shuffle delays
        // Y delays
        Yz_2 = Yz_1;
        Yz_1 = yn;
        
        // X delays
        Xz_2 = Xz_1;
        Xz_1 = xn;
        
        return  yn;
    }
};



#endif  // BIQUAD_H_INCLUDED
