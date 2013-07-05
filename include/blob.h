#ifndef BLOB_H
#define BLOB_H

#include <vector>

typedef struct pixel {
	int x;
	int y;
	int r;
	int g;
	int b;
} pixel;

class blob
{
	public:
		std::vector< pixel > pixels;
		int xlb, xub, ylb, yub;
};

#endif
