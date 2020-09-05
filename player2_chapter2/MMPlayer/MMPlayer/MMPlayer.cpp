#include "MMPlayer.h"

MMPlayer::MMPlayer(std::string _path)
{
	path = _path;
}

MMPlayer::~MMPlayer()
{

}

int MMPlayer::Open(double time)
{
	/*
	if (readerThread == nullptr) {
		readerThread = new MMPlayerReaderThread(path);
		readerThread->Start();

		return 0;
	}
	*/

	if (playerCtr == nullptr) {
		playerCtr = new MMPlayerCtr(time);
		playerCtr->Start();
		return 0;
	}
	
	return -1;
}

int MMPlayer::Stop()
{
	/*
	if (readerThread != nullptr) {
		readerThread->Stop();
		delete readerThread;
		readerThread = nullptr;
	}
	*/
	if (playerCtr != nullptr) {
		playerCtr->Stop();
		delete playerCtr;
		playerCtr = nullptr;
	}

	return 0;
}

int MMPlayer::Play()
{
	if (playerCtr != nullptr) {
		playerCtr->Play();
	}
	return 0;
}

int MMPlayer::Pause()
{
	if (playerCtr != nullptr) {
		playerCtr->Pause();
	}
	return 0;
}

int MMPlayer::Seek(double time)
{
	Stop();
	Open(time);
	return 0;
}