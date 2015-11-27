#ifndef _PACMAN_H_
#define _PACMAN_H_
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

void move(char direcao);
int acabou();
int isDirecao(char direcao);
void fantasmas();
int moveFantasma(int xatual, int yatual, int* xdestino, int* ydestino);
void explode();
void explosion(int x, int y, int somax, int somay, int qtd);
#endif