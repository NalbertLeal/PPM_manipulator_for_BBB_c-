#ifndef LERESCREVER_H
#define LERESCREVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "struct.h"

/**
*   A funcao zoomOut() recebe o nome da imagem que esta sofrendo
* as modificacoes. A funcao acessa essa imagem e a reescreve,
* comecando reescrevendo o cabecario, e depois lendo a matriz
* nImg e ampliando a imagem. Para facilitar o entendimento,
* a função faz 1 pixel ser copiado mais 3 vezes, dobrando
* o tamanho da imagem.
* @param img
* @return nao existe valor retornado
*/
int zoomOut(char img[50]) {
    FILE *arquivo;
    arquivo = fopen( img, "w");

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", 2 * lin, 2 * col);
    fprintf( arquivo,"255\n");

    int jaux = 0, iaux = 0, i, j, printer = 0, lz = 2 * lin, cz = 2 * col;
    for(i = 0; i < lz; i++){
        for(j = 0; j < cz; j++){
            iaux = i/2;
            jaux = j/2;
            fprintf( arquivo, "%i %i %i \n", nImg[iaux][jaux].red, nImg[iaux][jaux].green, nImg[iaux][jaux].blue);
        }
    }

    fclose(arquivo);
}


//! zoom in
/**
*   A função zoomIn() recebe o nome da imagem que esta sofrendo
* as modificacoes. A funcao acessa essa imagem e a reescreve,
* começando reescrevendo o cabecario, e depois lendo a matriz
* nImg e reduzindo a imagem. Para facilitar o entendimento,
* a função reduz reduz 4 pixels para 1.
* @param img
* @return nao existe valor retornado
*/
int zoomIn(char img[50]) {
    FILE *arquivo;
    arquivo = fopen( img, "w");

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin / 2, col / 2);
    fprintf( arquivo,"255\n");

    int jaux = 0, iaux = 0, i, j, printer = 0, lz = lin / 2, cz = col / 2;
    for(i = 0; i < lz; i++){
        for(j = 0; j < cz; j++){
            iaux = i*2;
            jaux = j*2;
            fprintf( arquivo, "%i %i %i \n", nImg[iaux][jaux].red, nImg[iaux][jaux].green, nImg[iaux][jaux].blue);
        }
    }

    fclose(arquivo);

}


/**
*   A funcao rotacaoAntihorario() recebe o nome da imagem
* que esta sofrendo as modificacoes. A funcao acessa essa
* imagem e a reescreve, começando reescrevendo o cabecario,
* apôs isso as variaveis contadoras são usadas da seguinte
* forma, para a linha usamos o contador  j , e onde o  j
* seria usado colocamos a expresao  lin-1-1 , apos alguns
* testes percebemos que [j][lin-i-1]  faria uma rotacao no
* sentido antihorario.
* @param img
* @return nao existe valor retornado
*/
int rotacaoAntihorario(char img[50]) {

    FILE *arquivo;
    arquivo = fopen( img, "w+");

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    int i, j;

    for(i = 0; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[j][lin-i-1].red, nImg[j][lin-i-1].green, nImg[j][lin-i-1].blue);
        }
    }
}

/**
*   A funcao rotacaoHorario() recebe o nome da imagem
* que esta sofrendo as modificacoes. A funcao acessa essa
* imagem e a reescreve, comecando reescrevendo o cabecario,
* com isso a logica utilijada e basicamente a logica inversa
* da funcao rotacaoAntihorario(). para a linha usamos
*  a expresao lin-j-1, e na posicao que deveria ser
* ocupada por  j  colocamos o contador i, desse jeito
* rotacionamos a imagem no sentido horario.
* @param img
* @return nao existe valor retornado
*/
int rotacaoHorario(char img[50]) {
    FILE *arquivo;
    arquivo = fopen( img, "w+");

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    int i, j;

    for(i = 0; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[lin - j -1][i].red, nImg[lin - j -1][i].green, nImg[lin - j -1][i].blue);
        }
    }
}

