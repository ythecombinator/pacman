#ifndef _MAPA_H_
#define _MAPA_H_
#define HERO '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa{
	char** matriz;
	int linhas, colunas;
};
typedef struct mapa MAPA;

struct posicao{
	int x, y;
}; 
typedef struct posicao POSICAO;

int encontraMapa(MAPA* m, POSICAO* p, char c);
void alocaMapa(MAPA* m);
void liberaMapa(MAPA* m);
void leMapa(MAPA* m);
int isValid(MAPA* m, int x, int y);
int isEmpty(MAPA* m, int x, int y);
void walking(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiaMapa(MAPA* destino, MAPA* origem);
int canWalk(MAPA* m, char personagem, int x, int y);
int isCharacter(MAPA* m, char personagem, int x, int y);
int isWall(MAPA* m, int x, int y);
#endif