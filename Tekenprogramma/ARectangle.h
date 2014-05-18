#pragma once
#include "acircle.h"
class ARectangle :
	public ACircle
{
public:
	ARectangle(void);
	~ARectangle(void);
	void undraw(CDC *pDC);
	void draw(CDC *pDC);
	bool isOn(CPoint point) const;
};

