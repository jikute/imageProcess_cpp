#pragma once
#include<vector>

using namespace std;

class Image
{
private:
	vector<vector<int>> pixels;
	Image(int row, int column);
	~Image();
	// read image from file
	void readImage(const char* infile);
	// write image to a file
	void writeImage(const char* outfile);
	// interpolate an image
	void interpolate(Image* image, const char* way);
};