/**
*   Assim como quase todas as funcoes desse programa
* a função binarizacao() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel da imagem
* faz uma media entre s valores RGB, se a media
* resultar em um valor abaixo ou igual a de 127 o
* valor do red, green e do blue e colocar como zero,
* caso o valor seja superior a 127 o red, green e
* o blue recebe o valor 255, assim o pixel ficará sempre
* preto ou branco.
* @param img
* @return nao existe valor retornado
*/
int binarizacao(char img[50], char fatherOrSon) {
    if(fatherOrSon == 'f') {
      // father
      FILE *arquivo;
      arquivo = fopen(img, "r+"); //tenta abri o arquivo

      // fprintf( arquivo,"P3\n");
      // fprintf( arquivo,"%i %i\n", lin, col);
      // fprintf( arquivo,"255\n");

      int mediaP, i, j;

      char ehPPM[3];
      // O scanf() pega as informações do cabeçario da imagem
      fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
      int pixelTem[4];
      //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
      arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
      for( i = 0; i < lin/2; i++) {
          /*
          *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
          * então é necessario fazer uso mais uma vez da alocação dinamica.
          */
          arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
          for(j = 0; j < col; j++) {
              fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
              arrayFilho[i][j].red = pixelTem[0];
              arrayFilho[i][j].green = pixelTem[1];
              arrayFilho[i][j].blue = pixelTem[2];
          }
      }

      // for( i = 0; i < lin/2; i++) {
      //     for(j = 0; j < col; j++) {
      //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
      //     }
      // }

      // binarização

      for(i = lin/2+1; i < lin; i++) {
          for(j = 0; j < col; j++) {

              mediaP = (int)(nImg[i][j].red + nImg[i][j].green + nImg[i][j].blue)/3;

              if(mediaP <= 127) {
                  fprintf(arquivo, "0 0 0\n");
              }
              if(mediaP > 127) {
                  fprintf(arquivo, "255 255 255\n");
              }
          }
      }

      fclose(arquivo);

      return 0;
    }
    else {
      // son
      int mediaP, i, j;

      FILE *arquivo;
      arquivo = fopen( img, "w");

      fprintf( arquivo,"P3\n");
      fprintf( arquivo,"%i %i\n", lin, col);
      fprintf( arquivo,"255\n");

      for(i = 0; i < lin/2; i++) {
          for(j = 0; j < col; j++) {

              mediaP = (int)(nImg[i][j].red + nImg[i][j].green + nImg[i][j].blue)/3;

              if(mediaP <= 127) {
                  fprintf(arquivo, "0 0 0\n");
              }
              if(mediaP > 127) {
                  fprintf(arquivo, "255 255 255\n");
              }
          }
      }

      fclose(arquivo);

      kill(getpid(), SIGKILL);
    }
}

/**
*   A funcao negativo() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel, o valor
* do red, do green e do blue e subtraido de 255 obtendo
* o complemento do valor, esse complemento e o valor a
* ser colocado no lugar do RGB deixando a imagem com
* a aparencia de negativo.
* @param img
* @return nao existe valor retornado
*/
int negativo(char img[50], char fatherOrSon) {
    if(fatherOrSon == 'f') {
      // father
      FILE *arquivo;
      arquivo = fopen(img, "r+"); //tenta abri o arquivo

      // fprintf( arquivo,"P3\n");
      // fprintf( arquivo,"%i %i\n", lin, col);
      // fprintf( arquivo,"255\n");

      int mediaP, i, j;

      char ehPPM[3];
      // O scanf() pega as informações do cabeçario da imagem
      fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
      int pixelTem[4];
      //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
      arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
      for( i = 0; i < lin/2; i++) {
          /*
          *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
          * então é necessario fazer uso mais uma vez da alocação dinamica.
          */
          arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
          for(j = 0; j < col; j++) {
              fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
              arrayFilho[i][j].red = pixelTem[0];
              arrayFilho[i][j].green = pixelTem[1];
              arrayFilho[i][j].blue = pixelTem[2];
          }
      }

      // for( i = 0; i < lin/2; i++) {
      //     for(j = 0; j < col; j++) {
      //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
      //     }
      // }

      //nagativo

      for(i = (lin/2)+1; i < lin; i++) {
          for(j = 0; j < col; j++) {
              fprintf( arquivo, "%i %i %i\n", 255-nImg[i][j].red, 255-nImg[i][j].green, 255-nImg[i][j].blue);
          }
      }

      fclose(arquivo);

      return 0;
    }
    else {
      // son
      int i, j;

      FILE *arquivo;
      arquivo = fopen(img, "r+"); //tenta abri o arquivo

      fprintf( arquivo,"P3\n");
      fprintf( arquivo,"%i %i\n", lin, col);
      fprintf( arquivo,"255\n");

      for(i = 0; i < lin/2; i++) {
          for(j = 0; j < col; j++) {
              fprintf( arquivo, "%i %i %i\n", 255-nImg[i][j].red, 255-nImg[i][j].green, 255-nImg[i][j].blue);
          }
      }

      fclose(arquivo);

      kill(getpid(), SIGKILL);
    }
}

