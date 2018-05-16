#pragma once

#ifndef _TEST_H
#define _TEST_H

#include "MasterInclude.hpp"
#include "Containers.hpp"		// GA/DE structs
#include "results.hpp"			// results_t

typedef std::function<double(const double, const double)> FitnessFunction;

/// <summary>Class that handles testing of the optimization strategies.</summary>
class Test
{
public:
	/// <summary>Constructor taking 4 arguements.</summary>
	/// <param name="ui_dimMin">Starting dimension for tests (inclusive; must be positive integer and strictly smaller than <paramref name="ui_dimMax"/>).</param>
	/// <param name="ui_dimMax">Ending dimension for tests (inclusive; must be positive integer and strictly greater than <paramref name="ui_dimMin"/>).</param>
	/// <param name="ui_dimDelta">Dimension increase step size (must be positive integer).</param>
	/// <param name="b_storeData">Whether or not to generate data files.</param>
	/// <param name="ui_generations">Number of generations to run DE/GA.</param>
	Test(const std::size_t ui_generations, const std::size_t ui_crossPoints, const std::size_t ui_popSize, const double d_crossRate, const double d_elitismRate,
			const double d_mutationRate, const double d_mutationRange, const double d_mutationPrecision, const int i_min, const int i_max);

	/// <summary>Destructor. Frees all dynamic memory beloging to this object.</summary>
	~Test(void);

	/// <summary>Runs GA to optimize all cost functions.</summary>
	/// <param name="ui_iterations">Number of iterations to run DE.</param>
	/// <param name="MR">Mutation rate.</param>
	/// <param name="MRg">Mutation Range.</param>
	/// <param name="MP">Mutation precision.</param>
	/// <param name="CP">Crossover points.</param>
	/// <param name="CR">Crossover rate.</param>
	/// <param name="ER">Elitism rate.</param>
	void RunGA(std::size_t ui_iterations, std::size_t ui_strat, FitnessFunction f);

#pragma region Private
private:
	// Member Variables:
	Crossing_Over_Info CO_Info;
	Population_Info popInfo;
	Mutation_Info mutInfo;
	Bounds bounds;


	/// <summary>Used for timing tests.</summary>
	timePoint	compute_start,
				compute_end;
	duration	time_to_compute;

	// Private Functions:
	/// <summary>Generates data file with test data.</summary>
	/// <param name="s_name">Name of the file to dump the data into.</param>
	/// <param name="res">A pointer to a results_t object containing the data to dump.</param>
	/// <remarks>This function is only called if b_storeData is set to true. The files created tend to be very large.</remarks>
	void dumpDataToFile(std::string s_name, results_t* res);

	/// <summary>Generates results file with test results.</summary>
	/// <param name="res">A pointer to a results_t object containing the test results.</param>
	/// <remarks>This function only writes the optimal point and solution to the file, all other data is ignored.</remarks>
	void writeResultsToFile(results_t* res);

	/// <summary>Generates a file name. Name will be generated as "data_[<paramref name="ui_dim"/>]_f[<paramref name="i_functionNumber"/>]".</summary>
	/// <param name="ui_dim">Dimension to insert into the name.</param>
	/// <param name="i_functionNumber">Function number to insert into the name.</param>
	std::string makeFileName(std::size_t ui_dim, int i_functionNumber);

#pragma endregion

}; // end Class Test

#endif // !_TEST_H
