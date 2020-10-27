
#pragma once
#include <string>
#include "Doco.h"

class AbstractSimpleDocoFactory
{
public:
	virtual Doco* createDocoDefault(int x_pos, int y_pos, std::string direction);
	virtual Doco* createDocoDiagonal(int x_pos, int y_pos, std::string direction);
	virtual Doco* createDocoHoriziontal(int x_pos, int y_pos, std::string direction);
	virtual Doco* createDocoVertical(int x_pos, int y_pos, std::string direction);
	virtual Doco* createDocoPerp(int x_pos, int y_pos, std::string direction);
};