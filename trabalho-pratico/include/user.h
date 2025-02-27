/**
 * @file user.h
 * @brief Declarações de funções e estruturas para manipulação de usuários.
 */

#ifndef USER_H
#define USER_H

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "gestor_music.h"
#include "history.h"

/**
 * @brief Declaração opaca da struct Historico.
 */
typedef struct Historico Historico;

/**
 * @brief Declaração opaca da struct User.
 */
typedef struct User User;

/**
 * @brief Cria um novo usuário.
 * @return Ponteiro para a nova estrutura User.
 */
User* criaUser();

/**
 * @brief Libera a memória alocada para um usuário.
 * @param user Ponteiro para a estrutura User a ser liberada.
 */
void freeUser(User* user);

/**
 * @brief Obtém dados do usuário em uma matriz.
 * @param matrix Matriz de caracteres para armazenar os dados.
 * @param user Ponteiro para a estrutura User.
 */
void getDataOnMatrix(char ***matrix, const User* user);

/**
 * @brief Obtém a duração do histórico do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param index Índice do histórico.
 * @return Duração do histórico como string.
 */
char* getDuration_Historico(const User* user, int index);

/**
 * @brief Obtém o timestamp do histórico do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param index Índice do histórico.
 * @return Timestamp do histórico como string.
 */
char* getTimestamp_Historico(const User* user, int index);

/**
 * @brief Obtém o ID da música do histórico do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param index Índice do histórico.
 * @return ID da música como string.
 */
char* getMusicId_Historico(const User* user, int index);

/**
 * @brief Obtém o tamanho do histórico do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Tamanho do histórico.
 */
int getHistoricoSize(const User* user);

/**
 * @brief Obtém o nome de usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Nome de usuário como string.
 */
char* getUsername(const User* user);

/**
 * @brief Obtém o email do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Email como string.
 */
char* getEmail(const User* user);

/**
 * @brief Obtém o primeiro nome do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Primeiro nome como string.
 */
char* getFirstName(const User* user);

/**
 * @brief Obtém o sobrenome do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Sobrenome como string.
 */
char* getLastName(const User* user);

/**
 * @brief Obtém a data de nascimento do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Data de nascimento como string.
 */
char* getDataNascimento(const User* user);

/**
 * @brief Obtém o país do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return País como string.
 */
char* getPais(const User* user);

/**
 * @brief Obtém a subscrição do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Subscrição como string.
 */
char* getSubscriçao(const User* user);

/**
 * @brief Obtém os gostos musicais do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param count Ponteiro para armazenar a contagem de gostos musicais.
 * @return Array de strings com os gostos musicais.
 */
char** getGostosMusicas(const User* user, int* count);

/**
 * @brief Obtém a lista de músicas do usuário.
 * @param user Ponteiro para a estrutura User.
 * @return Lista de músicas como string.
 */
char* getListaMusicas(const User* user);

/**
 * @brief Define o histórico do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param history Ponteiro para a estrutura History.
 */
void setHistory(User* user, History* history);

/**
 * @brief Define o nome de usuário.
 * @param user Ponteiro para a estrutura User.
 * @param username Nome de usuário como string.
 */
void setUsername(User* user, const char* username);

/**
 * @brief Define o email do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param email Email como string.
 */
void setEmail(User* user, const char* email);

/**
 * @brief Define o primeiro nome do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param firstName Primeiro nome como string.
 */
void setFirstName(User* user, const char* firstName);

/**
 * @brief Define o sobrenome do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param lastName Sobrenome como string.
 */
void setLastName(User* user, const char* lastName);

/**
 * @brief Define a data de nascimento do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param dataNascimento Data de nascimento como string.
 */
void setDataNascimento(User* user, const char* dataNascimento);

/**
 * @brief Define o país do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param pais País como string.
 */
void setPais(User* user, const char* pais);

/**
 * @brief Define a subscrição do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param subscriçao Subscrição como string.
 */
void setSubscriçao(User* user, const char* subscriçao);

/**
 * @brief Adiciona um gosto musical ao usuário.
 * @param user Ponteiro para a estrutura User.
 * @param gostoMusica Gosto musical como string.
 */
void addGostoMusica(User* user, const char* gostoMusica);

/**
 * @brief Libera a memória alocada para um usuário.
 * @param user Ponteiro para a estrutura User a ser liberada.
 */
void freeUser(User* user);

/**
 * @brief Define um campo do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param index Índice do campo.
 * @param value Valor do campo como string.
 */
void userField(User* user, int index, const char* value);

/**
 * @brief Calcula a idade a partir da data de nascimento.
 * @param data_nascimento Data de nascimento como string.
 * @return Idade calculada.
 */
int idade(const char* data_nascimento);

/**
 * @brief Imprime os dados do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param n Número de usuários a serem impressos.
 */
void printUser(User* user, int n);

/**
 * @brief Valida o email do usuário.
 * @param email Email como string.
 * @return 1 se válido, 0 caso contrário.
 */
int emailValida(const char* email);

/**
 * @brief Valida a subscrição do usuário.
 * @param sub Subscrição como string.
 * @return 1 se válido, 0 caso contrário.
 */
int subValida(const char* sub);

/**
 * @brief Valida a data.
 * @param date Data como string.
 * @return 1 se válida, 0 caso contrário.
 */
int dataValida(const char* date);

/**
 * @brief Valida a lista de músicas.
 * @param lista Lista de músicas como string.
 * @param hashTable Tabela hash de músicas.
 * @return 1 se válida, 0 caso contrário.
 */
int listaValida (const char* lista, gestorMusic* hashTable);

/**
 * @brief Exibe uma mensagem de erro.
 * @param user Ponteiro para a estrutura User.
 * @param flag Código do erro.
 * @param header Cabeçalho da mensagem de erro.
 */
void erro(User* user,int flag,char* header);

/**
 * @brief Imprime os dados do usuário.
 * @param user Ponteiro para a estrutura User.
 * @param n Número de usuários a serem impressos.
 */
void printUser(User* user, int n);

#endif // USER_H
