#include "pixel.h"

using namespace cimg_library;

Pixel::Pixel()
{
	x = 0;
	y = 0;
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel( int nx, int ny, int nr, int ng, int nb )
{
	x = nx;
	y = ny;
	r = nr;
	g = ng;
	b = nb;
}

Pixel::Pixel( int nx, int ny, CImg<unsigned char> *image )
{
	x = nx;
	y = ny;
	r = image->operator()( nx, ny, 0, 0 );
	g = image->operator()( nx, ny, 0, 1 );
	b = image->operator()( nx, ny, 0, 2 );
}

int Pixel::difference_from( Pixel other )
{
	int difference = 0;
	difference += abs( r - other.r );
	difference += abs( b - other.b );
	difference += abs( g - other.g );
	return difference;
}

void Pixel::print()
{
	printf( "[(%d, %d) R%d G%d B%d]", x, y, r, g, b );
}