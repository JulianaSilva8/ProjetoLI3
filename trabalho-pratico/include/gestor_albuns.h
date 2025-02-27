#ifndef GESTOR_ALBUNS_H
#define GESTOR_ALBUNS_H
#include <glib.h>
#include "albuns.h"

/**
 * @brief Estrutura que armazena o gestor de álbuns.
 *
 * @param hashTable hashTable que armazena os álbuns.
 */
typedef struct gestorAlbuns gestorAlbuns;

/**
 * @brief Cria um novo gestor de álbuns.
 *
 * Aloca memória para um novo gestor de álbuns e inicializa a hashTable com as funções de hash e comparação de strings.
 *
 * @return Ponteiro para o gestor de álbuns.
 */
gestorAlbuns* criaGestorAlbuns();

/**
 * @brief Liberta a memória alocada para o gestor de álbuns.
 *
 * Liberta a memória alocada para a hashTable e para o gestor de álbuns.
 *
 * @param gestor Ponteiro para o gestor de álbuns.
 */
void freeGestorAlbuns(gestorAlbuns* gestor);

/**
 * @brief Insere um álbum no gestor de álbuns.
 *
 * @param gestor Ponteiro para o gestor de álbuns.
 * @param album Ponteiro para o álbum.
 */
void insereAlbum(gestorAlbuns* gestor, Album* album);

/**
 * @brief Procura um álbum no gestor de álbuns.
 *
 * @param gestor Ponteiro para o gestor de álbuns.
 * @param album_id Id do álbum.
 */
Album* procuraAlbum(gestorAlbuns* gestor, const char* album_id);

#endif