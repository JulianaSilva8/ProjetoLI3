#ifndef Q5_H
#define Q5_H
#include "gestor_user.h"
#include "gestor_music.h"

/**
 * @brief Função auxiliar para construira  matriz com os dados para o output da query 5
 *
 * @param gestor_music - gestor de músicas
 * @param user - utilizador
 * @param matrix_user - matriz com os dados dos utilizadores
 * @param user_gender
 * @param line_atual - linha atual do ficheiro
 */
void buildmatrix(gestorMusic *gestor_music, User* user, char*** matrix_user, int *** user_gender, int line_atual);

/**
 * @brief Função que constroi a matriz com os dados para o output da query 5
 *
 * @param gestorMusic - gestor de músicas
 * @param gestorUser - gestor de utilizadores
 * @return matriz com os dados
 */
void** fazmatrix_q5(gestorMusic* gestorMusic, gestorUser* gestorUser);

/**
 * @brief Função que liberta a memória alocada para a matriz
 *
 * @param matriz_q5 - matriz com os dados
 * @param gestorUser - gestor de utilizadores
 */
void freeMatrixData(void** matriz_q5, gestorUser* user);
/**
 * @brief Query 5 - Esta função recebe  e devolve
 *
 * Esta funçao recebe  e devolve
 *
 * @param matriz_q5 - matriz com os dados
 * @param gestorUser - gestor de utilizadores
 * @param input - input do ficheiro
 * @param line1 - linha atual do ficheiro
 */

/**
 * @brief Query 5 - Esta função recebe um id de um utilizador e o número de utilizadores
 * a retornar e devolve uma lista de utilizadores semelhantes.
 *
 * Esta funçao devolve uma lista de utilizadores semelhantes ao utilizador dado.
 *
 * @param input - input do ficheiro
 * @param atualine - linha atual do ficheiro
 * @param gestor - gestor de utilizadores
 * @param gestor_m - gestor de músicas
 */
void query5(void** matriz_q5, gestorUser* gestorUser, char* input, int line1);

#endif