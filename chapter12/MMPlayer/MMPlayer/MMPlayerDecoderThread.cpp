#include "MMPlayer.h"

MMPlayerDecoderThread::MMPlayerDecoderThread(MMPlayerCtr* _playerCtr, MMDecoderType _type)
{
	decoder = new MMAVDecoder();
	playerCtr = _playerCtr;
	type = _type;
}

MMPlayerDecoderThread::~MMPlayerDecoderThread()
{
	if (decoder != nullptr) {
		delete decoder;
		decoder = nullptr;
	}
}

int MMPlayerDecoderThread::Init(MMAVStream* avStream)
{
	return decoder->Init(avStream);
}

int MMPlayerDecoderThread::PutPacket(MMAVPacket* pkt)
{
	return packetQueue.Push(pkt);
}

int MMPlayerDecoderThread::GetPacketQueueSize()
{
	return packetQueue.Size();
}

void MMPlayerDecoderThread::run()
{
	int frameCount = 0;
	// 进行解码操作
	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
			if (playerCtr->GetVideoQueueSize() > 10) {
				continue;
			}
		}
		else if (type == MMDecoderType::MMDECODER_TYPE_AUDIO) {
			if (playerCtr->GetAudioQueueSize() > 20) {
				continue;
			}
		}



		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			// 队列为空，取不到 Packet
			continue;
		}

		decoder->SendPacket(pkt);
		while (1) {
			MMAVFrame* frame = new MMAVFrame();
			ret = decoder->RecvFrame(frame);
			if (ret) {
				break;
			}
			frameCount++;
			// printf("Decoder Success: %d\n", frameCount);
			// std::this_thread::sleep_for(std::chrono::seconds(1));

			// 通过 playerCtr 的句柄，向其塞入 Frame 数据
			if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
				playerCtr->PushFrameToVideoQueue(frame);
			}
			else if (type == MMDecoderType::MMDECODER_TYPE_AUDIO) {
				playerCtr->PushFrameToAudioQueue(frame);
			}
		}
	}
}