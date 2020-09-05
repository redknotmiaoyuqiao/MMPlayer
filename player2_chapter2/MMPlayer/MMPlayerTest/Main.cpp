#include "MMPlayer/MMPlayer.h"

int main()
{
	MMPlayer player("c:/DemoVideo/demo_video.mp4");

	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail\n");
		return -1;
	}

	player.Play();
	printf("======================1 Play======================\n");

	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Seek(10);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	player.Pause();
	printf("======================1 Pause======================\n");

	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Play();
	printf("======================2 Play======================\n");

	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Pause();

	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));


	player.Play();

	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(60 * 60));

	player.Stop();

	return 0;
}