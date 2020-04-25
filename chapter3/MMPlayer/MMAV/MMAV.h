#pragma once

class MMAVPacketPrivate;

class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();
public:
	MMAVPacketPrivate* imp = nullptr;
};

class MMAVReaderPrivate;

class MMAVReader
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char * path);
	int Close();

	int Read(MMAVPacket * packet);

private:
	MMAVReaderPrivate* imp = nullptr;
};