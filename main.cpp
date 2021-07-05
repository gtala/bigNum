// Prueba de la clase cmdline: dado un precision entero pasado por la
// l�nea de comando, leemos una secuencia de n�meros que ingresan
// por la entrada est�ndar, los multiplicamos por ese precision, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h> 
#include <string.h>

#include "cmdline.h"
#include "Bignum.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_multiplicacion(string const &);
static void opt_help(string const &);


class BigNumHelper {

public:
	Bignum getNewBigNum(string num) {

		Bignum bn(num.length());
		for (size_t j = 0;j < num.length();j++) {
			int v = num[j] - 48;
			bn.set_digito(j, v);
		}
		return bn;
	}

	Bignum printBigNum(Bignum bn) {

		auto digit = bn.get_digitos();
		for (size_t j = 0; j < bn.size();j++) {
			cout << bn.get_digito(j) << endl;
		}
		return bn;
	}

};

// Tabla de opciones de l�nea de comando. El formato de la tabla
// consta de un elemento por cada opci�n a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opci�n lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opci�n.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opci�n en caso que no est� expl�citamente presente
//   en la l�nea de comandos del programa. Si la opci�n no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al m�todo de parseo de la opci�n,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La �ltima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opci�n: cuando la
//   opci�n es obligatoria, deber� activarse OPT_MANDATORY.
//
// Adem�s, la �ltima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "multiplicacion","-", opt_multiplicacion,OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
static int precision = 4;
static string tipo_multiplicacion="karatsuba"; // por defecto karatsuba
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "No se puede abrir "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "No se puede abrir "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_multiplicacion(string const &arg)
{
	istringstream iss(arg);
	
	// Intentamos extraer el precision de la l�nea de comandos.
	// Para detectar argumentos que �nicamente consistan de 
	// n�meros enteros, vamos a verificar que EOF llegue justo
	// despu�s de la lectura exitosa del escalar.
	//
	if (!(iss >> tipo_multiplicacion)
	    || !iss.eof() || (tipo_multiplicacion !="karatsuba" && tipo_multiplicacion !="standard") ) {
		cerr << "El tipo de multiplicacion no es correcto -->"
		     << arg
		     << ".Ingrese \"standard\" o \"karatsuba\" "
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "No se puede leer el entero de precision"
		     << endl;
		exit(1);
	}
}

static void
opt_help(string const &arg)
{
	cout << "./tp1.exe -m multiplicacion [-i file] [-o file]"
	     << endl;
	exit(0);
}



void escribe_salida(Bignum & a,Bignum & b,char &operacion,bool entrada,ostream *os){

	if( entrada ){
			switch(operacion) 
			{
				case '*': 
					*os << (a * b) <<"\n";
					break;
				case '+': 
					*os << (a + b) <<endl;
					break;
				case '-':
					*os << (a - b)<<"\n"; 
					break;
				case 'a':
					*os << a <<"\n"; 
					break;
				case 'v':
					*os << "" << endl; 
					break;
				
				default: *os << "Operacion invalida" <<"\n";
			}

	}
	
	else{
		*os << "Entrada invalida" <<"\n";
	}
	
}


void
procesa_entrada(istream *is, ostream *os)
{
	
	bool entrada=false;
	char operacion='i';
	Bignum a(precision),b(precision);

    //cout<<tipo_multiplicacion<<endl;

    if(tipo_multiplicacion=="standard"){
        a.set_tipo_multiplicacion(true); // tipo de multiplicacion normal
        b.set_tipo_multiplicacion(true); // tipo de multiplicacion normal
    }
        

	while( is->peek() != EOF){

		

		if(*is >> a && *is >> operacion && (operacion=='+'||operacion=='-'||operacion=='*')&& operacion !='\n' && *is >> b){
			//*os << a ;
			//*os << operacion;
			//*os << b <<"=";
			entrada=true;
		}
		else{
			entrada=false;
		}
		
		// acomode lo bignum a y b y que le quite 
		escribe_salida(a,b,operacion,entrada,os);
		is->clear();

	}


	if (os->bad()) {
		cerr << "No puede escribir en el flujo de salida."
		     << endl;
		exit(1);
	}
	if (is->bad()) {
		cerr << "No puede leer desde flujo de entrada."
		     << endl;
		exit(1);
	}
	if (!is->eof()) {
		cerr << "No puede encontrar EOF en el flujo de entrada."
		     << endl;
		exit(1);
	}
}

//TODO: funcion main original
//int
//main(int argc, char * const argv[])
//{
//	
//	cmdline cmdl(options);
//	cmdl.parse(argc, argv);
//	procesa_entrada(iss, oss);
//	return EXIT_SUCCESS;
//}


int main(int argc, char* const argv[])
{
	Multiplicacion_karatsuba* multiplicadorK = new Multiplicacion_karatsuba;
	BigNumHelper* helper = new BigNumHelper;
	Bignum a = helper->getNewBigNum("105");
	Bignum b = helper->getNewBigNum("205");

	helper->printBigNum(a);
	helper->printBigNum(b);

	

   Bignum  c = multiplicadorK->multiplicacion(a, b);
	
	return EXIT_SUCCESS;
}




