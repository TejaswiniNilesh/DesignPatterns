#include <iostream>
#include<string>
using namespace std;

namespace creationalPattern
{
	class IDocument
	{
	public:
		virtual std::unique_ptr<IDocument> clone() = 0;
		virtual std::string getDocumentType() = 0;
		virtual ~IDocument() {}

	};

	class Xliff : public IDocument
	{
	public:
		std::unique_ptr<IDocument> clone() override
		{
			return std::make_unique<Xliff>();
		}
		std::string getDocumentType() override
		{
			return "Xliff Document";
		}
	};

	class Word : public IDocument
	{
	public:
		std::unique_ptr<IDocument> clone() override
		{
			return std::make_unique<Word>();
		}
		std::string getDocumentType() override
		{
			return "Word Document";
		}

	};

	class XML : public IDocument
	{
	public:
		std::unique_ptr<IDocument> clone() override
		{
			return std::make_unique<XML>();
		}
		std::string getDocumentType() override
		{
			return "XML Document";
		}

	};

	class IDocumentManager
	{
	public:
		static std::unique_ptr<IDocument> createDocument(int choice);
		~IDocumentManager() {}

	};

	std::unique_ptr<IDocument> IDocumentManager::createDocument(int choice)
	{
		switch (choice)
		{

		case 1:
			return std::make_unique<Xliff>();
		case 2:
			return std::make_unique<XML>();
		case 3:
			return std::make_unique<Word>();
		default:
			return nullptr;
		}
	}

}

using namespace creationalPattern;
constexpr int MaxDocType = 4;
int main()
{
	IDocumentManager * docManager;
	int userChoice;
	cout << "quit(0), Xliff(1), XML(2), Word(3): \n";
	while (true) {
		cout << "Type in your choice (0-3)\n";
		cin >> userChoice;
		if (userChoice <= 0 || userChoice >= MaxDocType)
			break;
		//auto document= std::move(IDocumentManager::createDocument(userChoice));
		std::unique_ptr<IDocument> document = IDocumentManager::createDocument(userChoice);
		cout << document->getDocumentType() << endl;
	}

	getchar();
}

