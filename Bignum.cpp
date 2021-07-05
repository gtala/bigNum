#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h> 
#include "Bignum.h"
#include "Multiplicacion.h"

using namespace std;

Bignum::Bignum()
{
	// contructor por defecto
	digits_=NULL;
	longitud_ocupada_=0;
	signo_=false;
	multiplicacion_ = false; ; // flag utilizado para saber que tipo de multiplicacion, podria ser un enum 
}

 
Bignum::Bignum( const size_t &longitud)
{
	// cout<<"contructor por copia con arreglo"<<endl;
	unsigned short *aux;
	
	aux = new unsigned short [longitud];
	for(size_t i=0;i<longitud;i++){aux[i]=0;}

	digits_=aux;
	longitud_ocupada_=longitud;
	signo_=false;
	multiplicacion_ = false;
}

Bignum::Bignum( const Bignum &b) 
{
	
	//cout<<"contructor por copia"<<endl;

	unsigned short *aux;
	
	aux = new unsigned short [b.longitud_ocupada_];
	
	for(size_t i=0;i<b.longitud_ocupada_;i++){
		aux[i]=b.digits_[i];
	}								
	
	digits_=aux;
	longitud_ocupada_=b.longitud_ocupada_;
	signo_=b.signo_;
	multiplicacion_ = b.get_tipo_multiplicacion();
	
}

 
Bignum::~Bignum()
{
	// cout<<"destructor"<<endl;
	if (digits_)
		delete[] digits_;
}

size_t Bignum::size() const { 

	return longitud_ocupada_;
}
 
bool Bignum::get_signo() const {return signo_;}

void Bignum::set_signo(bool sig){ signo_=sig;}

bool Bignum::get_tipo_multiplicacion() const {return multiplicacion_;}

void Bignum::set_tipo_multiplicacion(bool mul){ multiplicacion_=mul;}

unsigned short* Bignum::get_digitos(){return digits_;}

unsigned short Bignum::get_digito(size_t p)const{return digits_[p];} 

void	Bignum::set_digito(size_t p,unsigned short item){ digits_[p]=item;}

Bignum Bignum::operator=( const Bignum &rhs )
{
	
	//cout<<"oprerador asignacion"<<endl;

	if ( &rhs == this ) {
		return *this;
	}

	longitud_ocupada_ = rhs.longitud_ocupada_;

	for ( size_t i = 0; i < rhs.longitud_ocupada_; i++ )
		digits_[ i ] = rhs.digits_[ i ]; 
	
	signo_=rhs.get_signo();
	multiplicacion_=rhs.multiplicacion_;
	
	return *this;
}


bool Bignum::modulo_igual_a( const Bignum &rhs ) const
{

	if ( longitud_ocupada_ != rhs.longitud_ocupada_ )
		return false; 
	else{
		for ( size_t i = 0; i < longitud_ocupada_; i++ ){
			if ( digits_[ i ] != rhs.digits_[ i ] )
       				return false; 
		}
	}
       	return true; 
}


bool Bignum::modulo_mayor_a( const Bignum &rhs ) const
{
	// regresa true si |a| > |b|

	if ( longitud_ocupada_ > rhs.longitud_ocupada_ )
		return true; 
	else if(longitud_ocupada_ == rhs.longitud_ocupada_){

		for ( size_t i = 0; i < longitud_ocupada_; i++ ){
			if ( digits_[ i ] > rhs.digits_[ i ] )
				return true; 
			else if(digits_[ i ] < rhs.digits_[ i ])
				return false;
		}
		return false;
	}
	else{
		return false;
	}
}


Bignum  operator+(const Bignum& a, const Bignum& b){ // c = a+b , c=a.oprator+(b)
	
	Bignum c(a.longitud_ocupada_+1);

	int acumulador=0,suma=0;
	int resta=0;
	
	if(a.signo_ && b.signo_){//  -a+-b a y b negativos -> -(a+b)
		c.set_signo(true);
	}
	
	else if(a.signo_ && !b.signo_){ // -a+b  a negativo y b positivo -> b-a
		
		if( b.modulo_mayor_a(a)){ // |b| > |a| 

			
			for(size_t i=0,j = 1;i<b.longitud_ocupada_;i++,j++){
			
				resta=b.digits_[i]-a.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
				
			}
			c.set_signo(false);
		}
		else if( b.modulo_igual_a(a) ){ // |a| = |b| 
			//cout<<"entra en la resta de -a+b "<<endl;
			c.digits_[c.longitud_ocupada_-1]=0;
		}

		else{ // |a| > |b| 

		
			for(size_t i=0,j = 1;i < a.longitud_ocupada_;i++,j++){
			
				resta=a.digits_[i]-b.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
				
			}
		
			c.set_signo(true);

		}
		
		return c;
		
	}
	
	else if(!a.signo_ && b.signo_){ // a+-b a positivo y b negativo -> a-b
		
		if( b.modulo_mayor_a(a)){ // |b| > |a| 

			for(size_t i=0,j = 1;i<b.longitud_ocupada_;i++,j++){
			
				resta=b.digits_[i]-a.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
				
			}
			c.set_signo(true);
			
		}
		else if( b.modulo_igual_a(a) ){ // |a| = |b| 
			c.digits_[c.longitud_ocupada_-1]=0;
		}

		else{ // |a| > |b| 

			for(size_t i=0,j = 1;i < a.longitud_ocupada_;i++,j++){
			
				resta=a.digits_[i]-b.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
				
			}

			c.set_signo(false);

		}
		
		return c;
	}
	
	// si a y b positivo  o si a y b son negativos	
	
	int j = c.longitud_ocupada_-1;

	for(int i=(b.longitud_ocupada_-1);i>=0;i--,j--){
	
		
		suma=b.digits_[i]+a.digits_[i]+acumulador;
		

		if(suma > 9){
			
			suma=suma-10;
			acumulador=1;
		}
		else{
			
			acumulador=0;
		}
		
		c.digits_[j]=suma;
		
		
	}
	if(acumulador ==1){
		c.digits_[j]=acumulador;
	}
	else{
		c.digits_[j]=0;
	}


	return c;
}



