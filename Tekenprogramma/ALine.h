#pragma once
#include "ashape.h"
class ALine :
	public AShape
{
public:
	ALine(void);
	~ALine(void);
	void undraw(CDC *pDC);
	void draw(CDC *pDC);
};

