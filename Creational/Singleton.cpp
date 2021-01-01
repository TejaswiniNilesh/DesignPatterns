#include<iostream>
#include<thread>
using namespace std;
#include <thread>
#include<mutex>
#include<string>
using namespace std;

//std::mutex mt;

class Logger
{
public:
	//static Logger* getInstance();
	//static Logger& getInstance();
//	static void destroyInstance();
	static Logger & getInstance()
	{
		//	std::unique_lock<std::mutex> lock(mt, std::defer_lock); // do not acquire ownership of the mutex
		//	lock.lock();
			//if (m_instance == nullptr)
			//{
			//	m_instance = new Logger();
			//}
		//	lock.unlock();

		std::call_once(flag, [&]() { m_instance.reset(new Logger()); cout << "count ++" << endl; });

		//return m_instance.get_interface()
		return *(m_instance.get());
	}
	static void log(const std::string & message);
private:
	Logger() = default;
	Logger(const Logger & Logger) = delete;
	Logger operator=(const Logger & Logger) = delete;
	//~Logger() = default;
	
	static std::unique_ptr<Logger> m_instance;
	static std::once_flag flag;

};

std::unique_ptr<Logger> Logger::m_instance;
std::once_flag Logger::flag;

//
//void Logger::destroyInstance()
//{
//	if (instance)
//	{
//		delete instance;
//		instance = nullptr;
//	}
//}

void Logger::log(const std::string & message)
{
	cout << message << endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
	Logger &logInstance = Logger::getInstance();
	
	std::thread thread1(&Logger::log,"Task 1");
	std::thread thread2(&Logger::log,"Task 2");

	std::cout << "starting first helper...\n";
	thread1.join();

	std::cout << "starting second helper...\n";
	thread2.join();

	std::cout << "waiting for helpers to finish..." << std::endl;

	cout << "Main worker thread" << endl;
	getchar();
}