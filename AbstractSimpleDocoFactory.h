
#pragma once
#include "Doco.h"

class AbstractSimpleDocoFactory
{
public:
	virtual Doco createDocoDefault();
	virtual Doco createDocoDiagonal();
	virtual Doco createDocoHoriziontal();
	virtual Doco createDocoVertical();
	virtual Doco createDocoPerp();
};