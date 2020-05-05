#include "MMPlayer.h"
#include "MMAV/MMAV.h"

MMPlayerReaderThread::MMPlayerReaderThread(std::string _path)
{
	path = _path;
}

MMPlayerReaderThread::~MMPlayerReaderThread()
{

}

void MMPlayerReaderThread::run()
{
	MMAVReader reader;
	int ret = reader.Open(path.c_str());
	if (ret) {
		return;
	}

	int videoStreamIndex = reader.GetVideoStreamIndex();
	int audioStreamIndex = reader.GetAudioStreamIndex();

	// TODO 初始化解码器

	while (!stopFlag) {
		MMAVPacket* pkt = new MMAVPacket();
		int ret = reader.Read(pkt);
		if (ret) {
			delete pkt;
			pkt = nullptr;
			break;
		}

		// 将 Packet 放入缓存
		printf("Read Packet Success\n");

		delete pkt;
		pkt = nullptr;
	}

	reader.Close();
}