Bignum  operator-(const Bignum& a, const Bignum& b){  // c=a-b c=a.operator-(b)

	Bignum c(a.longitud_ocupada_+1);
	
	int resta=0;
	int acumulador=0,suma=0;
	
	
	if(a.signo_ && b.signo_){//  -a--b  a y b negativos -> (b-a)
		//cout<<"entra al -a--b "<< endl;
		
		if( b.modulo_mayor_a(a)){ // |b| > |a| 


			for(size_t i=0,j = 1;i<b.longitud_ocupada_;i++,j++){
			
				resta=b.digits_[i]-a.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;

			}

			c.set_signo(false);

		}
		else if( b.modulo_igual_a(a) ){ // |a| = |b| 
			c.digits_[c.longitud_ocupada_-1]=0;
		}
		else{ // |a| > |b| 

			for(size_t i=0,j = 1;i < a.longitud_ocupada_;i++,j++){
			
				resta=a.digits_[i]-b.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;

			}
			
			c.set_signo(true);

		}
		
		return c;
	}
	
	else if(a.signo_ && !b.signo_){ // -a-b  a negativo y b positivo -> -(a+b)
		
		// cout<<"entra al -a-b"<< endl;
		int j = c.longitud_ocupada_-1;

		for(int i=(b.longitud_ocupada_-1);i>=0;i--,j--){
		
			suma=b.digits_[i]+a.digits_[i]+acumulador;
			
			if(suma > 9){
				
				suma=suma-10;
				acumulador=1;
			}
			else{
				
				acumulador=0;
			}
			
			c.digits_[j]=suma;
			
			
		}
		if(acumulador ==1){
			c.digits_[j]=acumulador;
		}
		else{
			c.digits_[j]=0;
		}

		c.signo_=true;

		return  c;
	}
	
	else if( !a.signo_  && b.signo_){ // a--b  a positivo y b negativo  -> a+b

		//cout<<"entra al a--b "<< endl;
		int j = c.longitud_ocupada_-1;

		for(int i=(b.longitud_ocupada_-1);i>=0;i--,j--){
		
			suma=b.digits_[i]+a.digits_[i]+acumulador;

			if(suma > 9){
				suma=suma-10;
				acumulador=1;
			}
			else{
				
				acumulador=0;
			}
			
			c.digits_[j]=suma;
			
			
		}
		if(acumulador ==1){
			c.digits_[j]=acumulador;
		}
		else{
			c.digits_[j]=0;
		}

		c.set_signo(false);

		return  c;
	}
	
	else{ // a-b  a y b positivos
		// cout<<"a-b"<<endl;
		if( b.modulo_mayor_a(a)){ // |b| > |a| 

			//cout<<"|b| > |a| "<<endl;
			for(size_t i=0,j = 1;i<b.longitud_ocupada_;i++,j++){
			
				resta=b.digits_[i]-a.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
				
			}
			c.set_signo(true);
		}
		else if( b.modulo_igual_a(a) ){ // |a| = |b| 
			c.digits_[c.longitud_ocupada_-1]=0;
		}
		else{ // |a| > |b| 

			for(size_t i=0,j = 1;i < a.longitud_ocupada_;i++,j++){
			
				resta=a.digits_[i]-b.digits_[i];

				if(resta < 0){
					size_t k=j-1;
					while(c.digits_[k]== 0){k--;}
					c.digits_[k] = c.digits_[k]-1;
					k++;
					while(k!=j){
						c.digits_[k] = 10+c.digits_[k]-1;
						k++;
					}
					
					resta=resta+10;
				}
				
				c.digits_[j]=resta;
			
			}
				
			c.set_signo(false);

		}
		
		return c;
	}	
	
	
}



