#include <iostream>
#include<string>

using namespace std;

namespace CreationalPatterns
{
	class SpellChecker
	{
	public:
		std::string getWord() const
		{
			return m_inputWord;
		}
		virtual std::string getSpellCheck() const = 0;

		friend std::ostream& operator <<(ostream & out, std::unique_ptr<SpellChecker> &spellCheck)
		{
			return out << spellCheck->getWord() << "=" << spellCheck->getSpellCheck() << endl;
		}
		SpellChecker() :m_inputWord(""), m_correctWord("") {}
		SpellChecker(const std::string& word) :m_inputWord(word), m_correctWord("") {}
		SpellChecker(const SpellChecker&) = delete;
		SpellChecker& operator =(const SpellChecker&) = delete;
		virtual ~SpellChecker() {};

	protected:
		std::string m_inputWord;
		std::string m_correctWord;
	};
	class SpellCheckLib : public SpellChecker
	{
	public:
		std::string getSpellCheck() const override
		{
			return "Corrected Word: " + m_correctWord;
		}
		SpellCheckLib(const std::string& word) :SpellChecker(word){}
		//Delete 5 default functions
		~SpellCheckLib() {}
	};
	class SpellCheckService : public SpellChecker
	{
	public:
		std::string getSpellCheck() const override
		{
			return "Corrected Word: " + m_correctWord;
		}
		SpellCheckService(const std::string& word) :SpellChecker(word){}
		//Delete 5 default functions
		~SpellCheckService() {}

	};


	class Translator
	{
	public:
		std::string getWord() const
		{
			return m_inputWord;
		}
		virtual std::string getTranslate() const = 0;

		friend std::ostream& operator <<(ostream & out, std::unique_ptr<Translator> &translation)
		{
			return out << translation->getWord() << "=" << translation->getTranslate() << endl;
		}
		Translator() :m_inputWord(""), m_translatedWord("") {}
		Translator(const std::string& word) :m_inputWord(word), m_translatedWord("") {}
		Translator(const Translator&) = delete;
		Translator& operator =(const Translator&) = delete;
		virtual ~Translator() {}

	protected:
		std::string m_inputWord;
		std::string m_translatedWord;
	};
	class TranslationLib : public Translator
	{
	public:
		
		std::string getTranslate() const override
		{
			return "Translated Word "+m_translatedWord;
		}
	
		TranslationLib (const std::string& word) : Translator(word){}
		//Delete 5 default functions
		~TranslationLib() {}
	};
	class TranslationService : public Translator
	{
	public:

		std::string getTranslate() const override
		{
			return "Translated Word "+m_translatedWord;
		}
		TranslationService(const std::string& word) : Translator(word) {}

		//Delete 5 default functions
		~TranslationService() {}

	};

	class AbstractFactoryConnectionMode
	{
	public:

		virtual std::unique_ptr<SpellChecker> callSpellChecker() = 0;
		virtual std::unique_ptr<Translator> callTranslator() = 0;

		AbstractFactoryConnectionMode() = default;
		AbstractFactoryConnectionMode(const AbstractFactoryConnectionMode&) = delete;
		AbstractFactoryConnectionMode(AbstractFactoryConnectionMode&&) = delete;
		AbstractFactoryConnectionMode& operator =(const AbstractFactoryConnectionMode&) = delete;
		virtual ~AbstractFactoryConnectionMode() {}
	};

	class ConcreteFactoryOnline : public AbstractFactoryConnectionMode
	{
	public:
		std::unique_ptr<SpellChecker> callSpellChecker() override
		{
			return std::make_unique<SpellCheckService>(string("word for spellchecker service"));
		}
		std::unique_ptr<Translator> callTranslator() override
		{
			return std::make_unique<TranslationService>(string("word for translation service"));
		}

		ConcreteFactoryOnline() = default;
		ConcreteFactoryOnline(const ConcreteFactoryOnline&) = delete;
		ConcreteFactoryOnline& operator =(const ConcreteFactoryOnline&) = delete;
		
		ConcreteFactoryOnline(ConcreteFactoryOnline&&) = delete;
		ConcreteFactoryOnline& operator =(ConcreteFactoryOnline&&) = delete;

		~ConcreteFactoryOnline() {}

	};

	class ConcreteFactoryOffline : public AbstractFactoryConnectionMode
	{
	public:
		std::unique_ptr<SpellChecker> callSpellChecker() override
		{
			return std::unique_ptr<SpellCheckLib>(new SpellCheckLib(string("word for spellcheck lib")));
		}
		std::unique_ptr<Translator> callTranslator() override
		{
			return std::unique_ptr<TranslationLib>(new TranslationLib(string("word for translation lib")));
		}

		ConcreteFactoryOffline() = default;
		ConcreteFactoryOffline(const ConcreteFactoryOffline&) = delete;
		ConcreteFactoryOffline& operator =(const ConcreteFactoryOffline&) = delete;
		~ConcreteFactoryOffline() {}

	};

}
using namespace CreationalPatterns;

void clientApplication(const std::shared_ptr< AbstractFactoryConnectionMode> connectionMode)
{
	std::unique_ptr<SpellChecker> spellCheck = connectionMode->callSpellChecker();
	std::unique_ptr<Translator> translate = connectionMode->callTranslator();

	std::cout << spellCheck << endl;
	std::cout << translate << endl;

}
int main()
{
//	ConcreteFactoryOnline online;
//	ConcreteFactoryOffline offline;

	std::shared_ptr<ConcreteFactoryOnline> online = std::make_shared<ConcreteFactoryOnline>();
	std::shared_ptr<ConcreteFactoryOffline> offline = std::make_shared<ConcreteFactoryOffline>();

	clientApplication(online);
	clientApplication(offline);

	getchar();
}




//#include <iostream>
//using namespace std;
//
//namespace CreationalPatterns
//{
//
//	class Word
//	{
//
//	};
//	class HindiWord
//	{
//
//	};
//	class EnglisWord
//	{
//
//	};
//
//	class AbstractFactoryString
//	{
//
//	};
//	class ConcreteFactoryWord : public AbstractFactoryString
//	{
//
//	};
//
//	class ConcreteFactoryNumber : public AbstractFactoryString
//	{
//
//	};
//
//
//
//
//}
//using namespace CreationalPatterns;
//int main()
//{
//	ConcreteFactoryWord word;
//	ConcreteFactoryNumber number;
//
//	std::shared_ptr<ConcreteFactoryWord> wordFactory = std::make_shared<ConcreteFactoryWord>();
//	std::shared_ptr<ConcreteFactoryNumber> numberFactory = std::make_shared<ConcreteFactoryNumber>();
//
//
//}
