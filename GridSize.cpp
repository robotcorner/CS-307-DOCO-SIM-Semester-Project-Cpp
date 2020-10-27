// Stephen Stammen - 9/25/2020
#include "GridSize.h"

GridSize::GridSize() {
	this->height = 0;
	this->width = 0;
}

GridSize::GridSize(int w, int h) 
{
	this->height = h;
	this->width = w;
}

GridSize::~GridSize() 
{
	// nothing special to do. No pointers
}

int GridSize::getHeight(void)
{
	return this->height;
}

int GridSize::getWidth(void)
{
	return this->width;
}

void GridSize::setHeight(int h)
{
	this->height = h;
}

void GridSize::setWidth(int w)
{
	this->width = w;
}