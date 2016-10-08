#ifndef classImageManipulator_H
#define classImageManipulator_H

#include <string>
#include <vector>

class ImageManipulator {
  public:
    ImageManipulator();

    void imageReader(std::string);
    void imageWriter(std::string);
    void zoomIn(int);
    void zoomOut(int);                    //
    void applyFilter(std::string);        // apply any filter to the image, receive the name of the filter that going to apply
    void applyFilterNegative(void);       // apply the negative filter on the image
    void run(int, const char *); // the program star to run when call this method
  private:
    int linesNumber;                      // variable that store the number of lines (heigth) of a image
    int colunmNumber;                     // variable that store the number of columns (weigth) of a image
    int maxPixelValue;
    Vector<Vector<PixelBase>> imageOriginal;  // store each line of pixel info of the image in a index of a vector
    Vector<Vector<PixelBase>> imageMod;  // store each line of pixel info of the modified image in a index of a vector

    // this is the base to store information of a pixel RGB
    typedef struct{
      int red,
      int green,
      int blue
    } PixelBase;

    // this store the pixel RGB data and the position XY of the pixel
    typedef struct {
    	int x, y;  // position of the pixel on the image
    	Pixel *image; // pixel data
    } PixelComplete;
};

#endif classImageManipulator_H
