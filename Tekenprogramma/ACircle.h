#pragma once
#include "ashape.h"

class ACircle :
	public AShape
{
public:
	ACircle(void);
	~ACircle(void);
	void undraw(CDC *pDC);
	void draw(CDC *pDC);
	bool isOn(CPoint point) const;
};

