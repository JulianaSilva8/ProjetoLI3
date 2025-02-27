#ifndef ALBUNS_H
#define ALBUNS_H

/**
 * @brief Estrutura que armazena os dados relativos ao álbum.
 *
 * @param albumId Id do álbum.
 * @param title Título do álbum.
 * @param artistId Id do artista.
 * @param year Ano de lançamento do álbum.
 * @param producers Produtores do álbum.
 */
typedef struct Album Album;

/**
 * @brief Retornao id de um álbum.
 *
 * @param album Ponteiro para o álbum.
 */
const char* getAlbumId(Album* album);

/**
 * @brief Retorna o título de um álbum.
 *
 * @param album Ponteiro para o álbum.
 */
const char* getAlbumTitle(Album* album);

/**
 * @brief Retorna o id do artista de um álbum.
 *
 * @param album Ponteiro para o álbum.
 */
const char* getAlbumArtistId(Album* album);

/**
 * @brief Retorna o ano de lançamento de um álbum.
 *
 * @param album Ponteiro para o álbum.
 */
const char* getAlbumYear(Album* album);

/**
 * @brief Retorna os produtores de um álbum.
 *
 * @param album Ponteiro para o álbum.
 */
const char* getAlbumProducers(Album* album);

/**
 * @brief Cria um novo álbum.
 *
 * Aloca memória para um novo álbum e inicializa os campos com NULL.
 *
 * @return Ponteiro para o álbum.
 */
Album* criaAlbum();

/**
 * @brief Liberta a memória alocada para um álbum.
 *
 * Liberta a memória alocada para os campos de um álbum e para o álbum em si.
 *
 * @param album Ponteiro para o álbum.
 */
void freeAlbum(Album* album);

/**
 * @brief Preenche um campo do álbum com o valor fornecido.
 *
 * @param album Ponteiro para o álbum.
 * @param index Índice do campo a preencher.
 * @param value Valor a preencher no campo.
 */
void albumField(Album* album, int index, const char* value);

#endif