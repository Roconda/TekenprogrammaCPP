#pragma once
class AWriter
{
public:
	static AWriter& getInstance();
private:
	AWriter();
	~AWriter();
};

