// MMPlayer.cpp: 定义应用程序的入口点。
//
#include <thread>
#include <chrono>
#include <vector>
#include "MMThread/MMThread.h"

int a;

void threadFunction(int i) {
	printf("Thread Function: %d\n", i);
}

void threadFun(int threadIndex) {
	for (int i = 0; i < 1000;i++) {
		printf("Thread: %d, index: %d\n", threadIndex, i);
	}
}

int main2()
{
	// std::thread t(threadFunction, 10);
	// t.join();
	// t.detach();

	// t.joinable();

	std::thread t1(threadFun, 1);
	std::thread t2(threadFun, 2);

	t1.join();
	t2.join();

	return 0;
}






class MyMMThread : public MMThread
{
private:
	int a = 0;
public:
	MyMMThread(int _a) 
	{
		a = _a;
	}

	virtual void run()
	{
		printf("MyMMThread %d\n", a);
	}
};

int main_thread()
{
	MyMMThread t(10);
	t.Start();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}


#include "MMAV/MMAV.h"

int main() {
	MMAVReader reader;

	int ret = reader.Open("c://DemoVideo/demo_video.MP4");
	if (ret) {
		printf("Open File Fail!!!\n");
		return -1;
	}

	int videoStreamIndex = reader.GetVideoStreamIndex();
	int audioStreamIndex = reader.GetAudioStreamIndex();

	printf("VideoStreamIndex: %d\n", videoStreamIndex);
	printf("AudioStreamIndex: %d\n", audioStreamIndex);

	std::vector<MMAVDecoder*> decoderList;

	int streamCount = reader.GetStreamCount();
	for (int i = 0; i < streamCount;i++) {
		MMAVStream avStream;
		reader.GetStream(&avStream, i);

		printf("StreamIndex:%d\n", avStream.streamIndex);

		MMAVDecoder* decoder = new MMAVDecoder();
		int ret = decoder->Init(&avStream);
		if (ret) {
			printf("Init decoder fail\n");
		}

		decoderList.push_back(decoder);
	}


	FILE* f = fopen("c://DemoVideo/demo_video.yuv", "wb");

	while (1) {
		MMAVPacket pkt;
		ret = reader.Read(&pkt);
		if (ret) {
			break;
		}

		int streamIndex = pkt.GetIndex();

		MMAVDecoder* decoder = decoderList[streamIndex];

		ret = decoder->SendPacket(&pkt);
		if (ret) {
			continue;
		}

		while (1) {
			MMAVFrame frame;
			ret = decoder->RecvFrame(&frame);
			if (ret) {
				break;
			}

			// Recv Success
			if (streamIndex == videoStreamIndex) {
				frame.VideoPrint();

				int width = frame.GetW();
				int height = frame.GetH();

				unsigned char* y = (unsigned char*)malloc(width * height);
				unsigned char* u = (unsigned char*)malloc(width / 2 * height / 2);
				unsigned char* v = (unsigned char*)malloc(width / 2 * height / 2);

				frame.GetY(y);
				frame.GetU(u);
				frame.GetV(v);

				fwrite(y, width * height, 1, f);
				fwrite(u, width / 2 * height / 2, 1, f);
				fwrite(v, width / 2 * height / 2, 1, f);

				free(y);
				free(u);
				free(v);
			}
			if (streamIndex == audioStreamIndex) {
				frame.AudioPrint();
			}
		}
	}

	for (int i = 0;i< decoderList.size(); i++) {
		MMAVDecoder* decoder = decoderList[i];

		ret = decoder->SendPacket(nullptr);

		while (1) {
			MMAVFrame frame;
			ret = decoder->RecvFrame(&frame);
			if (ret) {
				break;
			}

			// Recv Success

		}
	}

	reader.Close();


	for (int i = 0; i < decoderList.size();i++) {
		MMAVDecoder* decoder = decoderList[i];
		decoder->Close();
		delete decoder;
	}
	decoderList.clear();

	fclose(f);

	return 0;
}
