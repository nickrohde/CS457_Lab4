#include "MasterInclude.hpp" // everything that could possibly be needed
#include "GA.hpp"
#include "Containers.hpp"

#define DEBUG 0

using namespace std;



/// <summary>Program entry point.</summary> 
/// <param name="argc">Number of command line arguments passed to main.</param>
/// <param name="argv">Array of string containing the name of a ini file to parse, or nothing.</param>
/// <returns>0 on successful execution, 1 otherwise.</returns>
int main(int argc, char ** argv)
{
	const Bounds BOUNDS(-512, 512);
	const Crossing_Over_Info CO_INFO(4, 0.75);
	const Mutation_Info MUT_INFO(0.1, 25.0, 0.86);
	const Population_Info POP_INFO(50, 2, 100, 0.1);

	int* ip_results = geneticAlgorithm([](const std::vector<int>& vect) -> int { return (vect[0] - (2 * vect[1])); }, POP_INFO, BOUNDS, MUT_INFO, CO_INFO);

	ofstream file("results.txt", ios::app | ios::out);

	if (file.is_open() && !file.bad())
	{
		for (size_t i = 0; i <= POP_INFO.ui_GENERATIONS; i++)
		{
			file << ip_results[i];
		
			if (i < POP_INFO.ui_GENERATIONS)
			{
				file << ", ";
			} // end if
			else
			{
				file << "\n";
			} // end else
		} // end for
	} // end if

	delete[] ip_results;

	file.close();

	return 0;
} // end Main