/**
*   A funcao blur() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel,o pixel
* acessado encontrasse na matriz imgP, o red, o green,
* e o blue sao adicionados ao valor de uma outra matriz
* denominada nImg. Apos a leitura a matriz nImg e impre-
* sa dentro do arquivo com a imagem modificada usando
* outra dupla de FOR.
* @param img
* @return nao existe valor retornado
*/
int blur(char img[50], char fatherOrSon) {

  if(fatherOrSon == 'f') {
    // father
    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    // fprintf( arquivo,"P3\n");
    // fprintf( arquivo,"%i %i\n", lin, col);
    // fprintf( arquivo,"255\n");

    int mediaP, i, j;

    char ehPPM[3];
    // O scanf() pega as informações do cabeçario da imagem
    fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
    int pixelTem[4];
    //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
    arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = 0; i < lin/2; i++) {
        /*
        *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
        * então é necessario fazer uso mais uma vez da alocação dinamica.
        */
        arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
            arrayFilho[i][j].red = pixelTem[0];
            arrayFilho[i][j].green = pixelTem[1];
            arrayFilho[i][j].blue = pixelTem[2];
        }
    }

    // for( i = 0; i < lin/2; i++) {
    //     for(j = 0; j < col; j++) {
    //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
    //     }
    // }

    //blur
    for(i = (lin/2)+1; i < lin - 1; i++) {
        for(j = 1; j < col - 1; j++) {

            nImg[i][j].red += (imgP[i-1][j-1].red);
            nImg[i][j].green += (imgP[i-1][j-1].green);
            nImg[i][j].blue += (imgP[i-1][j-1].blue);

            nImg[i][j].red += (imgP[i-1][j].red);
            nImg[i][j].green += (imgP[i-1][j].green);
            nImg[i][j].blue += (imgP[i-1][j].blue);

            nImg[i][j].red += (imgP[i-1][j+1].red);
            nImg[i][j].green += (imgP[i-1][j+1].green);
            nImg[i][j].blue += (imgP[i-1][j+1].blue);

            nImg[i][j].red += (imgP[i][j-1].red);
            nImg[i][j].green += (imgP[i][j-1].green);
            nImg[i][j].blue += (imgP[i][j-1].blue);

            nImg[i][j].red += (imgP[i][j].red);
            nImg[i][j].green += (imgP[i][j].green);
            nImg[i][j].blue += (imgP[i][j].blue);

            nImg[i][j].red += (imgP[i][j+1].red);
            nImg[i][j].green += (imgP[i][j+1].green);
            nImg[i][j].blue += (imgP[i][j+1].blue);

            nImg[i][j].red += (imgP[i+1][j-1].red);
            nImg[i][j].green += (imgP[i+1][j-1].green);
            nImg[i][j].blue += (imgP[i+1][j-1].blue);

            nImg[i][j].red += (imgP[i+1][j].red);
            nImg[i][j].green += (imgP[i+1][j].green);
            nImg[i][j].blue += (imgP[i+1][j].blue);

            nImg[i][j].red += (imgP[i+1][j+1].red);
            nImg[i][j].green += (imgP[i+1][j+1].green);
            nImg[i][j].blue += (imgP[i+1][j+1].blue);
        }
    }

    for(i = lin/2; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo,"%i %i %i \n", nImg[i][j].red * 1 / 9, nImg[i][j].green / 9, nImg[i][j].blue / 9);
        }
    }

    fclose(arquivo);

    return 0;
  }
  else {
    // son
    int i, j;

    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    for(i = 1; i < lin/2 - 1; i++) {
        for(j = 1; j < col - 1; j++) {

            nImg[i][j].red += (imgP[i-1][j-1].red);
            nImg[i][j].green += (imgP[i-1][j-1].green);
            nImg[i][j].blue += (imgP[i-1][j-1].blue);

            nImg[i][j].red += (imgP[i-1][j].red);
            nImg[i][j].green += (imgP[i-1][j].green);
            nImg[i][j].blue += (imgP[i-1][j].blue);

            nImg[i][j].red += (imgP[i-1][j+1].red);
            nImg[i][j].green += (imgP[i-1][j+1].green);
            nImg[i][j].blue += (imgP[i-1][j+1].blue);

            nImg[i][j].red += (imgP[i][j-1].red);
            nImg[i][j].green += (imgP[i][j-1].green);
            nImg[i][j].blue += (imgP[i][j-1].blue);

            nImg[i][j].red += (imgP[i][j].red);
            nImg[i][j].green += (imgP[i][j].green);
            nImg[i][j].blue += (imgP[i][j].blue);

            nImg[i][j].red += (imgP[i][j+1].red);
            nImg[i][j].green += (imgP[i][j+1].green);
            nImg[i][j].blue += (imgP[i][j+1].blue);

            nImg[i][j].red += (imgP[i+1][j-1].red);
            nImg[i][j].green += (imgP[i+1][j-1].green);
            nImg[i][j].blue += (imgP[i+1][j-1].blue);

            nImg[i][j].red += (imgP[i+1][j].red);
            nImg[i][j].green += (imgP[i+1][j].green);
            nImg[i][j].blue += (imgP[i+1][j].blue);

            nImg[i][j].red += (imgP[i+1][j+1].red);
            nImg[i][j].green += (imgP[i+1][j+1].green);
            nImg[i][j].blue += (imgP[i+1][j+1].blue);
        }
    }

    for(i = 0; i < lin/2; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo,"%i %i %i \n", nImg[i][j].red * 1 / 9, nImg[i][j].green / 9, nImg[i][j].blue / 9);
        }
    }

    fclose(arquivo);

    kill(getpid(), SIGKILL);
  }
}

