#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h>
#define cimg_using_png
#include "CImg.h"

#define THRESHHOLD (20) // For now

typedef struct pixel {
	int x;
	int y;
	int r;
	int g;
	int b;
} pixel;

using namespace cimg_library;
using namespace std;

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

pixel new_pixel( int x, int y, CImg<unsigned char> *image )
{
	return new_pixel( x, y, image->operator()(x,y,0,0), image->operator()(x,y,0,1), image->operator()(x,y,0,2) );
}

int color_difference( pixel p1, pixel p2 )
{
	int difference = 0;
	difference += abs( p1.r - p2.r );
	difference += abs( p1.b - p2.b );
	difference += abs( p1.g - p2.g );
	return difference;
}

std::vector<pixel> find_neighbors( pixel p, CImg<unsigned char> *image )
{
	bool xlb = ( p.x >= 1 );
	bool xub = ( p.x < ( image->width() - 1 ) );
	bool ylb = ( p.y >= 1 );
	bool yub = ( p.y < ( image->height() - 1 ) );

	std::vector< pixel > new_neighbors;

	if( xlb )
	{
		new_neighbors.push_back( new_pixel( p.x-1, p.y, image ) );
	}
	if( xub )
	{
		new_neighbors.push_back( new_pixel( p.x+1, p.y, image ) );
	}
	if( ylb )
	{
		new_neighbors.push_back( new_pixel( p.x, p.y-1, image ) );
	}
	if( yub )
	{
		new_neighbors.push_back( new_pixel( p.x, p.y+1, image ) );
	}

	return new_neighbors;
}

void print_pixel( pixel p )
{
	printf( "[(%d, %d) R%d G%d B%d]", p.x, p.y, p.r, p.g, p.b );
}

bool is_visited( pixel p, CImg<unsigned char> *visited )
{
	if( visited->operator()( p.x, p.y, 0, 1 ) == 255 )
	{
		return true;
	}
	return false;
}

vector<pixel> find_blob( pixel starting, CImg<unsigned char> *image, CImg<unsigned char> *visited, pixel vcolor )
{
	// Create a blob to return, and add the first one to it
	vector<pixel> blob;
	blob.push_back( starting );

	// Add our first pixel to the line
	deque<pixel> queue;
	queue.push_back( starting );


	// While there is still things in line
	while( queue.size() > 0 )
	{
		// Get the next up
		pixel current = queue.front(); 
		queue.pop_front();

		// Make sure we haven't already visited it
		if ( !is_visited( current, visited ) )
		{
			// Add it to the visited list
			visited->operator()( current.x, current.y, 0, 0 ) = vcolor.r;
			visited->operator()( current.x, current.y, 0, 1 ) = vcolor.g;
			visited->operator()( current.x, current.y, 0, 2 ) = vcolor.b;

			// Find it's neighbors
			vector<pixel> neighbors = find_neighbors( current, image );
			// Loop through them
			for ( int i = 0; i < neighbors.size(); i++ )
			{
				// If we haven't visisted it
				if( !is_visited( neighbors[i], visited ) )
				{
					// Check if it's under our threshhold
					if( color_difference( current, neighbors[i] ) <= THRESHHOLD )
					{
						// Add it to the queue
						queue.push_back( neighbors[i] );
						// Add it to the visisted bitmap
						blob.push_back( neighbors[i] );
					}
				}
			}
		}
	}
	return blob;
}

int main( int argc, char **argv ) 
{
	CImg<unsigned char> image("2.jpg");

	CImg<unsigned char> visited(image.width(), image.height(), 1, 3, 0);
	
	int tx = 19, ty = 19;

	printf( "%d, %d, %d \n", image( tx, ty, 0, 0 ), image( tx, ty, 0, 1 ), image( tx, ty, 0, 2) );

	std::vector< std::vector<pixel> > blobs;

	for( int x = 0; x < image.width(); x++ )
	{
		for( int y = 0; y < image.height(); y++ )
		{
			if( visited( x, y, 1, 1 ) == 0 ) {
				// Create a pixel for this location
				pixel starting_pixel = new_pixel( x, y, &image );

				// Create a random color for our bitmap (TESTING)
				pixel vcolor;
				vcolor.r = rand()%255;
				vcolor.g = 255;
				vcolor.b = rand()%255;
// vector<pixel> find_blob( pixel starting, CImg<unsigned char> *image, CImg<unsigned char> *visisted, pixel vcolor )

				vector<pixel> new_blob = find_blob( starting_pixel, &image, &visited, vcolor );

				blobs.push_back( new_blob );
			}
		}
	}
#if 0
	for( int b = 0; b < blobs.size(); b++ )
	{
		for( int p = 0; p < blobs[b].size(); p++ )
		{
			print_pixel( blobs[b][p] );
		}
		printf( "\n" );
	}
	printf( "Number of blobs: %d\n", blobs.size() );
#endif
	visited.save("out.bmp");

	CImgDisplay main_display(image, "Main Display");
	CImgDisplay blob_display(visited, "Blob Display");
	while( !main_display.is_closed() && !blob_display.is_closed() ) ;
} // Main
