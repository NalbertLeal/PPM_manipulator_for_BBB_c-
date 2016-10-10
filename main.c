#include <stdio.h>
#include "struct.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 \mainpage
 \author Nalbert Gabriel
 \date 24 de novembro de 2015
 \brief Esse programa tem como proposito editar uma imagem do formato PPM.
*/

/**
*   Esta e a funcao principal, main(), ela cria
* duas strings que va pegar o nome da imagem que
* o usuario deseja modificar e o nome do arquivo
* de saida. A fun��o lerPPM() e chamada e se nao
* existir nenhum erro main() imprime na tela um
* menu que ira disponibilizar ao usuario as funcoes
* que o programa pode fazer. Todas as vezes
* que o usuario pedir que o programa fa�a algo
* a fun��o lerPPM() ser� chamada novamente.
*/
int main() {

    /*
    *   A variavel nomeImg � um array tipo char (string) e ir�
    * armazenar o nome da imagem que sera manipulada. J� a variavel
    * novoNomeImg vai armazenar o nome da nova imagem quando
    * a imagem for salva.
    */
	char nomeImg[50], novoNomeImg[50];
	printf("Digite o nome do arquivo: (coloque a extencao .ppm do arquivo) \n"); //esse printf pede ao usuario que digite o nome do arquivo a ser manipulado
	scanf("%s", &nomeImg); //guarda na variavel nomeImg (que foi citada acima) o nome do arquivo que sera manipulado

    /*
    *   O if(lerPPM(nomeImg) == 1) serve para verificar
    * se ouve algum problema no precesso de leitura da imagem,
    * como por exemplo ela n�o ser do formato PPM.
    */
    if( lerPPM(nomeImg) == 1){
        return 0;
    }

	lerPPM(nomeImg); //chama a fun��o lerPPM(), que ira ler o arquivo passado para o programa

    /*
    *   O do{}while(novoNomeImg == NULL) serve para garantir
    * que a variavel novoNomeImg n�o ficar� sem valor.
    */
    do {
        printf("\nQual o nome do arquivo de saida: (coloque a extencao .ppm do arquivo) \n");
        scanf("%s", &novoNomeImg);
	} while(novoNomeImg == NULL);

    /*
    *   A fun��o escrevePPM() cria uma copia da imagem original,
    * assim a imagem original fica intocada.
    */
	escrevePPM(novoNomeImg);
    // Essas variaveis ser�o utilizadas para organizar o menu
    int acao, sair = 0, zm = 0;

    /*
    *   O while(sair != 1) � um loop que funciona enquanto
    * o usuario aperentemente quiser aplicar alguma fun��o
    * na imagem.
    */
    pid_t processId;
    while(sair != 1) {

        // Esse � o menu exibido ao usuario.
        printf("\nOque voce deseja fazer? \n");
        printf( "+---------------------------------+\n"
                "| (1)   binarizacao,               |\n"
                "| (2)   blur,                      |\n"
                "| (3)   shapering,                 |\n"
                "| (4)   bordas,                    |\n"
                "| (5)   tons de cinza,             |\n"
                "| (6)   negativo,                  |\n"
                "| (7)   zoom in,                   |\n"
                "| (8)   zoom out,                  |\n"
                "| (9)   rotacao anti-horario,      |\n"
                "| (10)  rotacao horaria,           |\n"
                "| (11)  sair e salvar              |\n"
                "+---------------------------------+\n");
        /* O proximo printf e scanf pergunta e pega o
        * numero correspondente a ac�o que o usuario
        * quer que o programa fa�a.
        */
        printf("Write one of the numbers above to do some thing: ");
        scanf("%i", &acao);
        printf("\n");
        /*
        *   O switch abaixo virifica oque o usuario
        * quer baseando-se no valor existente na
        * variavel acao.
        */
        switch(acao) {
            case 1: // No caso do usuario querer binarizar a imagem.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  binarizacao(novoNomeImg, 's');
                }
                else {  // parent process
                  int *status;
                  waitpid(processId, status, 0);
                  binarizacao(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 2: // No caso do usuario querer aplicar o blur na imagem.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  blur(novoNomeImg, 's');
                }
                else {  // parent process
                  int *status;
                  waitpid(processId, status, 0);
                  blur(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 3: // No caso do usuario querer aplicar um shaperring na imagem.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  shapering(novoNomeImg, 's');
                }
                else {  // parent process
                  int status;
                  waitpid(processId, &status, 0);
                  shapering(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 4: // No caso do usuario querer aplicas bordas na imagem.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  bordasImg(novoNomeImg, 's');
                }
                else {  // parent process
                  int status;
                  waitpid(processId, &status, 0);
                  bordasImg(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 5: // No caso do usuario querer deixar a imagem em tons de cinza.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  tonsDeCinza(novoNomeImg, 's');
                }
                else {  // parent process
                  int status;
                  waitpid(processId, &status, 0);
                  tonsDeCinza(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 6: // No caso do usuario querer deixar a imagem em negativo.
                lerPPM(novoNomeImg);
                processId = fork();
                if(processId == 0) {  // chield process
                  negativo(novoNomeImg, 's');
                }
                else {  // parent process
                  int status;
                  waitpid(processId, &status, 0);
                  negativo(novoNomeImg, 'f');
                }
                lerPPM(novoNomeImg);
                break;
            case 7: // No caso do usuario querer uma redu��o de duas vezes na imagem.
                zoomIn(novoNomeImg);
                lerPPM(novoNomeImg);
                break;
            case 8: // No caso do usuario querer uma amplia��o de duas vezes na imagem.
                zoomOut(novoNomeImg);
                lerPPM(novoNomeImg);
                break;
            case 9: // No caso do usuario querer uma rota��o de 90� no sentido anti-horio.
                rotacaoAntihorario(novoNomeImg);
                lerPPM(novoNomeImg);
                break;
            case 10: // No caso do usuario querer uma rota��o de 90� no sentido horario.
                rotacaoHorario(novoNomeImg);
                lerPPM(novoNomeImg);
                break;
            case 11: // Caso o usuario deseje sair do programa essa ser� o case usado.
                free(arrayFilho);
                free(nImg);
                free(imgP);
                return 0;
        }

    }

}