/**
*   A funcao bordas() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel,o pixel
* acessado encontrasse na matriz imgP, o red, o green,
* e o blue multiplicados por valores predeterminados
* para cada pixel ao redor do pixel manipulado.
* Existe a chance de na multiplicação o valor do RGB
* ultrapase o 255 ou seja menor que 0, por isso foram
* criados seis  if  para assim caso o valor seja menor
* doque zero ele passe a ser zero, e se for um valor
* superior a 255 o valor seja colocado para 255. Os
* valores RGB sao adicionados ao valor de uma outra
* matriz denominada nImg. Apos a leitura a matriz
* nImg é impresa dentro do arquivo com a imagem modi-
* ficada usando outra dupla de FOR.
* @param img
* @return nao existe valor retornado
*/
int bordasImg(char img[50], char fatherOrSon) {

  if(fatherOrSon == 'f') {
    // father
    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    // fprintf( arquivo,"P3\n");
    // fprintf( arquivo,"%i %i\n", lin, col);
    // fprintf( arquivo,"255\n");

    int mediaP, i, j;

    char ehPPM[3];
    // O scanf() pega as informações do cabeçario da imagem
    fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
    int pixelTem[4];
    //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
    arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = lin/2; i < lin; i++) {
        /*
        *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
        * então é necessario fazer uso mais uma vez da alocação dinamica.
        */
        arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
            arrayFilho[i][j].red = pixelTem[0];
            arrayFilho[i][j].green = pixelTem[1];
            arrayFilho[i][j].blue = pixelTem[2];
        }
    }

    // for( i = 0; i < lin/2; i++) {
    //     for(j = 0; j < col; j++) {
    //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
    //     }
    // }

    //borders

    for( i = lin/2; i < lin; i++) {
        for(j = lin; j < col; j++) {
            nImg[i][j].red = 0;
            nImg[i][j].green = 0;
            nImg[i][j].blue = 0;
        }
    }

    for(i = (lin/2)+1; i < lin - 1; i++) {
        for(j = +1; j < col - 1; j++) {
            nImg[i][j].red += (imgP[i-1][j-1].red * -1);
            nImg[i][j].green += (imgP[i-1][j-1].green * -1);
            nImg[i][j].blue += (imgP[i-1][j-1].blue * -1);

            nImg[i][j].red += (imgP[i-1][j].red * -1);
            nImg[i][j].green += (imgP[i-1][j].green * -1);
            nImg[i][j].blue += (imgP[i-1][j].blue * -1);

            nImg[i][j].red += (imgP[i-1][j+1].red * -1);
            nImg[i][j].green += (imgP[i-1][j+1].green * -1);
            nImg[i][j].blue += (imgP[i-1][j+1].blue * -1);

            nImg[i][j].red += (imgP[i][j-1].red) * -1;
            nImg[i][j].green += (imgP[i][j-1].green * -1);
            nImg[i][j].blue += (imgP[i][j-1].blue * -1);

            nImg[i][j].red += (imgP[i][j].red * 8);
            nImg[i][j].green += (imgP[i][j].green * 8);
            nImg[i][j].blue += (imgP[i][j].blue * 8);

            nImg[i][j].red += (imgP[i][j+1].red * -1);
            nImg[i][j].green += (imgP[i][j+1].green * -1);
            nImg[i][j].blue += (imgP[i][j+1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j-1].red * -1);
            nImg[i][j].green += (imgP[i+1][j-1].green * -1);
            nImg[i][j].blue += (imgP[i+1][j-1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j].red * -1);
            nImg[i][j].green += (imgP[i+1][j].green * -1);
            nImg[i][j].blue += (imgP[i+1][j].blue * -1);

            nImg[i][j].red += (imgP[i+1][j+1].red * -1);
            nImg[i][j].green += (imgP[i+1][j+1].green * -1);
            nImg[i][j].blue += (imgP[i+1][j+1].blue * -1);

            if(nImg[i][j].red < 0){
                nImg[i][j].red = 0;
            }

            if(nImg[i][j].green < 0){
                nImg[i][j].green = 0;
            }

            if(nImg[i][j].blue < 0){
                nImg[i][j].blue = 0;
            }

            if(nImg[i][j].red > 255){
                nImg[i][j].red = 255;
            }

            if(nImg[i][j].green > 255){
                nImg[i][j].green = 255;
            }

            if(nImg[i][j].blue > 255){
                nImg[i][j].blue = 255;
            }

        }
    }

    for(i = lin/2; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[i][j].red, nImg[i][j].green, nImg[i][j].blue);
        }
    }

    fclose(arquivo);

    return 0;
  }
  else {
    // son
    int i, j;

    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    for( i = 0; i < lin/2; i++) {
        for(j = 0; j < col; j++) {
            nImg[i][j].red = 0;
            nImg[i][j].green = 0;
            nImg[i][j].blue = 0;
        }
    }

    for(i = 1; i < lin/2 - 1; i++) {
        for(j = 1; j < col - 1; j++) {
            nImg[i][j].red += (imgP[i-1][j-1].red * -1);
            nImg[i][j].green += (imgP[i-1][j-1].green * -1);
            nImg[i][j].blue += (imgP[i-1][j-1].blue * -1);

            nImg[i][j].red += (imgP[i-1][j].red * -1);
            nImg[i][j].green += (imgP[i-1][j].green * -1);
            nImg[i][j].blue += (imgP[i-1][j].blue * -1);

            nImg[i][j].red += (imgP[i-1][j+1].red * -1);
            nImg[i][j].green += (imgP[i-1][j+1].green * -1);
            nImg[i][j].blue += (imgP[i-1][j+1].blue * -1);

            nImg[i][j].red += (imgP[i][j-1].red) * -1;
            nImg[i][j].green += (imgP[i][j-1].green * -1);
            nImg[i][j].blue += (imgP[i][j-1].blue * -1);

            nImg[i][j].red += (imgP[i][j].red * 8);
            nImg[i][j].green += (imgP[i][j].green * 8);
            nImg[i][j].blue += (imgP[i][j].blue * 8);

            nImg[i][j].red += (imgP[i][j+1].red * -1);
            nImg[i][j].green += (imgP[i][j+1].green * -1);
            nImg[i][j].blue += (imgP[i][j+1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j-1].red * -1);
            nImg[i][j].green += (imgP[i+1][j-1].green * -1);
            nImg[i][j].blue += (imgP[i+1][j-1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j].red * -1);
            nImg[i][j].green += (imgP[i+1][j].green * -1);
            nImg[i][j].blue += (imgP[i+1][j].blue * -1);

            nImg[i][j].red += (imgP[i+1][j+1].red * -1);
            nImg[i][j].green += (imgP[i+1][j+1].green * -1);
            nImg[i][j].blue += (imgP[i+1][j+1].blue * -1);

            if(nImg[i][j].red < 0){
                nImg[i][j].red = 0;
            }

            if(nImg[i][j].green < 0){
                nImg[i][j].green = 0;
            }

            if(nImg[i][j].blue < 0){
                nImg[i][j].blue = 0;
            }

            if(nImg[i][j].red > 255){
                nImg[i][j].red = 255;
            }

            if(nImg[i][j].green > 255){
                nImg[i][j].green = 255;
            }

            if(nImg[i][j].blue > 255){
                nImg[i][j].blue = 255;
            }

        }
    }

    for(i = 0; i < lin/2; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[i][j].red, nImg[i][j].green, nImg[i][j].blue);
        }
    }

    fclose(arquivo);

    kill(getpid(), SIGKILL);
  }
}

