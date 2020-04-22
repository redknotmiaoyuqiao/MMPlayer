// MMPlayer.cpp: 定义应用程序的入口点。
//
#include <thread>
#include <chrono>
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

int main()
{
	MyMMThread t(10);
	t.Start();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}
