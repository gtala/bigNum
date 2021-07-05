#ifndef BIGNUM_H
#define BIGNUM_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <Multiplicacion.h>

using namespace std;



class Bignum
{

private:

	unsigned short  *digits_; 
	size_t  longitud_ocupada_ ;
	bool signo_;
	bool multiplicacion_ ; // flag utilizado para saber que tipo de multiplicacion, podria ser un enum 

	bool 		modulo_mayor_a(const Bignum &) const;
	bool 		modulo_igual_a(const Bignum &) const;
	

public:
	Bignum( );
	Bignum(const size_t &); 
	Bignum(const Bignum &);
	~Bignum( ); 
	bool 		get_signo( ) const;
	void 		set_signo(bool) ;
	bool		get_tipo_multiplicacion() const ;
	void		set_tipo_multiplicacion(bool);
	unsigned short* get_digitos(); 
	unsigned short  get_digito(size_t) const; 
	void		set_digito(size_t,unsigned short);
	size_t 		size( ) const; 
	Bignum		operator=( const Bignum & ); 
	friend Bignum  operator+(const Bignum&, const Bignum&);
	friend Bignum  operator-(const Bignum&, const Bignum&);

	Bignum   	multiplicacion_cifra(const unsigned short  &)const;
	void		corrimiento_izquierda(int &);
	void 		suma_arreglos(unsigned short *, const size_t &);

	Bignum primeros(size_t)const;
	Bignum ultimos(size_t)const;
	Bignum potencia_10(size_t)const;
	friend Bignum  operator*(const Bignum&, const Bignum&);

	friend std::ostream& operator<<(std::ostream&, const Bignum&);
	friend std::istream& operator>>(std::istream&,Bignum&);
	

};


#endif

