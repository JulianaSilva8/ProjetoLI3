CC = gcc
CFLAGS = -Wall -Wextra -g $(shell pkg-config --cflags glib-2.0) -lm -lncurses
LDFLAGS = $(shell pkg-config --libs glib-2.0)

all: programa-principal programa-interativo programa-testes

programa-principal: src/main.o src/main_interativo.o src/gestores_entidades/gestor_user.o src/entidades/user.o src/gestores_entidades/gestor_music.o src/entidades/music.o src/gestores_entidades/gestor_artist.o src/entidades/artist.o src/estruturas_de_dados/tree.o src/estruturas_de_dados/tree_data_history.o src/querys/q6.o src/querys/q5.o src/querys/q4.o src/querys/q3.o src/querys/q2.o src/querys/q1.o src/validacoes/validacoes_musicas.o src/estruturas_de_dados/load_db.o src/querys/gestor_query.o src/io/parser_inputs.o src/io/output.o src/utils.o src/gestores_entidades/gestor_albuns.o src/entidades/albuns.o src/gestores_entidades/gestor_history.o src/entidades/history.o src/entidades/data_artist src/recomendador/recomendador-linux-x86_64.o
	$(CC) -o programa-principal src/main_interativo.o src/main.o src/gestores_entidades/gestor_user.o src/entidades/user.o src/gestores_entidades/gestor_music.o src/entidades/music.o src/gestores_entidades/gestor_artist.o src/entidades/artist.o src/estruturas_de_dados/tree.o src/estruturas_de_dados/tree_data_history.o src/querys/q6.o src/querys/q4.o src/querys/q5.o src/querys/q3.o src/querys/q2.o src/querys/q1.o src/validacoes/validacoes_musicas.o src/estruturas_de_dados/load_db.o src/querys/gestor_query.o src/io/parser_inputs.o src/io/output.o src/utils.o src/gestores_entidades/gestor_albuns.o src/entidades/albuns.o src/gestores_entidades/gestor_history.o src/entidades/history.o src/entidades/data_artist src/recomendador/recomendador-linux-x86_64.o $(CFLAGS) $(LDFLAGS)

programa-interativo: src/main_interativo.o src/main.o src/gestores_entidades/gestor_user.o src/entidades/user.o src/gestores_entidades/gestor_music.o src/entidades/music.o src/gestores_entidades/gestor_artist.o src/entidades/artist.o src/estruturas_de_dados/tree.o src/estruturas_de_dados/tree_data_history.o src/querys/q6.o src/querys/q5.o src/querys/q4.o src/querys/q3.o src/querys/q2.o src/querys/q1.o src/validacoes/validacoes_musicas.o src/estruturas_de_dados/load_db.o src/querys/gestor_query.o src/io/parser_inputs.o src/io/output.o src/utils.o src/gestores_entidades/gestor_albuns.o src/entidades/albuns.o src/gestores_entidades/gestor_history.o src/entidades/history.o src/entidades/data_artist src/recomendador/recomendador-linux-x86_64.o
	$(CC) -o programa-interativo src/main.o src/main_interativo.o src/gestores_entidades/gestor_user.o src/entidades/user.o src/gestores_entidades/gestor_music.o src/entidades/music.o src/gestores_entidades/gestor_artist.o src/entidades/artist.o src/estruturas_de_dados/tree.o src/estruturas_de_dados/tree_data_history.o src/querys/q6.o src/querys/q4.o src/querys/q5.o src/querys/q3.o src/querys/q2.o src/querys/q1.o src/validacoes/validacoes_musicas.o src/estruturas_de_dados/load_db.o src/querys/gestor_query.o src/io/parser_inputs.o src/io/output.o src/utils.o src/gestores_entidades/gestor_albuns.o src/entidades/albuns.o src/gestores_entidades/gestor_history.o src/entidades/history.o src/entidades/data_artist src/recomendador/recomendador-linux-x86_64.o $(CFLAGS) $(LDFLAGS)

src/main.o: src/main.c include/main_interativo.h include/gestor_user.h include/gestor_music.h include/gestor_artist.h include/gestor_albuns.h include/gestor_history.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o 

src/main_interativo.o: src/main_interativo.c include/main_interativo.h
	$(CC) $(CFLAGS) -c src/main_interativo.c -o src/main_interativo.o
	
src/gestores_entidades/gestor_user.o: src/gestores_entidades/gestor_user.c include/gestor_user.h
	$(CC) $(CFLAGS) -c src/gestores_entidades/gestor_user.c -o src/gestores_entidades/gestor_user.o

src/entidades/user.o: src/entidades/user.c include/user.h
	$(CC) $(CFLAGS) -c src/entidades/user.c -o src/entidades/user.o

src/gestores_entidades/gestor_music.o: src/gestores_entidades/gestor_music.c include/gestor_music.h
	$(CC) $(CFLAGS) -c src/gestores_entidades/gestor_music.c -o src/gestores_entidades/gestor_music.o

