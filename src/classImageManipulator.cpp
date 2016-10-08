#ifndef classImaageManipulator_CPP
#define classImaageManipulator_CPP

#include <string>
#include <vector>
#include <stdio.h>

#include <sys/types.h>
#include <csignal>
#include <unistd.h>
#include <cstdlib>

ImageManipulator::ImageManipulator() {
  this->imageOriginal = new Vector(50);
  this->imageMod = new Vector(50);
  this->linesNumber = 0;
  this->colunmNumber = 0;
  this->maxPixelValue = 0;
}

void ImageManipulator::zoomOut() {

}

void ImageManipulator::zoomIn() {

}

void ImageManipulator::applyBlur() {

  for(int i = 0; i < this->linesNumber; i++) {
      for(int j = 0; j < this->colunmNumber; j++) {
          this->imageMod[i][j].red = 0;
          this->imageMod[i][j].green = 0;
          this->imageMod[i][j].blue = 0;
      }
  }

  for(int i = 1; i < this->linesNumber - 1; i++) {
      for(int j = 1; j < this->colunmNumber - 1; j++) {
          this->imageMod[i][j].red += (this->imageOriginal[i-1][j-1].red * 0);
          this->imageMod[i][j].green += (this->imageOriginal[i-1][j-1].green * 0);
          this->imageMod[i][j].blue += (this->imageOriginal[i-1][j-1].blue * 0);

          this->imageMod[i][j].red += (this->imageOriginal[i-1][j].red * -1);
          this->imageMod[i][j].green += (this->imageOriginal[i-1][j].green * -1);
          this->imageMod[i][j].blue += (this->imageOriginal[i-1][j].blue * -1);

          this->imageMod[i][j].red += (this->imageOriginal[i-1][j+1].red * 0);
          this->imageMod[i][j].green += (this->imageOriginal[i-1][j+1].green * 0);
          this->imageMod[i][j].blue += (this->imageOriginal[i-1][j+1].blue * 0);

          this->imageMod[i][j].red += (this->imageOriginal[i][j-1].red) * -1;
          this->imageMod[i][j].green += (this->imageOriginal[i][j-1].green * -1);
          this->imageMod[i][j].blue += (this->imageOriginal[i][j-1].blue * -1);

          this->imageMod[i][j].red += (this->imageOriginal[i][j].red * 5);
          this->imageMod[i][j].green += (this->imageOriginal[i][j].green * 5);
          this->imageMod[i][j].blue += (this->imageOriginal[i][j].blue * 5);

          this->imageMod[i][j].red += (this->imageOriginal[i][j+1].red * -1);
          this->imageMod[i][j].green += (this->imageOriginal[i][j+1].green * -1);
          this->imageMod[i][j].blue += (this->imageOriginal[i][j+1].blue * -1);

          this->imageMod[i][j].red += (this->imageOriginal[i+1][j-1].red * 0);
          this->imageMod[i][j].green += (this->imageOriginal[i+1][j-1].green * 0);
          this->imageMod[i][j].blue += (this->imageOriginal[i+1][j-1].blue * 0);

          this->imageMod[i][j].red += (this->imageOriginal[i+1][j].red * -1);
          this->imageMod[i][j].green += (this->imageOriginal[i+1][j].green * -1);
          this->imageMod[i][j].blue += (this->imageOriginal[i+1][j].blue * -1);

          this->imageMod[i][j].red += (this->imageOriginal[i+1][j+1].red * 0);
          this->imageMod[i][j].green += (this->imageOriginal[i+1][j+1].green * 0);
          this->imageMod[i][j].blue += (this->imageOriginal[i+1][j+1].blue * 0);

          if(this->imageMod[i][j].red < 0){
              this->imageMod[i][j].red = 0;
          }

          if(this->imageMod[i][j].green < 0){
              this->imageMod[i][j].green = 0;
          }

          if(this->imageMod[i][j].blue < 0){
              this->imageMod[i][j].blue = 0;
          }

          if(this->imageMod[i][j].red > this->maxPixelValue){
              this->imageMod[i][j].red = this->maxPixelValue;
          }

          if(this->imageMod[i][j].green > this->maxPixelValue){
              this->imageMod[i][j].green = this->maxPixelValue;
          }

          if(this->imageMod[i][j].blue > this->maxPixelValue){
              this->imageMod[i][j].blue = this->maxPixelValue;
          }

      }
  }
}

void ImageManipulator::applyBin() {

}

void ImageManipulator::applNagative() {

}

void ImageManipulator::applyBorder() {

}

void ImageManipulator::applySharpe() {

}

void ImageManipulator::applyGrey() {

}

void ImageManipulator::applyNegative() {

}

