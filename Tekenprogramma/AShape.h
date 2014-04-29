#pragma once


class AShape
{

public:
	AShape();
	~AShape();
	void setStartPoint(CPoint &point);
	void setEndPoint(CPoint &point);

	CPoint* getStartPoint();
	CPoint* getEndPoint();

	virtual void undraw(CDC *pDC) = 0; // pure virtual
	virtual void draw(CDC *pDC) = 0; // pure virtual

public:
	CPoint startPoint;
	CPoint previousPoint;
	CPoint endPoint;
	CPen pen;
};

