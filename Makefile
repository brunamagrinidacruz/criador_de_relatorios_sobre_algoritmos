all: clean relatorio
 
relatorio: relatorio.o ordenacoes.o vetores.o arquivos.o
	gcc relatorio.o ordenacoes.o vetores.o arquivos.o -lm -o relatorio 
 
relatorio.o: relatorio.c ordenacoes.h vetores.h arquivos.h
	gcc -o relatorio.o relatorio.c -c -W -g -Wall

arquivos.o: arquivos.c arquivos.h ordenacoes.h vetores.h
	gcc -o arquivos.o arquivos.c -c -W -Wall

vetores.o: vetores.c vetores.h
	gcc -o vetores.o vetores.c -c -W -Wall
 
ordenacoes.o: ordenacoes.c ordenacoes.h
	gcc -o ordenacoes.o ordenacoes.c -c -W -Wall
 
clean:
	rm -rf *.o *~ relatorio
