#ifndef BLOB_H
#define BLOB_H

#include "CImg.h"
#include "pixel.h"
#include <vector>
#include <deque>

class Blob
{
	public:
		std::vector< Pixel > pixels;
		int xlb, xub, ylb, yub;
		float xaverage, yaverage;
		int count;

		Blob();

		void add_pixel( Pixel pixel );

		// MARK: Blob finding functions	
		static Blob find_blob( Pixel starting, cimg_library::CImg<unsigned char> *image, cimg_library::CImg<unsigned char> *visited, Pixel vcolor, int threshhold );
		static std::vector<Blob> find_all_blobs( cimg_library::CImg<unsigned char>image, int threshhold, int size_threshhold, cimg_library::CImg<unsigned char> *visited );
		static std::vector<Pixel> find_neighbors( Pixel p, cimg_library::CImg<unsigned char> *image );
		static bool is_visited( Pixel p, cimg_library::CImg<unsigned char> *visited);

		// MARK: Blob drawing functions
		void ensquare( cimg_library::CImg<unsigned char> *image );
		void draw( cimg_library::CImg<unsigned char> *image );

		// MARK: Blob math code
		float get_x_skewness();
		float get_y_skewness();
};

#endif
