CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: tp1.exe
	

tp1.exe: main.o  Bignum.o cmdline.o  Multiplicacion.o Bignum.h Multiplicacion.h
	$(CXX) $(CXXFLAGS) -o tp1.exe main.o cmdline.o Bignum.o Multiplicacion.o

main.o: main.cc cmdline.h  Bignum.h
	$(CXX) $(CXXFLAGS) -c main.cc 
	
cmdline.o: cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cc	

Bignum.o: Bignum.h
	$(CXX) $(CXXFLAGS) -c Bignum.cc

Multiplicacion.o: Bignum.h  Multiplicacion.h 
	$(CXX) $(CXXFLAGS) -c Multiplicacion.cc 

test: test+ test- testx test100 test_longitud test_enunciado

test+:
	valgrind --leak-check=full ./tp1.exe  -p 100 -i casos_prueba_+.txt -o salida+.txt
test-:
	valgrind --leak-check=full ./tp1.exe -p 100 -i casos_prueba_-.txt -o salida-.txt
testx:
	valgrind --leak-check=full ./tp1.exe -p 100 -i casos_prueba_x.txt -o salidax.txt
test100:
	valgrind --leak-check=full --show-leak-kinds=all ./tp1.exe -p 100 -i input_p\=100_n\=1000.txt -o output_p\=100_n\=1000.txt
test_longitud:
	valgrind --leak-check=full ./tp1.exe  -p 1 -i casos_prueba_longitud.txt -o salida_longitud.txt
test_enunciado:
	./tp1.exe -p 2 -i /dev/null
	echo 1123581321345589*123456789 | ./tp1.exe -p 20
	echo "-1 - 5" | ./tp1.exe -p 1
	
clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
