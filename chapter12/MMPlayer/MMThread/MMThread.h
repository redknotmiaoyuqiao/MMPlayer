#pragma once

#include <thread>

class MMThread
{
public:
	virtual void run() = 0;
	int Start();
	int Stop();

public:
	std::thread* t = nullptr;
	int stopFlag = 0;
};