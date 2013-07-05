#include <iostream>
#include <vector>
#include <stdlib.h>

#include "CImg.h"

#define THRESHHOLD (10) // For now

typedef struct pixel {
	int x;
	int y;
	int r;
	int g;
	int b;
} pixel;

using namespace cimg_library;

pixel new_pixel( int nx, int ny, int nr, int ng, int nb )
{
	pixel new_pixel;
	new_pixel.x = nx;
	new_pixel.y = ny;
	new_pixel.r = nr;
	new_pixel.g = ng;
	new_pixel.b = nb;
	return new_pixel;
}

pixel new_pixel( int x, int y, CImg<unsigned char> image )
{
	return new_pixel( x, y, image(0,0,1,1), image(0,0,1,2), image(0,0,1,3) );
}

int color_difference( pixel p1, pixel p2 )
{
	int difference = 0;
	difference += abs( p1.r - p2.r );
	difference += abs( p1.b - p2.b );
	difference += abs( p1.g - p2.g );
	return difference;
}

std::vector<pixel> neighbors( pixel p, int height, int width )
{
	bool xlb = ( p.x > 0 );
	bool xub = ( p.x < width );
	bool ylb = ( p.y > 0 );
	bool yub = ( p.y < height ):

	std::vector< pixel > new_neighbors;

	if( xlb )
	{
		new_neighbors.push_back( new_pixel(
	}
}

void print_pixel( pixel p )
{
	printf( "[(%d, %d) R%d G%d B%d]", p.x, p.y, p.r, p.g, p.b );
}

void find_blob( pixel current, CImg<unsigned char> image, CImg<unsigned char> visited, std::vector<pixel> *blob )
{
}

int main( int argc, char **argv ) 
{
	CImg<unsigned char> image("1.png");

	CImg<unsigned char> visited(image.width(), image.height(), 1, 3, 0);

	std::vector< std::vector<pixel> > blobs;

	for( int x = 0; x < image.width(); x++ )
	{
		for( int y = 0; y < image.height(); y++ )
		{
			pixel starting_pixel = new_pixel( x, y, image(0,0,1,1), image(0,0,1,2), image(0,0,1,3) );

			if( visited( x, y, 1, 1 ) == 0 ) {
				std::vector<pixel> new_blob;
				new_blob.push_back( starting_pixel );

				find_blob( starting_pixel, image, visited, &new_blob );

				blobs.push_back( new_blob );
			}
		}
	}

	for( int b = 0; b < blobs.size(); b++ )
	{
		for( int p = 0; p < blobs[b].size(); p++ )
		{
			print_pixel( blobs[b][p] );
		}
		printf( "\n" );
	}

	CImgDisplay main_display(image, "Main Display");
	CImgDisplay blob_display(visited, "Blob Display");
	while( !main_display.is_closed() && !blob_display.is_closed() ) ;
} // Main
