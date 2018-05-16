#include "Driver.hpp"							// class header
#include "Test.hpp"								// Test class
#include "GA.hpp"								// GA
#include "../../../../IniParser/IniParser.hpp"	// IniParser class

#define _DEBUG 1

using namespace std;


char Driver::askUserYesNo(void)
{
	char c = 0x0;
	bool first = true;

	do
	{
		if (!first)
		{
			cout << "Invalid input! Try again." << endl;
		} // end if
		first = false;

		cout << "Enter choice (Y/N): ";
		cin >> c;

		if (cin.fail()) // error check
		{
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
			continue;
		} // end if

		c = static_cast<char>(tolower(static_cast<char>(c)));

	} while (c != 'y' && c != 'n');

	return c;
} // end method askUserYesNo


void Driver::initialize(const std::string  s_fileName)
{
	IniParser* parser = new IniParser(s_fileName);

	try
	{
		// extract data from .ini file
		ui_iterations = parser->getKeyAs<size_t>("TEST", "num_test_itrs");

		ui_generations = parser->getKeyAs<size_t>("POP", "generations");
		d_ER = parser->getKeyAs<double>("POP", "er");

		d_GA_CR = parser->getKeyAs<double>("GA", "cr");
		ui_GA_CP = parser->getKeyAs<size_t>("GA", "cp");
		d_GA_MR = parser->getKeyAs<double>("GA", "mr");
		d_GA_MRg = parser->getKeyAs<double>("GA", "mrg");
		d_GA_MP = parser->getKeyAs<double>("GA", "mp");
		
	} // end try
	catch (invalid_argument e)
	{
		delete parser;
		throw e; // handled above
	} // end catch

	b_invalid = false;

	delete parser;
} // end method initialize


bool Driver::isValid(void)
{
	return !b_invalid;
} // end method isValid


Driver::Driver(void)
{
	// initialize variables
	compute_start = highRes_Clock::now(),
	compute_end = highRes_Clock::now();
	time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	b_invalid = true;
} // end Default Constructor


Driver::Driver(string s_fileName) : Driver()
{
	// attempt to parse .ini file
	ifstream file(s_fileName.c_str(), ios::in);

	if (file.is_open() && !file.bad())
	{
		file.close();

		for (;;)
		{
			try
			{
				initialize(s_fileName);
				break;
			} // end try
			catch (invalid_argument e)
			{
				cout << "A required field was not found the file!" << endl;
				cout << e.what() << endl << endl;
				cout << "Try different file?" << endl;
				clearInput();
				char c = askUserYesNo();

				if (c == 'n')
				{
					return; // the object is in an invalid state
				} // end if

				s_fileName = askUserForFileName();

				if (b_stop)
				{
					return; // the object is in an invalid state
				} // end if
			} // end catch
		} // end forever
	} // end if
	else
	{
		file.close();

		for (;;)
		{
			cout << "The file \"" << s_fileName << "\" could not be opened." << endl;
			cout << "Try different file?" << endl;
			clearInput();
			char c = askUserYesNo();

			if (c == 'n')
			{
				return; // the object is in an invalid state
			} // end if

			s_fileName = askUserForFileName();

			if (b_stop)
			{
				return; // the object is in an invalid state
			} // end if

			try
			{
				initialize(s_fileName);
				break;
			} // end try
			catch (invalid_argument e)
			{
				cout << "An error occurred while parsing the ini file!" << endl;
				cout << "Error: " << e.what();
				cout << "Try different file?" << endl;
				char c = askUserYesNo();

				if (c == 'n')
				{
					return; // the object is in an invalid state
				} // end if
			} // end catch
		} // end forever
	} // end else

	b_invalid = false;
} // end Constructor 1


int Driver::run(void)
{
	if (b_invalid)
	{
		cout << "Parsing of the .ini file failed. Exiting ..." << endl;
		return EXIT_FAILURE; // ini file parsing was unsuccessful
	} // end if

	Test* test = new Test(ui_generations, ui_GA_CP, d_GA_CR, d_ER, d_GA_MR, d_GA_MRg, d_GA_MP);

	clearInput();

	cout << "Starting tests for Genetic Algorithm ..." << endl;

	compute_start = highRes_Clock::now(); // start timer for whole run

	test->RunGA(ui_iterations);

	compute_end = highRes_Clock::now();
	time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	cout << "Finished running tests for Genetic Algorithm." << endl;
	cout << "Time elapsed: " << time_to_compute.count() << " seconds." << endl << endl;


	delete test;

	return EXIT_SUCCESS;
} // end method run


string Driver::askUserForFileName(void)
{
	// Variables:
	string s_name = "";

	b_stop = false;

	for(;;)
	{
		cout << "Please enter the name of the .ini file: ";
		clearInput();
		getline(cin, s_name);

		if (s_name.length() > 0)
		{
				ifstream file(s_name, ios::in);

				if (!file.bad() && file.is_open())
				{
					file.close();
					return s_name;
				} // end if 
				else
				{
					file.close();
					cout << "The file \"" << s_name << "\" could not be opened." << endl;
					cout << "Try different file?" << endl;
					clearInput();
					char c = askUserYesNo();

					if (c == 'n')
					{
						b_stop = true;
						return "";
					} // end if
				} // end else
		} // end if (s_name.length() > 0)
		else
		{
			cout << "Invalid input!" << endl;
			cout << "Try again?" << endl;
			clearInput();
			char c = askUserYesNo();

			if (c == 'n')
			{
				cout << "Exiting ..." << endl;
				b_stop = true;
				return "";
			} // end if
		} // end else
	} // end forever

	return s_name;
} // end method askUserForFileName


void Driver::clearInput()
{
	cin.clear();
	cin.ignore(std::cin.rdbuf()->in_avail());
} // end method clearInput