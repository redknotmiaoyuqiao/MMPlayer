#pragma once

#include <string>
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMQueue/MMQueue.h"

class MMPlayerReaderThread : public MMThread
{
public:
	MMPlayerReaderThread(std::string path);
	~MMPlayerReaderThread();

	virtual void run();

private:
	std::string path;
};

class MMPlayerDecoderThread : public MMThread
{
public:
	MMPlayerDecoderThread();
	~MMPlayerDecoderThread();

	virtual void run();

	int Init(MMAVStream * avStream);

	int PutPacket(MMAVPacket * pkt);
	int GetPacketQueueSize();

private:
	MMAVDecoder* decoder = nullptr;
	MMQueue<MMAVPacket> packetQueue;
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