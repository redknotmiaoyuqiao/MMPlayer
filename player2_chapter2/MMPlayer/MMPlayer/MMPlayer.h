#pragma once

#include <string>
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMQueue/MMQueue.h"

enum MMDecoderType
{
	MMDECODER_TYPE_VIDEO = 0,
	MMDECODER_TYPE_AUDIO = 1
};

enum MMPlayerCtrStatus
{
	MMPLAYER_CTR_STATUS_PLAYING = 0,
	MMPLAYER_CTR_STATUS_PAUSEING = 1
};

class MMPlayerCtr : public MMThread
{
public:
	MMPlayerCtr(double seekTime = 0.0);
	~MMPlayerCtr();

	virtual void run();

	int Play();
	int Pause();

	int GetVideoQueueSize();
	int GetAudioQueueSize();

	int PushFrameToVideoQueue(MMAVFrame * frame);
	int PushFrameToAudioQueue(MMAVFrame* frame);
private:
	MMQueue<MMAVFrame> videoQueue;
	MMQueue<MMAVFrame> audioQueue;

	MMPlayerCtrStatus status = MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PLAYING;

	double seekTime = 0.0;
};

class MMPlayerReaderThread : public MMThread
{
public:
	MMPlayerReaderThread(std::string path, double seekTime, MMPlayerCtr * playerCtr);
	~MMPlayerReaderThread();

	virtual void run();

private:
	std::string path;
	MMPlayerCtr* playerCtr = nullptr;
	double seekTime = 0.0;
};

class MMPlayerDecoderThread : public MMThread
{
public:
	MMPlayerDecoderThread(MMPlayerCtr* playerCtr, MMDecoderType type);
	~MMPlayerDecoderThread();

	virtual void run();

	int Init(MMAVStream * avStream);

	int PutPacket(MMAVPacket * pkt);
	int GetPacketQueueSize();

private:
	MMAVDecoder* decoder = nullptr;
	MMQueue<MMAVPacket> packetQueue;

	MMPlayerCtr* playerCtr = nullptr;

	MMDecoderType type;
};

class MMPlayer
{
public:
	MMPlayer(std::string path);
	~MMPlayer();

	int Open(double time = 0.0);
	int Stop();

	int Play();
	int Pause();

	int Seek(double time);

private:
	std::string path;
	MMPlayerReaderThread* readerThread = nullptr;

	MMPlayerCtr* playerCtr = nullptr;
};