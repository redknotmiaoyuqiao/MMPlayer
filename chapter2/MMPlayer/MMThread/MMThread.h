#pragma once

class MMThread
{
public:
	virtual void run() = 0;
	int Start();
};