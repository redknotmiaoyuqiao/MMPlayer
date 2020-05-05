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
	MMPlayerDecoderThread* videoDecoderThread = new MMPlayerDecoderThread();
	MMPlayerDecoderThread* audioDecoderThread = new MMPlayerDecoderThread();

	MMAVStream videoStream;
	reader.GetStream(&videoStream, videoStreamIndex);
	videoDecoderThread->Init(&videoStream);

	MMAVStream audioStream;
	reader.GetStream(&audioStream, audioStreamIndex);
	audioDecoderThread->Init(&audioStream);

	videoDecoderThread->Start();
	audioDecoderThread->Start();

	while (!stopFlag) {
		if (videoDecoderThread->GetPacketQueueSize() > 5 && audioDecoderThread->GetPacketQueueSize() > 5) {
			continue;
		}

		MMAVPacket* pkt = new MMAVPacket();
		int ret = reader.Read(pkt);
		if (ret) {
			delete pkt;
			pkt = nullptr;
			break;
		}

		if (pkt->GetIndex() == videoStreamIndex) {
			videoDecoderThread->PutPacket(pkt);
		}

		if (pkt->GetIndex() == audioStreamIndex) {
			audioDecoderThread->PutPacket(pkt);
		}

		// 将 Packet 放入缓存
		printf("Read Packet Success\n");

		// delete pkt;
		// pkt = nullptr;
	}

	videoDecoderThread->Stop();
	audioDecoderThread->Stop();

	reader.Close();
}