#include "MMPlayer.h"

MMPlayerCtr::MMPlayerCtr(double _seekTime)
{
	seekTime = _seekTime;
}

MMPlayerCtr::~MMPlayerCtr()
{

}

int MMPlayerCtr::Play()
{
	status = MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PLAYING;
	return 0;
}

int MMPlayerCtr::Pause()
{
	status = MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PAUSEING;
	return 0;
}

void MMPlayerCtr::run()
{
	MMPlayerReaderThread readerThread("c:/DemoVideo/demo_video.mp4", seekTime, this);
	readerThread.Start();

	// 获取线程启动时候的时间 start_time
	long long startTime = MMAVTime::GetTime();

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	long long sleepCountTime = 0;

	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		long long sleepTimeStart = MMAVTime::GetTime();
		while (status == MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PAUSEING) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		long long sleepTimeEnd = MMAVTime::GetTime();
		long long sleepDTime = sleepTimeEnd - sleepTimeStart;
		sleepCountTime += sleepDTime;

		// 获取当前的时间 now_time
		long long nowTime = MMAVTime::GetTime();

		// 获取到当前时间和开始时间的差值 d_time
		long long dTime = nowTime - startTime;
		dTime = dTime - sleepCountTime;

		dTime = dTime + (long long)(seekTime * 1000);

		// printf("DTime: %lld\n", dTime);

		// 从视频缓存队列中，获取一帧视频 frame_pts 
		if (videoFrame == nullptr) {
			// 尝试取一帧出来
			videoQueue.Pop(&videoFrame);
		}

		// printf("Video Queue Size: %d\n", videoQueue.Size());

		if (videoFrame != nullptr) {
			if (videoFrame->GetPts() < (long long)(seekTime * 1000)) {
				delete videoFrame;
				videoFrame = nullptr;
			}
		}
		
		if (videoFrame != nullptr) {
			// 如果 frame_pts <= d_time
			if (videoFrame->GetPts() <= dTime) {
				// 这帧视频，应该立即播放出来
				printf("Video Frame: %lld\n", videoFrame->GetPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			// 否则
				// 这帧视频还不到播放的时候,程序进行自旋，或者去处理音频
			else {

			}
		}
		



		// 从音频缓存队列中，获取一帧音频 frame_pts 
		if (audioFrame == nullptr) {
			audioQueue.Pop(&audioFrame);
		}

		if (audioFrame != nullptr) {
			if (audioFrame->GetPts() < (long long)(seekTime * 1000)) {
				delete audioFrame;
				audioFrame = nullptr;
			}
		}

		if (audioFrame != nullptr) {
			// 如果 frame_pts <= d_time
			if (audioFrame->GetPts() <= dTime) {
				// 这帧音频，应该立即播放出来
				// printf("Audio Frame\n");
				delete audioFrame;
				audioFrame = nullptr;
			}
			else {
				// 这帧音频还不到播放的时候,程序进行自旋。
			}
		}
	}

	readerThread.Stop();
}

int MMPlayerCtr::GetVideoQueueSize()
{
	return videoQueue.Size();
}

int MMPlayerCtr::GetAudioQueueSize()
{
	return audioQueue.Size();
}

int MMPlayerCtr::PushFrameToVideoQueue(MMAVFrame* frame)
{
	// printf("Vudio Queue Size: %d\n", videoQueue.Size());
	return videoQueue.Push(frame);
}

int MMPlayerCtr::PushFrameToAudioQueue(MMAVFrame* frame)
{
	// printf("Audio Queue Size: %d\n", audioQueue.Size());
	return audioQueue.Push(frame);
}