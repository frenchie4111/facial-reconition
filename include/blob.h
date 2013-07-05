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

		Blob();

		void add_pixel( Pixel pixel );

		// MARK: Blob Static methods	
		static Blob find_blob( Pixel starting, cimg_library::CImg<unsigned char> *image, cimg_library::CImg<unsigned char> *visited, Pixel vcolor, int threshhold );
		static std::vector<Blob> find_all_blobs( cimg_library::CImg<unsigned char>image, int threshhold );

		static std::vector<Pixel> find_neighbors( Pixel p, cimg_library::CImg<unsigned char> *image );
		static bool is_visited( Pixel p, cimg_library::CImg<unsigned char> *visited);
};

#endif
