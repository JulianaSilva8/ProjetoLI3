#ifndef HISTORY_H
#define HISTORY_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Estrutura que armazena o histórico de reprodução.
 *
 * @param historyId Id do histórico.
 * @param user_id Id do utilizador.
 * @param music_id Id da música.
 * @param timestamp Data e hora da reprodução.
 * @param duration Duração da música.
 * @param platform Plataforma de reprodução.
 */
typedef struct History History;

/**
 * @brief Retorna o Id do utilizador.
 *
 * @param history Ponteiro para o histórico.
 */
char* getUserid_History(History* history);

/**
 * @brief Retorna o Id do histórico.
 *
 * @param history Ponteiro para o histórico.
 */
char* getHistoryId(const History* history);

/**
 * @brief Retorna o Id da música.
 *
 * @param history Ponteiro para o histórico.
 */
char* getMusicId_History(History* history);

/**
 * @brief Retorna a duração de reprodução da música.
 *
 * @param history Ponteiro para o histórico.
 */
char* getDuration_History(History* history);

/**
 * @brief Retorna a data e hora da reprodução.
 *
 * @param history Ponteiro para o histórico.
 */
char* getTimestamp_History(History* history);

/**
 * @brief Retorna a plataforma de reprodução.
 *
 * @param history Ponteiro para o histórico.
 */
char* getPlatform_History(History* history);

/**
 * @brief Cria um novo histórico.
 *
 * Aloca memória para um novo histórico e inicializa os campos com NULL.
 *
 * @return Ponteiro para o histórico.
 */
History* criaHistory();

/**
 * @brief Liberta a memória alocada para um histórico.
 *
 * Liberta a memória alocada para os campos de um histórico e para o histórico em si.
 *
 * @param historical Ponteiro para o histórico.
 */
void freeHistory(History* historical);

/**
 * @brief Preenche um campo do histórico com o valor fornecido.
 *
 * @param historical Ponteiro para o histórico.
 * @param index Índice do campo a preencher.
 * @param value Valor a preencher no campo.
 */
void historyField(History* historical, int index, const char* value);

/**
 * @brief Envia os históricos não válidos para a pasta de erros.
 *
 * @param history Ponteiro para o histórico.
 * @param flag Flag que indica se o histórico é válido.
 * @param header Nome do ficheiro.
 */
void erro_history(History* history,int flag,char* header);

#endif