void ImageManipulator::imageReader(std::string fileName) {
  FILE *imageFile;
  imageFile = fopen(fileName, "r+");

  if(!arquivo){
        //se a imagem não existe a função imprime uma mensagem no console e retorna 1.
		printf("> Sorry, the file coundn't be opened");
		return 1;
	}

  char PPMHeader[3];
  fscanf( arquivo,"%c %i %i %i %i", &this->PPMHeader[0], &this->PPMHeader[1], &this->linesNumber, &this->colunmNumber, &this->maxPixelValue);

  if(ehPPM[0] != "P" && ehPPM[1] == "3") {
      /*
      *   Caso a imagem não seja do formato PPM
      * então o a função imprime uma mensagem na
      * tela e retorna 1.
      */
      printf("Desculpe, mas o arquivo nao é do formato PPM.");
      return 1;
  }

  int auxPixel[4];  // a temporary array of int that store the values of the pixel that is been read
  this->imageOriginal = new Vector<PixelBase>(this->linesNumber);
  for( i = 0; i < this->linesNumber; i++) {
      /*
      *   Como imgP é uma matriz (pois os pixels possuem coordenadas)
      * então é necessario fazer uso mais uma vez da alocação dinamica.
      */
      this->imageOriginal[i] = new Vector<PixelBase>(this->colunmNumber);
      for(j = 0; j < col; j++) {
          fscanf( arquivo, "%i %i %i", &auxPixel[0], &auxPixel[1], &auxPixel[2]);
          imageOriginal[i][j].red = auxPixel[0];
          imageOriginal[i][j].green = auxPixel[1];
          imageOriginal[i][j].blue = auxPixel[2];
      }
  }

  this->imageMod = new Vector<PixelBase>(this->linesNumber);
  for( i = 0; i < lin; i++) {

      this->imageMod[i] = new Vector<PixelBase>(this->colunmNumber);
      for(j = 0; j < col; j++) {
          this->imageMod[i][j].red = this->imageMod[i][j].red;
          this->imageMod[i][j].green = this->imageMod[i][j].green;
          this->imageMod[i][j].blue = this->imageMod[i][j].blue;
      }
  }

  fclose(imageFile);
}

void ImageManipulator::imageWriter(std::string fileName) {
  FILE *imageFile;
  imageFile = fopen( fileName, "w");

  // Os 3 fprintf() escreven o cabeçario da imagem.
  fprintf( novoArquivo,"P3\n");
  fprintf( novoArquivo,"%i %i\n", lin, col);
  fprintf( novoArquivo,"255\n");

  /*
  *   Os 2 FOR são utilizados para acessar cada um dos elementos
  * da matriz imgP que contém cada pixel en sua respectiva posi-
  * ção.
  */
  for(int i = 0; i < lin; i++) {
      for(int j = 0; j < col; j++) {
          /*
          *   Quando o pixel é acessado os seus valores RGB são escritos
          * no arquivo que é uma copia da imagem origianl.
          */
          fprintf(novoArquivo, "%i %i %i\n", imgP[i][j].red, imgP[i][j].green, imgP[i][j].blue);
      }
  }

  fclose(novoArquivo);
}

void ImageManipulator::run(int argc, const char *argv) {
  this->imageReader();
  pid_t processId;

  while(true) {
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

    printf("Digite o numero de um dos comandos acima: ");
    scanf("%i", &acao);
    printf("\n");

    // pid_t arrayOfProcessId[4];
    // int numberOfForks = 4;
    // for(int counter = 0; counter < numberOfForks; counter++) {
      processId = fork();
    //   arrayOfProcessId[i] = processId;
    // }

    if(processId == 0) {  // chield process
      this->imageWriter("image#2.ppm");
    }
    else {  // parent process
      this->imageWriter("image#1.ppm");
    }

    switch(acao) {
        case 1: // No caso do usuario querer binarizar a imagem.
            processId = fork();
            if(processId == 0) {  // chield process
              this->
              this->applyBin();
              this->imageWriter(this->fileOutName);
            }
            else {  // parent process
              int status;
              waitpid(processId, &status, 0);
              this->applyBin();
              this->imageWriter(this->fileOutName);
            }
            break;
        case 2: // No caso do usuario querer aplicar o blur na imagem.
            this->applyBlur(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 3: // No caso do usuario querer aplicar um shaperring na imagem.
            this->applySharpe(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 4: // No caso do usuario querer aplicas bordas na imagem.
            this->applyBorder(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 5: // No caso do usuario querer deixar a imagem em tons de cinza.
            this->applyGrey(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 6: // No caso do usuario querer deixar a imagem em negativo.
            this->applyNegative(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 7: // No caso do usuario querer uma redu��o de duas vezes na imagem.
            this->zoomIn(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 8: // No caso do usuario querer uma amplia��o de duas vezes na imagem.
            this->zoomOut(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 9: // No caso do usuario querer uma rota��o de 90� no sentido anti-horio.
            this->rotacaoAntihorario(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 10: // No caso do usuario querer uma rotacao de 90� no sentido horario.
            this->rotacaoHorario(novoNomeImg);
            lerPPM(novoNomeImg);
            break;
        case 11: // Caso o usuario deseje sair do programa essa sera o case usado.
            return 0;
            break;
    }
  }
}

#endif classImaageManipulator_CPP