/**
*   A funcao shapering() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel,o pixel
* acessado encontrasse na matriz imgP, o red, o green,
* e o blue multiplicados por valores predeterminados
* para cada pixel ao redor do pixel manipulado.
* Existe a chance de na multiplicacao o valor do RGB
* ultrapase o 255 ou seja menor que 0, por isso foram
* criados seis  if  para assim caso o valor seja menor
* doque zero ele passe a ser zero, e se for um valor
* superior a 255 o valor seja colocado para 255. Os
* valores RGB são adicionados ao valor de uma outra
* matriz denominada nImg. Apos a leitura a matriz
* nImg e impresa dentro do arquivo com a imagem modi-
* ficada usando outra dupla de FOR.
* @param img
* @return nao existe valor retornado
*/
int shapering(char img[50], char fatherOrSon) {

  if(fatherOrSon == 'f') {
    // father
    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    // fprintf( arquivo,"P3\n");
    // fprintf( arquivo,"%i %i\n", lin, col);
    // fprintf( arquivo,"255\n");

    int mediaP, i, j;

    char ehPPM[3];
    // O scanf() pega as informações do cabeçario da imagem
    fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
    int pixelTem[4];
    //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
    arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = 0; i < lin/2; i++) {
        /*
        *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
        * então é necessario fazer uso mais uma vez da alocação dinamica.
        */
        arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
            arrayFilho[i][j].red = pixelTem[0];
            arrayFilho[i][j].green = pixelTem[1];
            arrayFilho[i][j].blue = pixelTem[2];
        }
    }

    // for( i = 0; i < lin/2; i++) {
    //     for(j = 0; j < col; j++) {
    //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
    //     }
    // }

    //sharpering

    for( i = lin/2; i < lin; i++) {
        for(j = 0; j < col; j++) {
            nImg[i][j].red = 0;
            nImg[i][j].green = 0;
            nImg[i][j].blue = 0;
        }
    }

    for(i = (lin/2)+1; i < lin - 1; i++) {
        for(j = 1; j < col - 1; j++) {
            nImg[i][j].red += (imgP[i-1][j-1].red * 0);
            nImg[i][j].green += (imgP[i-1][j-1].green * 0);
            nImg[i][j].blue += (imgP[i-1][j-1].blue * 0);

            nImg[i][j].red += (imgP[i-1][j].red * -1);
            nImg[i][j].green += (imgP[i-1][j].green * -1);
            nImg[i][j].blue += (imgP[i-1][j].blue * -1);

            nImg[i][j].red += (imgP[i-1][j+1].red * 0);
            nImg[i][j].green += (imgP[i-1][j+1].green * 0);
            nImg[i][j].blue += (imgP[i-1][j+1].blue * 0);

            nImg[i][j].red += (imgP[i][j-1].red) * -1;
            nImg[i][j].green += (imgP[i][j-1].green * -1);
            nImg[i][j].blue += (imgP[i][j-1].blue * -1);

            nImg[i][j].red += (imgP[i][j].red * 5);
            nImg[i][j].green += (imgP[i][j].green * 5);
            nImg[i][j].blue += (imgP[i][j].blue * 5);

            nImg[i][j].red += (imgP[i][j+1].red * -1);
            nImg[i][j].green += (imgP[i][j+1].green * -1);
            nImg[i][j].blue += (imgP[i][j+1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j-1].red * 0);
            nImg[i][j].green += (imgP[i+1][j-1].green * 0);
            nImg[i][j].blue += (imgP[i+1][j-1].blue * 0);

            nImg[i][j].red += (imgP[i+1][j].red * -1);
            nImg[i][j].green += (imgP[i+1][j].green * -1);
            nImg[i][j].blue += (imgP[i+1][j].blue * -1);

            nImg[i][j].red += (imgP[i+1][j+1].red * 0);
            nImg[i][j].green += (imgP[i+1][j+1].green * 0);
            nImg[i][j].blue += (imgP[i+1][j+1].blue * 0);

            if(nImg[i][j].red < 0){
                nImg[i][j].red = 0;
            }

            if(nImg[i][j].green < 0){
                nImg[i][j].green = 0;
            }

            if(nImg[i][j].blue < 0){
                nImg[i][j].blue = 0;
            }

            if(nImg[i][j].red > 255){
                nImg[i][j].red = 255;
            }

            if(nImg[i][j].green > 255){
                nImg[i][j].green = 255;
            }

            if(nImg[i][j].blue > 255){
                nImg[i][j].blue = 255;
            }

        }
    }

    for(i = lin/2; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[i][j].red, nImg[i][j].green, nImg[i][j].blue);
        }
    }

    fclose(arquivo);

    return 0;
  }
  else {
    // son
    int i, j;

    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    for( i = 0; i < lin/2; i++) {
        for(j = 0; j < col; j++) {
            nImg[i][j].red = 0;
            nImg[i][j].green = 0;
            nImg[i][j].blue = 0;
        }
    }

    for(i = 1; i < lin/2 - 1; i++) {
        for(j = 1; j < col - 1; j++) {
            nImg[i][j].red += (imgP[i-1][j-1].red * 0);
            nImg[i][j].green += (imgP[i-1][j-1].green * 0);
            nImg[i][j].blue += (imgP[i-1][j-1].blue * 0);

            nImg[i][j].red += (imgP[i-1][j].red * -1);
            nImg[i][j].green += (imgP[i-1][j].green * -1);
            nImg[i][j].blue += (imgP[i-1][j].blue * -1);

            nImg[i][j].red += (imgP[i-1][j+1].red * 0);
            nImg[i][j].green += (imgP[i-1][j+1].green * 0);
            nImg[i][j].blue += (imgP[i-1][j+1].blue * 0);

            nImg[i][j].red += (imgP[i][j-1].red) * -1;
            nImg[i][j].green += (imgP[i][j-1].green * -1);
            nImg[i][j].blue += (imgP[i][j-1].blue * -1);

            nImg[i][j].red += (imgP[i][j].red * 5);
            nImg[i][j].green += (imgP[i][j].green * 5);
            nImg[i][j].blue += (imgP[i][j].blue * 5);

            nImg[i][j].red += (imgP[i][j+1].red * -1);
            nImg[i][j].green += (imgP[i][j+1].green * -1);
            nImg[i][j].blue += (imgP[i][j+1].blue * -1);

            nImg[i][j].red += (imgP[i+1][j-1].red * 0);
            nImg[i][j].green += (imgP[i+1][j-1].green * 0);
            nImg[i][j].blue += (imgP[i+1][j-1].blue * 0);

            nImg[i][j].red += (imgP[i+1][j].red * -1);
            nImg[i][j].green += (imgP[i+1][j].green * -1);
            nImg[i][j].blue += (imgP[i+1][j].blue * -1);

            nImg[i][j].red += (imgP[i+1][j+1].red * 0);
            nImg[i][j].green += (imgP[i+1][j+1].green * 0);
            nImg[i][j].blue += (imgP[i+1][j+1].blue * 0);

            if(nImg[i][j].red < 0){
                nImg[i][j].red = 0;
            }

            if(nImg[i][j].green < 0){
                nImg[i][j].green = 0;
            }

            if(nImg[i][j].blue < 0){
                nImg[i][j].blue = 0;
            }

            if(nImg[i][j].red > 255){
                nImg[i][j].red = 255;
            }

            if(nImg[i][j].green > 255){
                nImg[i][j].green = 255;
            }

            if(nImg[i][j].blue > 255){
                nImg[i][j].blue = 255;
            }

        }
    }

    for(i = 0; i < lin/2; i++) {
        for(j = 0; j < col; j++) {
            fprintf( arquivo, "%i %i %i \n", nImg[i][j].red, nImg[i][j].green, nImg[i][j].blue);
        }
    }

    fclose(arquivo);

    kill(getpid(), SIGKILL);
  }
}

