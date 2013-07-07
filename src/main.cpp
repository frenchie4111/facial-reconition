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
	char* image_name = "4.png";
	if( argc > 1 )
		image_name = argv[1];
	CImg<unsigned char> image(image_name);

	CImg<unsigned char> visited(image.width(), image.height(), 1, 3, 0);

	CImg<unsigned char> blobsImg(image.width(), image.height(), 1, 3, 0);

	Blob single_blob = Blob::find_blob( Pixel( 0, 0, &image ), &image, &visited, Pixel(1,1,1,1,1), 10 );

	std::vector<Blob> blobs = Blob::find_all_blobs( image, 13, 0, &visited );

	for( int i = 0; i < blobs.size(); i++ )
	{
		printf("blob# %d: skewed: %f\n", i, blobs[i].get_x_skewness());
		if( blobs[i].pixels.size() > 100 && blobs[i].get_x_skewness() < .3f )
		{
			blobs[i].ensquare( &visited );
			blobs[i].draw( &blobsImg );
		}
	}

	printf( "Number of blobs: %d\n", blobs.size() );

	visited.save("out.bmp");

	CImgDisplay blob_disp( blobsImg, "Blobs Display" );
	CImgDisplay vis_disp( visited, "Visited Display" );
	CImgDisplay main_display(image, "Main Display");
//	CImgDisplay blob_display(visited, "Blob Display");
	while( !main_display.is_closed() && !vis_disp.is_closed() && !blob_disp.is_closed() ) ;
} // Main