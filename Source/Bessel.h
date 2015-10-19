/*
  ==============================================================================

    Bessel.h
    Created: 19 Oct 2015 5:14:17pm
    Author:  Anthony Nash

  ==============================================================================
*/

#ifndef BESSEL_H_INCLUDED
#define BESSEL_H_INCLUDED


class Bessel
{
public:
    Bessel(void) {};
    virtual ~Bessel(void) {};
    
protected:
    
    // Delays.
    float Xz_1;
    float Xz_2;
    float Xz_3;
    float Xz_4;
    float Yz_1;
    float Yz_2;
    float Yz_3;
    float Yz_4;
    
public:
    
    float gain;
    float b1;
    float b2;
    float b3;
    float b4;
    
    // flush Delays
    void flushDelays()
    {
        Xz_1 = 0;
        Xz_2 = 0;
        Xz_3 = 0;
        Xz_4 = 0;
        Yz_1 = 0;
        Yz_2 = 0;
        Yz_3 = 0;
        Yz_4 = 0;
        
    }
    
    // Do the filter: given input xn, calculate output yn and return it
    float doBessel(float xn)
    {
        xn = xn / gain;  // 1.533856183e+07;
        float yn = (1 * Xz_4) + (4 * Xz_3) + (6 * Xz_2) + (4 * Xz_1) + (1 * xn)
            + (b4 * Yz_4) + (b3 * Yz_3) + (b2 * Yz_2) + (b1 * Yz_1);
       
        // underflow check
        if(yn > 0.0 && yn < FLT_MIN_PLUS) yn = 0;
        if(yn < 0.0 && yn > FLT_MIN_MINUS) yn = 0;
        
        // shuffle delays
        // Y delays
        Yz_4 = Yz_3;
        Yz_3 = Yz_2;
        Yz_2 = Yz_1;
        Yz_1 = yn;
        
        // X delays
        Xz_4 = Xz_3;
        Xz_3 = Xz_2;
        Xz_2 = Xz_1;
        Xz_1 = xn;
        
        return  yn;
    }
};


#endif  // BESSEL_H_INCLUDED
