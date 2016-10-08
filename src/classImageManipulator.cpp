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

void ImageManipulator::applyFilterNegative() {

}

void ImageManipulator::applyFilter() {

}

void ImageManipulator::zoomOut() {

}

void ImageManipulator::zoomIn() {

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

  // int numberOfForks = 4;
  // for(int counter = 0; counter < numberOfForks; counter++) {
    processId = fork();
  // }

  if(processId == 0) {  // chield process
    this->imageWriter("image#2.ppm");
  }
  else {  // parent process
    this->imageWriter("image#1.ppm");
  }
}

#endif classImaageManipulator_CPP
