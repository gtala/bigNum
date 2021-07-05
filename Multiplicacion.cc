#include <iostream>
#include <Multiplicacion.h> 
#include <Bignum.h>

using namespace std;


MultiplicacionBase::~MultiplicacionBase(){};

// Implemento la clase heredada multiplicacion

/*
Bignum Multiplicacion_standard::multiplicacion_cifra(const unsigned short  &k )const{

	Bignum c(this->size()*2);
	size_t carry=0,aux=0,j=c.size()-1;
	
	for(int i=size()-1;i>=0;i--,j--){

		//cout<<"multiplicacion:"<<i<<endl;    
		
		aux= k*get_digito(i)+carry;
		if(aux > 9){
			carry=aux/10;
			aux= aux%10;
			c.get_digito(j)=aux;
		}
		else{
			c.get_digito(j)=aux;
			carry=0;
		}
		
	}

	if(carry!=0)
		c.get_digito(j)=carry;

	

	return c;
}

void Multiplicacion_standard::corrimiento_izquierda(int & ci){

	for(size_t j=ci;j < size();j++){
		get_digito(j-ci)=get_digito(j);
	}
	for(size_t j=size()- ci;j<size();j++){
			
		get_digito(j)=0;
			
	}
	
}

void Multiplicacion_standard::suma_arreglos(unsigned short *b,const size_t &l){

	int acumulador = 0, suma=0;
	

	for(int i=l-1;i>=0;i--){
	
		suma= this->get_digito(i)+b[i]+acumulador;

		if(suma > 9){
			suma=suma-10;
			acumulador=1;
		}
		else{
			acumulador=0;
		}
		
		this->get_digito(i)=suma;
		
	}

}
*/



Bignum Multiplicacion_standard::multiplicacion(const Bignum & a,const Bignum & b){
	
	cout << "Multiplicacion_standard sentence." << endl;
	
	Bignum c(a.size()*2),aux(a.size()*2);
	
	
	if(b.size()!=0)
		c = a.multiplicacion_cifra(b.get_digito(b.size()-1));

	for(int i= b.size()-2,k=1;i>=0;i--,k++){
		

		if(b.get_digito(i) != 0){
			aux= a.multiplicacion_cifra(b.get_digito(i));
			
			aux.corrimiento_izquierda(k);
			
			c.suma_arreglos(aux.get_digitos(),c.size());
			
		}	
		
	}

	if(a.get_signo() == b.get_signo()){//  -a*-b a y b negativos -> (a*b)  y tambien a*b a y b positivos -> (a*b)
		c.set_signo(false);
	}
	else{ //  -a*b a negativo y b postivo -> -(a*b)  y tambien a*-b a positivo y b negativo -> -(a*b)
		c.set_signo(true);
	}
	
	return c;
};

Multiplicacion_standard::~Multiplicacion_standard(){};

// Implemento la clase heredada multiplicacion karatsuba


Bignum Multiplicacion_karatsuba::multiplicacion(const Bignum & a,const Bignum & b){
	//cout << "Multiplicacion_karatsuba sentence." << endl;

	size_t  n = a.size(),k=0;

	cout<<"a :"<< a <<endl;
	cout<<"b :"<< b <<endl;

	if(n <= 1){
		//return a.get_digito(a.size()-1) * b.get_digito(b.size()-1);
		
		Bignum c(a.size());

		a.set_tipo_multiplicacion(true);
		b.set_tipo_multiplicacion(true);


		c=a*b;


		cout<<"a final :"<< a <<endl;
		cout<<"b final :"<< b <<endl;
		cout<<"a final llll :"<< a.get_digito(a.size()-1)  <<endl;
		cout<<"b final llll :"<< b.get_digito(a.size()-1) <<endl;


		return c;//a.get_digito(a.size()-1) * b.get_digito(a.size()-1);
	}
	
	k = (n / 2) + (n % 2);

	Bignum a0(k),b0(k),a1(k),b1(k),c(2*a.size());

 	a0 = a.primeros(k); 
	a1 = a.ultimos(k); 
	b0 = b.primeros(k); 
	b1 = b.ultimos(k); 

	/*
	cout << a0 << endl;
	cout << b0 << endl;
	cout << a1 << endl;
	cout << b1 << endl;
	*/
	
	Bignum p = multiplicacion(a0,b0); // 1234 * 2345  -> 12*23 

	cout<<"p :"<< p<< endl;

	/*
	cout << " resultado multiplicacion(a0,b0)"<<endl;
	cout <<"a1 :"<< a1 << endl;
	cout <<"b1 :"<< b1 << endl;

	Bignum q = multiplicacion(a1,b1);

	cout << " resultado multiplicacion(a1,b1)"<<endl;

	Bignum wMasx = a0 + a1;
	Bignum zMasy = b0 + b1;

	Bignum r=multiplicacion(wMasx, zMasy);

	cout<< p.potencia_10(2*k)<<endl;
	cout<< (r-p-q).potencia_10(k)<<endl;
	cout<< q <<endl;
	
	cout << " resultado final"<<endl;

	// Salida final, usamos la función Power implementada arriba
	*/
	return p;//p.potencia_10(2*k) + (r-p-q).potencia_10(k) + q;

};

Multiplicacion_karatsuba::~Multiplicacion_karatsuba(){};



