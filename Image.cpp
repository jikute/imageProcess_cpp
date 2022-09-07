#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Image.h"

// construct function of class Image

Image::Image(int row, int column)
{
	row = row;
	column = column;
	pixels.resize(row);
	for (int i = 0; i < row; i++)
	{
		pixels[i].resize(column);
	}
}

// desctructor of class Image
Image::~Image()
{
	
}

// read image from a input file
void Image::readImage(const char* infile)
{
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, infile, "rb");
	if (error != 0)
	{
		printf("Cannot open infile\n");
		exit(1);
	}
	for (int x = 0; x < row; x++)
		if (fread(pixels[x]., 1, column, fp) != column)
		{
			fprintf(stderr, "error: couldn't read enough stuff\n");
			exit(1);
		}
	fclose(fp);
	printf("read input file sucess\n");
}

// write image to a file
void Image::writeImage(const char* outfile)
{
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, outfile, "wb");
	if (error != 0)
	{
		printf("Cannot open outfile\n");
		exit(1);
	}
	for (int x = 0; x < this->row; x++)
		fwrite(this->content[x], 1, this->column, fp);
	fclose(fp);
	printf("write sucess\n");
}

// interpolate an image
void Image::interpolate(Image* image, const char* way)
{
	double rm = ((double)image->row - 1) / ((double)(this->row) - 1);
	double cm = ((double)image->column - 1) / ((double)(this->column) - 1);
	if (strcmp(way, "nearestNeighbor") == 0)
	{
		// nearest neighbor interpolation
		for (int x = 0; x < image->row; x++)
		{
			for (int y = 0; y < image->column; y++)
			{
				if (x / rm - (int)(x / rm) <= 0.5)
				{
					if (y / cm - (int)(y / cm) <= 0.5)
					{
						image->content[x][y] = this->content[(int)(x / rm)][(int)(y / cm)];
					}
					else
					{
						image->content[x][y] = this->content[(int)(x / rm)][(int)(y / cm) + 1];
					}
				}
				else
				{
					if (y / cm - (int)(y / cm) <= 0.5)
					{
						image->content[x][y] = this->content[(int)(x / rm) + 1][(int)(y / cm)];
					}
					else
					{
						image->content[x][y] = this->content[(int)(x / rm) + 1][(int)(y / cm) + 1];
					}
				}
			}
		}
		printf("interpolate by nearest neighbor success\n");
	}
	else
	{
		printf("parameter is wrong\n");
	}
}

// fourier transform of an image
