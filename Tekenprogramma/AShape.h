#pragma once
class AShape
{

public:
	AShape();
	~AShape();
	void setStartPoint(CPoint *point);
	void setEndPoint(CPoint *point){
		endPoint = point;
	}
	void setCDC(CDC *cdcP){
		cdc = cdcP;
	}
	virtual void draw() = 0; // pure virtual

public:
	CPoint *startPoint;
	CPoint *endPoint;
	CDC *cdc;
};

