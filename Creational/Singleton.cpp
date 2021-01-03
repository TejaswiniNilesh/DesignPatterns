#include<iostream>
#include<thread>
using namespace std;
#include <thread>
#include<mutex>
#include<string>
using namespace std;

//std::mutex mt;
namespace CreationalPatterns
{
	class Logger
	{
	public:

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


			//Executes the function exactly once, even if called concurrently, from several threads.
			std::call_once(m_flag, [&]() {
				//m_instance = std::unique_ptr<Logger>(new Logger());
				//m_instance = std::make_unique<Logger>();

				m_instance.reset(new Logger());
				cout << " Instance created..." << endl;
			});

			//return m_instance.get_interface()
			return *(m_instance.get());
		}
		static void log(const std::string & message);
	private:
		Logger() = default;
		Logger(const Logger & Logger) = delete;
		Logger operator=(const Logger & Logger) = delete;
		//~Logger() = default;
		//static Logger* getInstance();

		static std::unique_ptr<Logger> m_instance;
		static std::once_flag m_flag;

	};

	std::unique_ptr<Logger> Logger::m_instance;
	std::once_flag Logger::m_flag;

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

	void thread1CallLog(string message)
	{
		Logger &logInstance = Logger::getInstance();
		logInstance.log("Thread 1 logging done...");

	}
	void thread2CallLog(string message)
	{
		Logger &logInstance2 = Logger::getInstance();
		logInstance2.log("Thread 2 logging done...");

	}
}
using namespace CreationalPatterns;
int main()
{
	cout << "Main worker thread" << endl;

	/*
	std::thread thread1(&Logger::log,"Task 1");
	std::thread thread2(&Logger::log,"Task 2");
	*/
	std::cout << "starting first helper...\n";
	std::thread thread1(thread1CallLog, "Task 1");

	std::cout << "starting second helper...\n";
	std::thread thread2(thread2CallLog, "Task 2");

	std::cout << "waiting for helpers to finish..." << std::endl;
	thread1.join();
	thread2.join();


	getchar();
}