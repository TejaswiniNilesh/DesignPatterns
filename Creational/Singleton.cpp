#include<iostream>
#include<thread>
using namespace std;
#include <thread>
#include<mutex>

using namespace std;

std::mutex mt;

class Logger
{
public:
	static Logger* getInstance();
	static void destroyInstance();
	void log(const std::string & message);
private:
	Logger() = default;
	Logger(const Logger & Logger) = delete;
	Logger operator=(const Logger & Logger) = delete;
	~Logger() = default;
	static Logger *m_instance;

};

Logger * Logger::getInstance()
{
	std::unique_lock<std::mutex> lock(mt, std::defer_lock); // do not acquire ownership of the mutex
	lock.lock();
	if (m_instance == nullptr)
	{
		m_instance = new Logger();
	}
	lock.unlock();
	return m_instance;
}

void Logger::destroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void Logger::log(const std::string & message)
{
	cout << "Excetpion log" << endl;
}


int main()
{
	std::thread threads[5];
}