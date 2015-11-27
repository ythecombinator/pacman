#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "pacman.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int pill = 0;

int moveFantasma(int xatual, int yatual, int* xdestino, int* ydestino){
	int opcoes[4][2] = {
		{xatual, yatual + 1},
		{xatual + 1, yatual},
		{xatual, yatual - 1},
		{xatual - 1, yatual}
	};

	srand(time(0));
	for(int i = 0; i < 10; i++){
		int posicao = rand() % 4;
		if(canWalk(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];

			return 1;
		}
	}

	return 0;
}

void fantasmas(){
	MAPA copia;

	copiaMapa(&copia, &m);
	for(int i = 0; i < m.linhas; i++){
		for(int j = 0; j < m.colunas; j++){
			if(copia.matriz[i][j] == FANTASMA){
				
				int xdestino, ydestino;
				int encontrou = moveFantasma(i, j, &xdestino, &ydestino);

				if(encontrou){
					walking(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}
	liberaMapa(&copia);
}

int acabou(){
	POSICAO pos;
	int pacman = encontraMapa(&m, &pos, HERO);
	printf("Perdeu otário\n");
	return !pacman;
}

void explode(){
	if(!pill) return;
	explosion(heroi.x, heroi.y, 0, 1, 3);
	explosion(heroi.x, heroi.y, 0, -1, 3);
	explosion(heroi.x, heroi.y, 1, 0, 3);
	explosion(heroi.x, heroi.y, -1, 0, 3);

	pill = 0;
}

void explosion(int x, int y, int somax, int somay, int qtd){
	
	if(qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!isValid(&m, novox, novoy)) return;
	if(isWall(&m, novox, novoy)) return;
	m.matriz[novox][novoy] = VAZIO;
	explosion(novox, novoy, somax, somay, qtd - 1);	
}

int isDirecao(char direcao){
	return direcao == 'a' ||
		direcao == 'w' ||
		direcao == 's' ||
		direcao == 'd';
}

void move(char direcao){
	
	if(!isDirecao(direcao))
		return;

	int proximoX = heroi.x;
	int proximoY = heroi.y;

	switch(direcao){
		case ESQUERDA: 
			proximoY--;
			break;
		case CIMA:
			proximoX--;
			break;
		case BAIXO:
			proximoX++;
			break;
		case DIREITA:
			proximoY++;
			break;
	}

	if(!canWalk(&m, HERO, proximoX, proximoY)) return;

	if(isCharacter(&m, PILULA, proximoX, proximoY)){
		pill = 1;

	}

	walking(&m, heroi.x, heroi.y, proximoX, proximoY);
	heroi.x = proximoX;
	heroi.y = proximoY;
}

int main(){

	leMapa(&m);
	encontraMapa(&m, &heroi, HERO);

	do {

		system("clear");
		printf("Pills: %d\n", pill);
		imprimeMapa(&m);
		char comando;
		scanf(" %c", &comando);
		move(comando);
		if(comando == BOMBA) explode();
		fantasmas();
	} while (!acabou());
	liberaMapa(&m);
}