Bignum Bignum::multiplicacion_cifra(const unsigned short  &k )const{

	Bignum c(longitud_ocupada_*2);
	size_t carry=0,aux=0,j=c.longitud_ocupada_-1;
	
	for(int i=longitud_ocupada_-1;i>=0;i--,j--){

		//cout<<"multiplicacion:"<<i<<endl;
		
		aux= k*digits_[i]+carry;
		if(aux > 9){
			carry=aux/10;
			aux= aux%10;
			c.digits_[j]=aux;
		}
		else{
			c.digits_[j]=aux;
			carry=0;
		}
		
	}

	if(carry!=0)
		c.digits_[j]=carry;

	

	return c;
}

void Bignum::corrimiento_izquierda(int & ci){

	for(size_t j=ci;j < longitud_ocupada_;j++){
		digits_[j-ci]=digits_[j];
	}
	for(size_t j=longitud_ocupada_- ci;j<longitud_ocupada_;j++){
			
		digits_[j]=0;
			
	}
	
}

void Bignum::suma_arreglos(unsigned short *b,const size_t &l){

	int acumulador = 0, suma=0;
	

	for(int i=l-1;i>=0;i--){
	
		suma= this->digits_[i]+b[i]+acumulador;

		if(suma > 9){
			suma=suma-10;
			acumulador=1;
		}
		else{
			acumulador=0;
		}
		
		this->digits_[i]=suma;
		
	}

}

Bignum Bignum::primeros(size_t cantidad_digitos)const{

	Bignum a0(cantidad_digitos);

	for (size_t i = 0; i < cantidad_digitos; i++)
	{
		a0.set_digito(i,this->get_digito(i));
		//cout<<a.get_digito(i)<<endl;
		//cout<<this->get_digito(i)<<endl;
	}
	
	return a0;
}

Bignum Bignum::ultimos(size_t cantidad_digitos)const{

	Bignum a0(4);

	
	for (size_t i = this->size()-cantidad_digitos; i < this->size(); i++)
	{
		a0.set_digito(i,this->get_digito(i));
		//cout<<i << " "<<a.get_digito(i)<<endl;
		//cout<<this->get_digito(i)<<endl;
	}
	
	
	return a0;

}

Bignum Bignum::potencia_10(size_t potencia)const{

	Bignum a0(potencia+this->size());
	
	for(size_t j=0;j < this->size();j++){
		a0.set_digito(j,this->get_digito(j));
	}

	return a0;

}


Bignum  operator*(const Bignum& a, const Bignum& b){
        
        MultiplicacionBase* ptr;
		Bignum c(2*a.longitud_ocupada_);

        cout << "operator*" << endl;

        if(a.multiplicacion_){

            ptr =new Multiplicacion_standard;

        }
        else{

            ptr =new Multiplicacion_karatsuba;

        }

		c = ptr->multiplicacion(a,b);

		delete ptr;

        return  c;
}



std::ostream & operator<< (std::ostream& os,const Bignum & a)
{
	//cout<<"operador de salida:"<<endl;

	size_t i=0;
    
	if( a.longitud_ocupada_ == 0 ){
		os << " ";
		return os;
	}
	else{
	
		if(a.signo_){
			os << "-";
		}
		for(; a.digits_[i] == 0 && i<a.longitud_ocupada_-1; ++i){}  
		for(; i< a.longitud_ocupada_; ++i){  
			os << a.digits_[i] ;
		}
		
	}

	return os;
}


std::istream & operator>> (std::istream& is,Bignum& a)
{
	//cout<<"operador de entrada:"<<endl;

	char ch = 0;
	size_t i=0,precision=a.longitud_ocupada_;
	unsigned short aux[5];
	bool entrada=false;
	
	
	for(size_t i=0;i<a.longitud_ocupada_;i++){
		aux[i]=0;
		a.digits_[i]=0;
	}
		
	if( (is.get(ch))&& (isdigit(ch) || isspace(ch)|| ch=='-'|| ch=='+')) {
		
		while(isspace(ch) &&(is.get(ch)));

		if(ch	==	'-'){
			a.signo_=true; // es negativo
			entrada=true;
			
		}
		else if(ch	==	'+'){
			a.signo_=false; // es positivo
			entrada=true;
			
		}
		else if(isdigit(ch)){
			aux[i++] = ch -'0';
			a.signo_=false;
			entrada=true;
		}
		else{
			entrada=false;
		}

		while( entrada && (is.get(ch)) && ch!='\n' && ch!= EOF && isdigit(ch) && i<precision+1){
			if(i< precision){
			aux[i++] =ch -'0';
			entrada=true;
			}
			else{
				i++;
				entrada=false;
			}
			
		}
		
		if(entrada){
			size_t inicio =a.longitud_ocupada_- i;
			for(size_t j=inicio;j<a.longitud_ocupada_;j++)
				a.digits_[j]=aux[j-inicio];
			entrada=true;
		}
		else{
			while(ch!='\n' && is.get(ch));
		}
		
	}


	if((ch == '+' || ch == '-' || ch =='*' || ch == '\n' || ch == EOF || isdigit(ch) || isspace(ch)) && entrada ==true ){
		if(ch != '\n'&& !isdigit(ch) && !isspace(ch) && ch != EOF ){
			is.putback(ch);
		}
			
		return is;
	}
	else{
		is.clear(ios::badbit);
		return is;
	}
}

