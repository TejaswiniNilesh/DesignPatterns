#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

namespace CreationalPatterns
{

	enum class Languages
	{
		Hindi,
		English
	};


	class Number
	{
	public:

		Number() :m_number(0) {} //default constructor
		Number(int num) :m_number(num) {}
		Number(const Number&) = delete; // copy constructor
		Number& operator= (const Number&) = delete; //Assignment operator
		virtual ~Number() {} //destructor

		virtual std::string getNumbertoWord() const = 0;
		int getNumber() const { return m_number; };
		std::string getLanguage() const { return convert(m_language); }
		friend std::ostream & operator << (std::ostream &out, const std::unique_ptr<Number> &number)
		{
			if (number == nullptr)
			{
				return out << "number empty";
			}
			return (out << "Language: " << number->getLanguage() << "\t Number: " << number->getNumber() << "\tWord: " << number->getNumbertoWord() << endl);
		}
	protected:

		int m_number = 0;
		string m_word;
		Languages m_language;

	private:
		string convert(Languages lang) const
		{
			switch (lang)
			{
			case Languages::Hindi:
				return "Hindi";
			case Languages::English:
				return "English";
			default:
				return string();
			}
		}
	};

	class EnglishNumber : public Number
	{
	public:
		std::string getNumbertoWord() const override
		{
			return "Convert English Number";
		}
		EnglishNumber() = delete;
		EnglishNumber(int num) :Number(num) {}
		EnglishNumber(const EnglishNumber &) = delete;
		EnglishNumber&  operator = (const EnglishNumber&) = delete;

	};

	class HindiNumber : public Number
	{
	public:
		std::string getNumbertoWord() const override
		{
			return "Convert Hindi Number";
		}		
		HindiNumber() = delete;
		HindiNumber(int num) :Number(num) {}
		HindiNumber(const HindiNumber &) = delete;
		HindiNumber&  operator = (const HindiNumber&) = delete;

	};


	class ConverterFactory
	{
	public:
		virtual std::unique_ptr<Number>convertNumberToWord(Languages type, int num) = 0;

		ConverterFactory() = default; //default constructor
		ConverterFactory(const ConverterFactory&) = delete; // copy constructor
		ConverterFactory& operator = (const ConverterFactory&) = delete; // assignment operator
		virtual ~ConverterFactory() {}

	};

	class ConcreteConverter : public ConverterFactory
	{
	public:

		std::unique_ptr<Number>convertNumberToWord(Languages type, int num) override
		{
			switch (type)
			{
			case Languages::Hindi:
					return std::make_unique<HindiNumber>(num);
				
			case Languages::English:
					return std::make_unique<EnglishNumber>(num);
			default:
				return nullptr;
			}
		}

		ConcreteConverter() = default;
		ConcreteConverter(const ConcreteConverter&) = delete; //copy constructor
		ConcreteConverter& operator = (const ConcreteConverter&) = delete; // assignment operator
		ConcreteConverter(ConcreteConverter&&) = delete; //move constructor
		ConcreteConverter operator=(ConcreteConverter&&) = delete; //move assignment operator
		~ConcreteConverter() = default; //default destructor
	};

}

using namespace CreationalPatterns;
void printMessage()
{
	cout << "Program converts input number to word" << endl;
	cout << "Enter language of conversion:hindi or english " << endl;
	cout << "Enter number to convert:" << endl;
}
Languages convertLangToEnum(string language)
{
	transform(language.begin(), language.end(), language.begin(), tolower);
	if (language == "hindi")
	{
		return Languages::Hindi;
	}
	else if (language == "english")
	{
		return Languages::English;
	}

}
int main()
{
	std::unique_ptr<ConverterFactory> converter = std::make_unique<ConcreteConverter>();
	printMessage();
	string language;
	cin >> language;
	int num;
	cin >> num;
	cout << converter->convertNumberToWord(convertLangToEnum(language), num);
	

	getchar();
	//return 0;
}