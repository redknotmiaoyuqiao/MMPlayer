#pragma once

class MMAVStreamPrivate;
class MMAVStream;

class MMAVPacketPrivate;

class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();

	int GetIndex();
public:
	MMAVPacketPrivate* imp = nullptr;
};

class MMAVFramePrivate;

class MMAVFrame
{
public:
	MMAVFrame();
	~MMAVFrame();

	int VideoPrint();
	int AudioPrint();

	int GetW();
	int GetH();

	int GetY(unsigned char* y);
	int GetU(unsigned char* u);
	int GetV(unsigned char* v);

	long long GetPts();

public:
	MMAVFramePrivate* imp = nullptr;
};



class MMAVReaderPrivate;

class MMAVReader
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char * path);

	int GetStreamCount();
	int GetStream(MMAVStream * stream, int streamId);

	int GetVideoStreamIndex();
	int GetAudioStreamIndex();

	int Close();

	int Read(MMAVPacket * packet);

	int Seek(double time);
private:
	MMAVReaderPrivate* imp = nullptr;
};

class MMAVStreamPrivate;

class MMAVStream
{
public:
	MMAVStream();
	~MMAVStream();
public:
	int streamIndex = -1;
	int timebaseNum = 0;
	int timebaseDen = 0;
	MMAVStreamPrivate* imp = nullptr;
};


class MMAVDecoderPrivate;

class MMAVDecoder
{
public:
	MMAVDecoder();
	~MMAVDecoder();

	int Init(MMAVStream * stream);

	int SendPacket(MMAVPacket * pkt);

	int RecvFrame(MMAVFrame * frame);

	int Close();

private:
	MMAVDecoderPrivate* imp = nullptr;

	int timebaseNum = 0;
	int timebaseDen = 0;
};


class MMAVTime
{
public:
	static long long GetTime();
};