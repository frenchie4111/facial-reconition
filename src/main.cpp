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

	CImg<unsigned char> visited(image.width(), image.height(), 1, 3, 0);

	std::vector<Blob> blobs = Blob::find_all_blobs( image, 15, &visited );

	for( int i = 0; i < blobs.size(); i++ )
	{
		if( blobs[i].pixels.size() > 200 )
		{
			blobs[i].ensquare( &visited );
		}
	}

	printf( "Number of blobs: %d\n", blobs.size() );

	visited.save("out.bmp");

	CImgDisplay vis_disp( visited, "Visited Display" );
	CImgDisplay main_display(image, "Main Display");
//	CImgDisplay blob_display(visited, "Blob Display");
	while( !main_display.is_closed() && !vis_disp.is_closed() ) ;
} // Main