src/entidades/music.o: src/entidades/music.c include/music.h
	$(CC) $(CFLAGS) -c src/entidades/music.c -o src/entidades/music.o

src/gestores_entidades/gestor_artist.o: src/gestores_entidades/gestor_artist.c include/gestor_artist.h
	$(CC) $(CFLAGS) -c src/gestores_entidades/gestor_artist.c -o src/gestores_entidades/gestor_artist.o

src/entidades/artist.o: src/entidades/artist.c include/artist.h
	$(CC) $(CFLAGS) -c src/entidades/artist.c -o src/entidades/artist.o

src/estruturas_de_dados/tree.o: src/estruturas_de_dados/tree.c include/tree.h
	$(CC) $(CFLAGS) -c src/estruturas_de_dados/tree.c -o src/estruturas_de_dados/tree.o

src/querys/q1.o: src/querys/q1.c include/q1.h
	$(CC) $(CFLAGS) -c src/querys/q1.c -o src/querys/q1.o

src/querys/q2.o: src/querys/q2.c include/q2.h
	$(CC) $(CFLAGS) -c src/querys/q2.c -o src/querys/q2.o

src/querys/q3.o: src/querys/q3.c include/q3.h
	$(CC) $(CFLAGS) -c src/querys/q3.c -o src/querys/q3.o

src/querys/q4.o: src/querys/q4.c include/q4.h
	$(CC) $(CFLAGS) -c src/querys/q4.c -o src/querys/q4.o

src/querys/q5.o: src/querys/q5.c include/q5.h
	$(CC) $(CFLAGS) -c src/querys/q5.c -o src/querys/q5.o

src/querys/q6.o: src/querys/q6.c include/q6.h
	$(CC) $(CFLAGS) -c src/querys/q6.c -o src/querys/q6.o

src/validacoes/validacoes_musicas.o: src/validacoes/validacoes_musicas.c include/validacoes_musicas.h
	$(CC) $(CFLAGS) -c src/validacoes/validacoes_musicas.c -o src/validacoes/validacoes_musicas.o

src/estruturas_de_dados/load_db.o: src/estruturas_de_dados/load_db.c include/load_db.h
	$(CC) $(CFLAGS) -c src/estruturas_de_dados/load_db.c -o src/estruturas_de_dados/load_db.o

src/querys/gestor_query.o: src/querys/gestor_query.c include/gestor_query.h
	$(CC) $(CFLAGS) -c src/querys/gestor_query.c -o src/querys/gestor_query.o

src/io/parser_inputs.o: src/io/parser_inputs.c include/parser_inputs.h
	$(CC) $(CFLAGS) -c src/io/parser_inputs.c -o src/io/parser_inputs.o

src/io/output.o: src/io/output.c include/output.h
	$(CC) $(CFLAGS) -c src/io/output.c -o src/io/output.o

src/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c src/utils.c -o src/utils.o

src/gestores_entidades/gestor_albuns.o: src/gestores_entidades/gestor_albuns.c include/gestor_albuns.h
	$(CC) $(CFLAGS) -c src/gestores_entidades/gestor_albuns.c -o src/gestores_entidades/gestor_albuns.o

src/entidades/albuns.o: src/entidades/albuns.c include/albuns.h
	$(CC) $(CFLAGS) -c src/entidades/albuns.c -o src/entidades/albuns.o

src/gestores_entidades/gestor_history.o: src/gestores_entidades/gestor_history.c include/gestor_history.h
	$(CC) $(CFLAGS) -c src/gestores_entidades/gestor_history.c -o src/gestores_entidades/gestor_history.o

src/entidades/history.o: src/entidades/history.c include/history.h
	$(CC) $(CFLAGS) -c src/entidades/history.c -o src/entidades/history.o

src/entidades/data_artist: src/entidades/data_artist.c include/data_artist.h
	$(CC) $(CFLAGS) -c src/entidades/data_artist.c -o src/entidades/data_artist

src/estruturas_de_dados/tree_data_history.o: src/estruturas_de_dados/tree_data_history.c include/tree_data_history.h
	$(CC) $(CFLAGS) -c src/estruturas_de_dados/tree_data_history.c -o src/estruturas_de_dados/tree_data_history.o

# Programa de testes
programa-testes: src/programatestes.o
	$(CC) -o programa-testes src/programatestes.o $(CFLAGS)

src/programatestes.o: src/programatestes.c
	$(CC) $(CFLAGS) -c src/programatestes.c -o src/programatestes.o

clean:
	rm -f src/*.o src/gestores_entidades/*.o src/entidades/*.o src/estruturas_de_dados/*.o src/querys/*.o src/validacoes/*.o src/io/*.o programa-principal programa-testes
	rm -f resultados/*
	rm -f "input_interativo.txt"

valgrind: programa-principal
	valgrind --leak-check=full ./programa-principal dataset/ input.txt

run-principal: programa-principal
	./programa-principal dataset/ input.txt

run-interativo: programa-interativo
	./programa-interativo

run-testes: programa-testes
	./programa-testes dataset/ input.txt resultados-esperados/

