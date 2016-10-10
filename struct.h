#ifndef __struct__
#define __struct__

/**
* Pixel é um struct que vai ser a base para
* cada pixel usado no programa.
*/
typedef struct {
	int red, green, blue;
} Pixel;

/**
* Imagem é um struct que que reuna as informações,
*o X e Y assim como o RGB de um pixel.
*/
typedef struct {
	int x, y;
	Pixel *image;
} Imagem;

/**
*   img e nImg são variaveis do tipo Pixel (são
* ponteiros de ponteiros) e mais para frente
* serão utilizadas na leitura da imagem
*/
Pixel** imgP;
Pixel** nImg;
Pixel** arrayFilho;
/**
* lin e col são variaveis globais que irão armazenar
*o quantidade de linhas e colunas da imagem.
*/
int lin, col;
int maximo;


#endif
