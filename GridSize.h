// Stephen Stammen - 9/25/2020
#pragma once
class GridSize
{
private:
	int height;
	int width;
public:
	GridSize(int w, int h);
	~GridSize();
	int getHeight(void);
	int getWidth(void);
	void setHeight(int);
	void setWidth(int);
};

