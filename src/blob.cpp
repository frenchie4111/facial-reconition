#include "blob.h"

using namespace cimg_library;
using namespace std;

Blob::Blob()
{
	// Initialize bounds to maximum/minimum
	xub = 0;
	xlb = 32766;
	yub = 0;
	ylb = 32766;
}

void Blob::add_pixel( Pixel pixel )
{
	pixels.push_back(pixel);
	if( pixel.x > xub )
	{
		xub = pixel.x;
	}
	if( pixel.x < xlb )
	{
		xlb = pixel.x;
	}
	if ( pixel.y > yub )
	{
		yub = pixel.y;
	}
	if ( pixel.y < ylb )
	{
		ylb = pixel.y;
	}
}

Blob Blob::find_blob( Pixel starting, CImg<unsigned char> *image, CImg<unsigned char> *visited, Pixel vcolor, int threshhold )
{
	// Create a blob to return, and add the first one to it
	Blob blob;
	blob.add_pixel( starting );

	// Add our first pixel to the line
	deque<Pixel> queue;
	queue.push_back( starting );


	// While there is still things in line
	while( queue.size() > 0 )
	{
		// Get the next up
		Pixel current = queue.front(); 
		queue.pop_front();

		current.print();
		printf("\n");

		// Make sure we haven't already visited it
		// We do this here incase we somehow got to here
		// with a already visited pixel
		if ( !Blob::is_visited( current, visited ) )
		{
			// Add it to the visited bitmap
			visited->operator()( current.x, current.y, 0, 0 ) = vcolor.r;
			visited->operator()( current.x, current.y, 0, 1 ) = vcolor.g;
			visited->operator()( current.x, current.y, 0, 2 ) = vcolor.b;

			// Find it's neighbors
			vector<Pixel> neighbors = Blob::find_neighbors( current, image );

			// Loop through them
			for ( int i = 0; i < neighbors.size(); i++ )
			{
				// If we haven't visisted it
				if( !Blob::is_visited( neighbors[i], visited ) )
				{
					// Check if it's under our threshhold
					if( neighbors[i].difference_from( current ) <= threshhold )
					{
						// Add it to the queue
						queue.push_back( neighbors[i] );

						// Add it to the visisted bitmap
						blob.add_pixel( neighbors[i] );
					}
				}
			}
		}
	}
	return blob;
}

std::vector<Blob> Blob::find_all_blobs( CImg<unsigned char> image, int threshhold )
{
	// Create a visited bitmap, this will serve two purposes:
	// 		1 - Stop us from backtracking when finding blobs
	//		2 - Give us a visual representation of our blobs
	CImg<unsigned char> visited(image.width(), image.height(), 1, 3, 0);
	
	// Initialize our vector of blobs to eventually return
	std::vector< Blob > blobs;

	for( int x = 0; x < image.width(); x++ )
	{
		for( int y = 0; y < image.height(); y++ )
		{
			if( visited( x, y, 1, 1 ) == 0 ) {
				// Create a pixel for this location
				Pixel starting_pixel( x, y, &image );

				// Create a random color for our bitmap
				Pixel vcolor;
				vcolor.r = rand()%253 + 1;
				vcolor.g = rand()%253 + 1;
				vcolor.b = rand()%253 + 1;

				Blob new_blob = Blob::find_blob( starting_pixel, &image, &visited, vcolor, threshhold );

				blobs.push_back( new_blob );
			}
		}
	}

	visited.save("out.bmp");
	CImgDisplay vis_disp( visited, "Visited Display" );
	while( !vis_disp.is_closed() );
	return blobs;
}

std::vector<Pixel> Blob::find_neighbors( Pixel p, CImg<unsigned char> *image )
{
	std::vector< Pixel > new_neighbors;

	if( p.x >= 1 )
	{
		new_neighbors.push_back( Pixel( p.x-1, p.y, image ) );
	}
	if( p.x < ( image->width() - 1 ) )
	{
		new_neighbors.push_back( Pixel( p.x+1, p.y, image ) );
	}
	if( p.y >= 1 )
	{
		new_neighbors.push_back( Pixel( p.x, p.y-1, image ) );
	}
	if( p.y < ( image->height() - 1 ) )
	{
		new_neighbors.push_back( Pixel( p.x, p.y+1, image ) );
	}

	return new_neighbors;
}

bool Blob::is_visited( Pixel p, CImg<unsigned char> *visited )
{
	if( visited->operator()( p.x, p.y, 0, 1 ) != 0 )
	{
		return true;
	}
	printf("not visited: ");
	p.print();
	printf("\n");
	return false;
}