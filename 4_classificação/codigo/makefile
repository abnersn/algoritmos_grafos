main:
	gcc -Wall -g -c ./fila/fila.c -o ./obj/fila.o
	gcc -Wall -g -c ./pilha/pilha.c -o ./obj/pilha.o
	gcc -Wall -g -c ./grafo/grafo.c -o ./obj/grafo.o
	gcc -Wall -g -c ./busca/busca.c -o ./obj/busca.o
	gcc -Wall -g -c ./questao/questao.c -o ./obj/questao.o
	gcc -Wall -g -c main.c -o ./obj/main.o
	gcc -Wall -g ./obj/pilha.o ./obj/fila.o ./obj/grafo.o ./obj/busca.o ./obj/questao.o ./obj/main.o -o compilado.bin
	./compilado.bin
