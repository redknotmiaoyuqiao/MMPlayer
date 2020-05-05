#pragma once

#include <string>
#include "MMThread/MMThread.h"

class MMPlayerReaderThread : public MMThread
{
public:
	MMPlayerReaderThread(std::string path);
	~MMPlayerReaderThread();

	virtual void run();

private:
	std::string path;
};

class MMPlayer
{
public:
	MMPlayer(std::string path);
	~MMPlayer();

	int Open();
	int Stop();

	int Play();
	int Pause();

	int Seek(double time);

private:
	std::string path;
	MMPlayerReaderThread* readerThread = nullptr;
};