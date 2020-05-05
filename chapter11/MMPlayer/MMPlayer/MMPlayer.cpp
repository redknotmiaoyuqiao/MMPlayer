#include "MMPlayer.h"

MMPlayer::MMPlayer(std::string _path)
{
	path = _path;
}

MMPlayer::~MMPlayer()
{

}

int MMPlayer::Open()
{
	if (readerThread == nullptr) {
		readerThread = new MMPlayerReaderThread(path);
		readerThread->Start();

		return 0;
	}
	
	return -1;
}

int MMPlayer::Stop()
{
	if (readerThread != nullptr) {
		readerThread->Stop();
		delete readerThread;
		readerThread = nullptr;
	}
	return 0;
}

int MMPlayer::Play()
{
	return 0;
}

int MMPlayer::Pause()
{
	return 0;
}

int MMPlayer::Seek(double time)
{
	return 0;
}