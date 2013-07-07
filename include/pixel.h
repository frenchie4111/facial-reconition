#ifndef PIXEL_H
#define PIXEL_H

#include "CImg.h"

class Pixel {
	public:
		int x;
		int y;
		int r;
		int g;
		int b;

		// MARK: Pixel Static methods

		// Initializers
		Pixel();
		Pixel( int nx, int ny, int nr, int ng, int nb );
		Pixel( int nx, int ny, cimg_library::CImg<unsigned char> *image);

		int difference_from( Pixel other );
		void print();
		void draw( cimg_library::CImg<unsigned char> *image );
};

#endif