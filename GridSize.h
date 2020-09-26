// Stephen Stammen - 9/25/2020
// GridSize contains your grid shape info.
#pragma once
class GridSize
{
private:
	int height;
	int width;
public:
	GridSize();
	GridSize(int w, int h);
	~GridSize();
	int getHeight(void);
	int getWidth(void);
	void setHeight(int);
	void setWidth(int);
};

