#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h>
#define cimg_using_png
#include "CImg.h"

#include "blob.h"
#include "pixel.h"


using namespace cimg_library;
using namespace std;



int main( int argc, char **argv ) 
{
	CImg<unsigned char> image("7.jpg");

	std::vector<Blob> blobs = Blob::find_all_blobs( image, 10 );

	printf( "Number of blobs: %d\n", blobs.size() );

//	visited.save("out.bmp");

	CImgDisplay main_display(image, "Main Display");
//	CImgDisplay blob_display(visited, "Blob Display");
	while( !main_display.is_closed() ) ;
} // Main
