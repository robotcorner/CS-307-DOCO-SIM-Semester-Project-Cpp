
#pragma once
#include <string>
#include "Doco.h"

class AbstractSimpleDocoFactory
{
public:
	virtual Doco* createDocoDefault(int x_pos, int y_pos, std::string direction) = 0;
	virtual Doco* createDocoDiagonal(int x_pos, int y_pos, std::string direction) = 0;
	virtual Doco* createDocoHorizontal(int x_pos, int y_pos, std::string direction) = 0;
	virtual Doco* createDocoVertical(int x_pos, int y_pos, std::string direction) = 0;
	virtual Doco* createDocoPerp(int x_pos, int y_pos, std::string direction) = 0;
};