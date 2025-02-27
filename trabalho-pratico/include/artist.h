#ifndef ARTIST_H
#define ARTIST_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Estrutura que armazena os dados relativos ao artista.
 *
 * @param artistId Id do artista.
 * @param country País do artista.
 * @param name Nome do artista.
 * @param type Tipo do artista.
 * @param id_constituent Id do constituinte.
 * @param artistDuration Duração total do artista.
 * @param album_count Número de albuns do artista.
 */
typedef struct Artist Artist;

/**
 * @brief Retornao Id de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
char* getArtistId(const Artist* artist);

/**
 * @brief Retorna o país de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
char* getArtistCountry(const Artist* artist);

/**
 * @brief Retorna o nome de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
char* getArtistName(const Artist* artist);

/**
 * @brief Retorna o tipo de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
char* getArtistType(const Artist* artist);

/**
 * @brief Retorna a lista de id dos constituintes caso o artista seja coletivo.
 *
 * @param artist Ponteiro para o artista.
 */
char* getArtistIdConstituent(const Artist* artist);

/**
 * @brief Retorna a duração total de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
int getArtistDuration(const Artist* artist);

/**
 * @brief Retorna o número de albuns de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
int getArtistAlbumCount(const Artist* artist);

/**
 * @brief Adiciona a duração ao artista.
 *
 * Acumula a duração do artista.
 *
 * @param artist Ponteiro para o artista.
 * @param duration Duração a adicionar.
 */
void addArtistDuration(Artist* artist, int duration);

/**
 * @brief Define o número de albuns de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
void setAlbumCount(Artist* artist);

/**
 * @brief Define o total de reproduções de um artista.
 *
 * @param artist Ponteiro para o artista.
 */
void setRepCount(Artist* artist);

/**
 * @brief Define o total de reproduções de participação de um artista.
 *
 * @param artist Ponteiro para o artista.
 * @param artist_a Ponteiro para o artista.
 * @param num Número de partes.
 */
void setRepCountPart(Artist* artist,Artist* artist_a,int num);

/**
* @brief Cria um novo artista.
*
* Aloca memória para um novo artista e inicializa os campos com NULL.
*
* @return Ponteiro para o artista.
*/
Artist* criaArtist();

/**
 * @brief Liberta a memória alocada para um artista.
 *
 * Liberta a memória alocada para os campos de um artista e para o artista em si.
 *
 * @param artist Ponteiro para o artista.
 */
void freeArtist(Artist* artists);

/**
 * @brief Preenche um campo do artista com o valor fornecido.
 *
 * @param artist Ponteiro para o artista.
 * @param index Índice do campo a preencher.
 * @param value Valor a preencher no campo.
 */
void artistField(Artist* artists, int index, const char* value);

/**
 * @brief Reseta a duração do artista a 0.
 *
 * @param artist Ponteiro para o artista.
 */
void resetArtistDuration(Artist* artist);

/**
 * @brief Compara a duração de dois artistas.
 *
 * @param a Ponteiro para o primeiro artista.
 * @param b Ponteiro para o segundo artista.
 * @return 0 se forem iguais, < 0 se a < b, > 0 se a > b.
 */
int comparaArtistDuration(const Artist* a, const Artist* b);

/**
 * @brief Ordena a lista de artistas por duração.
 *
 * @param artistList Lista de artistas.
 * @return Lista de artistas ordenada por duração.
 */
GList* ordenaArtistasPorDuracao(GList* artistList);

/**
 * @brief Imprime o artista com os campos pedidos para a query 2.
 *
 * @param artist Ponteiro para o artista.
 * @param n Número da linha.
 * @param ficheiro_vazio Flag que indica se o ficheiro está vazio.
 * @param existe_s Flag que indica se o ficheiro tem a opção -s.
 */
void printArtist(Artist* artist, int n, int ficheiro_vazio, bool existe_s);

/**
 * @brief Imprime o top N artistas para a query 2.
 *
 * @param artistList Lista de artistas.
 * @param N Número de artistas a imprimir.
 * @param n_atualine Número da linha.
 * @param existe_s Flag que indica se o ficheiro tem a opção -s.
 */
void imprimeTopNArtistas(GList* artistList, int N, int n_atualine, bool existe_s);

/**
 * @brief Imprime dados do artista com os campos pedidos para a query 4.
 *
 * @param matrix Matriz com os dados do artista.
 * @param topartist Nome do artista.
 * @param max_freq Frequência máxima.
 * @param tipo Tipo de artista.
 */
void printArtist2(char* topartist, int n, int ficheiro_vazio, char* tipo, int max_freq, bool existe_s);

/**
 * @brief Valida se o type é individual e se o id_constituent não é vazio.
 *
 * @param matrix Matriz com os dados do artista.
 * @param topartist Nome do artista.
 * @param max_freq Frequência máxima.
 * @param tipo Tipo de artista.
 */
bool validaElementos(const char* type, const char* id_constituent);

/**
 * @brief Envia os artistas não válidos para a pasta de erros.
 *
 * @param artist Ponteiro para o artista.
 * @param flag Flag que indica se o artista é válido.
 * @param header Nome do ficheiro.
 * @param token2 Token do artista.
 */
void erroArtist(Artist* artist,int flag,char* header,char* token2);

#endif