/**
*   A funcao tonsDeCinza() recebe como paramentro o nome
* da imagem que esta sendo manipulada, escreve o cabecario
* e com dois loops FOR acessa cada pixel tira
* uma media entre os valores do RGB, esse valor e colo-
* cado no lugar dos valores exisentes anteriormente,
* pois no RGB o cinza ocorre quando o valor do RGB e
* igual, assim uma media entre os tres iguala os valores.
* @param img
* @return nao existe valor retornado
*/
int tonsDeCinza(char img[50], char fatherOrSon) {

  if(fatherOrSon == 'f') {
    // father
    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    // fprintf( arquivo,"P3\n");
    // fprintf( arquivo,"%i %i\n", lin, col);
    // fprintf( arquivo,"255\n");

    int mediaP, i, e, j;

    char ehPPM[3];
    // O scanf() pega as informações do cabeçario da imagem
    fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);
    int pixelTem[4];
    //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
    arrayFilho = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = 0; i < lin/2; i++) {
        /*
        *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
        * então é necessario fazer uso mais uma vez da alocação dinamica.
        */
        arrayFilho[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
            arrayFilho[i][j].red = pixelTem[0];
            arrayFilho[i][j].green = pixelTem[1];
            arrayFilho[i][j].blue = pixelTem[2];
        }
    }

    // for( i = 0; i < lin/2; i++) {
    //     for(j = 0; j < col; j++) {
    //         fprintf( arquivo, "%i %i %i", arrayFilho[i][j].red, arrayFilho[i][j].green, arrayFilho[i][j].blue);
    //     }
    // }

    //tons de cinza

    for(i = lin/2; i < lin; i++) {
        for(e = 0; e < col; e++) {

            mediaP = (int)(imgP[i][e].red + imgP[i][e].green + imgP[i][e].blue)/3;

                fprintf(arquivo, "%i %i %i \n", mediaP, mediaP, mediaP);
        }
    }

    fclose(arquivo);

    return 0;
  }
  else {
    // son
    int i, j, mediaP, e;

    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    fprintf( arquivo,"P3\n");
    fprintf( arquivo,"%i %i\n", lin, col);
    fprintf( arquivo,"255\n");

    for(i = 0; i < lin/2; i++) {
        for(e = 0; e < col; e++) {

            mediaP = (int)(imgP[i][e].red + imgP[i][e].green + imgP[i][e].blue)/3;

                fprintf(arquivo, "%i %i %i \n", mediaP, mediaP, mediaP);
        }
    }

    fclose(arquivo);

    kill(getpid(), SIGKILL);
  }
}

#endif
