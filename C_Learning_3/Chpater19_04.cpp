#include <iostream>
#include <thread>
#include <atomic>	
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;

int main()
{
	int shared_memory(0);

	auto count_func = [&]() {
		for (int i = 0; i < 1000; ++i)
		{
			this_thread::sleep_for(chrono::milliseconds(1));

			std::lock_guard lock(mtx); //std::scoped_lock lock(mtx);
			//요새는 이게 더 안전해서 권장됨
			shared_memory++;

		}
	};

	thread t1 = thread(count_func);
	thread t2 = thread(count_func);

	t1.join();
	t2.join();

	cout << "After" << endl;
	cout << shared_memory << endl;

	return 0;
}