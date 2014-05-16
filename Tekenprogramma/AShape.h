#pragma once
#include<string>

class AShape
{

public:
	AShape();
	~AShape();
	void setStartPoint(CPoint &point);
	void setEndPoint(CPoint &point);

	CPoint* getStartPoint();
	CPoint* getEndPoint();
	bool isSet;
	
	std::string getSerialized();

	virtual void undraw(CDC *pDC) = 0; // pure virtual
	virtual void draw(CDC *pDC) = 0; // pure virtual

protected:
	CPoint startPoint;
	CPoint previousPoint;
	CPoint endPoint;
	short shapeType;
};

