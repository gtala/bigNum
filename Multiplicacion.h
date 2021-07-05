#ifndef Multiplicacion_H
#define Multiplicacion_H

#include<iostream>
#include <Bignum.h>

using namespace std;

// declaro la clase base abstracta multiplicacion 
class Bignum;

class MultiplicacionBase{
    
    public: 
    virtual Bignum multiplicacion(const Bignum & c1,const Bignum & c2)=0;
    virtual ~MultiplicacionBase();
   
};

// declaro la clase heredada multiplicacionA

class Multiplicacion_standard :  public MultiplicacionBase{
    
    public: 
    /*
    Bignum   	multiplicacion_cifra(const unsigned short  &)const;
	void		corrimiento_izquierda(int &);
	void 		suma_arreglos(unsigned short *, const size_t &);
    */
    Bignum multiplicacion(const Bignum & c1,const Bignum & c2);
    ~Multiplicacion_standard();
};

// declaro la clase heredada multiplicacionB

class Multiplicacion_karatsuba :  public MultiplicacionBase{
    public: 
    Bignum multiplicacion( const Bignum  & c1,const Bignum & c2);
    ~Multiplicacion_karatsuba();
};


#endif

