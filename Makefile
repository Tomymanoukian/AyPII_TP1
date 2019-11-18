objects_fft = complejo.o vector_t.o fft.o
objects_dft = complejo.o vector_t.o dft.o test_dft.o
objects_prog = complejo.o vector_t.o dft.o fft.o cmdline.o main.o
objects_diff = complejo.o vector_t.o test_diff.o

programa: $(objects_prog)
	g++ -Wall -g -o programa $(objects_prog)

cmdline.o: cmdline.cpp cmdline.h
	g++ -Wall -g -c cmdline.cpp

complejo.o : complejo.cpp complejo.h
	g++ -Wall -g -c complejo.cpp

vector_t.o : vector_t.cpp vector_t.h complejo.h
	g++ -Wall -g -c vector_t.cpp

dft.o : dft.cpp dft.h vector_t.h complejo.h
	g++ -Wall -g -c dft.cpp

fft.o : fft.cpp fft.h vector_t.h complejo.h
	g++ -Wall -g -c fft.cpp

main.o : main.cpp cmdline.h complejo.h vector_t.h dft.h
	g++ -Wall -g -c main.cpp

test_dft.o: test_dft.cpp
	g++ -Wall -g -c test_dft.cpp

test_vector.o : test_vector.cpp
	g++ -Wall -g -c test_vector.cpp

test_diff.o: test_diff.cpp complejo.h vector_t.h
	g++ -Wall -g -c test_diff.cpp

#los archivos de prueba se deben llamar test y un numero
test_programa_dft: programa test_diff.o 
	@g++ -Wall -g -o test_diff $(objects_diff)

	@echo "\n--------INICIA PRUEBA DE PROGRAMA--------\n"

	@echo "Probando dft sin argumento -m: "
	@set -e; for t in test_dft?; do                   \
		echo Aplicando DFT a $$t;                     \
		./programa -i $$t -o $$t.out;                 \
	done

	@echo "\n"

	@set -e; for t in test_dft?; do                   \
		echo Testing: $$t;                            \
		./test_diff $$t dft;                          \
		echo Test ok;                                 \
	done

	@rm *.out

	@echo "\nProbando dft con argumento -m: "
	@set -e; for t in test_dft?; do                   \
		echo Aplicando DFT a $$t;                     \
		./programa -m "dft" -i $$t -o $$t.out;        \
	done

	@echo "\n"

	@set -e; for t in test_dft?; do                   \
		echo Testing: $$t;                            \
		./test_diff $$t dft;                          \
		echo Test ok;                                 \
	done
	@echo "\nTEST_DFT OK.\n"

	@echo "Probando idft:"
	@set -e; for t in test_idft?; do                  \
		echo Aplicando IDFT a $$t;                    \
		./programa -m "idft" -i $$t -o $$t.out;       \
	done

	@echo "\n"

	@set -e; for t in test_idft?; do                  \
		echo Testing: $$t;                            \
		./test_diff $$t idft;                         \
		echo Test ok;                                 \
	done
	@echo "\nTEST_IDFT OK.\n"

	@rm *.out test_diff

#comprueba que no haya fugas de memoria en el programa
test_programa_valgrind: programa
	@echo "\n--------INICIA PRUEBA DE MEMORIA--------\n"

	@set -e; for t in test_dft?; do                                           \
		echo "\n" testing: $$t "\n";                                          \
		valgrind --leak-check=full ./programa -m "dft" -i $$t -o $$t.out;     \
	done

	@set -e; for t in test_idft?; do                                          \
		echo "\n" testing: $$t "\n";                                          \
		valgrind --leak-check=full ./programa -m "idft" -i $$t -o $$t.out;    \
	done

	@echo "\n" testing: argumento "--help" "\n"

	@set -e; valgrind --leak-check=full ./programa -h;

	@rm *.out

	@echo "\n--------PRUEBA DE MEMORIA FINALIZADA--------\n"

#Prueba de la clase vector_t
test-vector_t: complejo.o vector_t.o test_vector.o
	g++ -Wall -o test_vector_t complejo.o vector_t.o test_vector.o

#Empieza la ejecución de la prueba y compara los achivos
	@./test_vector_t test_vector_t.txt
	@printf "\n-----Prueba de Vector_t-----\n\n"
	-@diff -T -s -b -w test_vector_t.txt out_test_vector_t.txt
	@rm complejo.o vector_t.o test_vector.o test_vector_t

test-vector_t-memory: complejo.o vector_t.o test_vector.o
	g++ -Wall -o test-vector_t-memory complejo.o vector_t.o test_vector.o
	@printf "\n-----Prueba de memoria del Vector_t-----\n\n"
	@valgrind --leak-check=yes ./test-vector_t-memory test_vector_t.txt
	@rm complejo.o vector_t.o test_vector.o test-vector_t-memory

clean:
	@rm -f *o *.out programa test_diff