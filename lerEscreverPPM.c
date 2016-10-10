#ifndef LERESCREVER_H
#define LERESCREVER_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

/**
*   A função lerPPM() le a imagem que
* foi passada como parametro para essa
* função, caso ocorra algum erro no
* decorrer da função, lerPPM() retorna o
* valor 1. A imagem lida e gravada em uma
* matriz na qual foi utilizada alocação
* dinamica. Nessa funcao tambem existe
* uma copia da matriz que possui a imagem
* original. Essa copia sera utilizada para
* o funcionamento de algumas funções como
* o blur() e bordas().
* @param img
* @return nao existe valor retornado
*/

int lerPPM(char img[50]) {

    // variaveis que serão utilizadas em loop FOR ou na leitura da imagem
    int i, j, maximo;

    /*
    *   Nessas linhas a função lerPPM() tenta
    * abrir a imagem que teve seu nome passado
    * como parametro.
    */
    FILE *arquivo;
    arquivo = fopen(img, "r+"); //tenta abri o arquivo

    // O if if(!arquivo) verifica se a imagem exite.
    if(!arquivo){
        //se a imagem não existe a função imprime uma mensagem no console e retorna 1.
        printf("Desculpe, o arquivo nao pode ser aberto.");
        return 1;
    }

    // Se a imagem existir então um vetor é criado para armazenar a informação se a imagem é do formato PPM
    char ehPPM[3];

    // O scanf() pega as informações do cabeçario da imagem
    fscanf( arquivo,"%c %c %i %i %i", &ehPPM[0], &ehPPM[1], &lin, &col, &maximo);

    /*
    *   O if(ehPPM[0] != "P" && ehPPM[1] == "3") verifica
    * se a informação no vetor ehPPM[] confirma se a imagem
    * é do formato PPM.
    */
    if(ehPPM[0] != "P" && ehPPM[1] == "3") {
        /*
        *   Caso a imagem não seja do formato PPM
        * então o a função imprime uma mensagem na
        * tela e retorna 1.
        */
        printf("Desculpe, mas o arquivo nao é do formato PPM.");
        return 1;
    }

    /*
    *   Se não tiver ocorrido qualquer prolblema um vetor
    * chamado pixelTem[] é criado, ele vai armazenar o
    * pixel que será lido e irá ser usado para gravar
    * o valor RGB desse pixel na memoria do computador
    * fazendo uso da alocação dinamica.
    */
    int pixelTem[4];
    //  Com a função malloc() abrimos espaço na memoria para alocar os pixel
    imgP = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = 0; i < lin; i++) {
        /*
        *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
        * então é necessario fazer uso mais uma vez da alocação dinamica.
        */
        imgP[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            fscanf( arquivo, "%i %i %i", &pixelTem[0], &pixelTem[1], &pixelTem[2]);
            imgP[i][j].red = pixelTem[0];
            imgP[i][j].green = pixelTem[1];
            imgP[i][j].blue = pixelTem[2];
        }

    }
    /*
    *   Para usar as funções blur(), shaerring() e outras
    * foi necessario fazer uso de 2 matrizes do tipo Pixel
    * por isso foi criada uma 2ª matriz que a principio é
    * uma copia da primeira.
    */
    nImg = (Pixel**)malloc(lin * sizeof(Pixel*));
    for( i = 0; i < lin; i++) {

        nImg[i] = (Pixel*)malloc(col * sizeof(Pixel));
        for(j = 0; j < col; j++) {
            nImg[i][j].red = imgP[i][j].red;
            nImg[i][j].green = imgP[i][j].green;
            nImg[i][j].blue = imgP[i][j].blue;
        }
    }

    // Com o fim da função a função fclose() fecha o arquivo.
    fclose(arquivo);
}

/**
    \brief escreve a imagem de saida do programa com base na matriz imgP.
*   A função escrevePPM() usa a matriz imgP criada da
* função lerPPM() para criar uma imagem copia da original
*  Essa copia sofrera as modificações requeridas
* pelo usuario.
* @param img
* @return não existe valor retornado
*/
int escrevePPM(char img[50]) {

    // Variaveis i e j utilizadas no loop FOR.
    int i, j;

    /*
    *   Assim como a função lerPPM(), escrevePPM
    * também recebe o nome da fução como perametro
    * para poder criar a nova imagem que é uma copia
    * da original.
    */
    FILE *novoArquivo;
    novoArquivo = fopen( img, "w");

    // Os 3 fprintf() escreven o cabeçario da imagem.
    fprintf( novoArquivo,"P3\n");
    fprintf( novoArquivo,"%i %i\n", lin, col);
    fprintf( novoArquivo,"255\n");

    /*
    *   Os 2 FOR são utilizados para acessar cada um dos elementos
    * da matriz imgP que contém cada pixel en sua respectiva posi-
    * ção.
    */
    for(i = 0; i < lin; i++) {
        for(j = 0; j < col; j++) {
            /*
            *   Quando o pixel é acessado os seus valores RGB são escritos
            * no arquivo que é uma copia da imagem origianl.
            */
            fprintf(novoArquivo, "%i %i %i\n", imgP[i][j].red, imgP[i][j].green, imgP[i][j].blue);
        }
    }

    // Como a função escreverPPM() terminou a função fclose() fecha o arquivo.
    fclose(novoArquivo);
}

#endif
