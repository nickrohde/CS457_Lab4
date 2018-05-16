#include "Test.hpp"				// class header
#include "GA.hpp"				// GA

#define NUM_THREADS 16
#define DIM 2

using namespace std;


Test::Test(const std::size_t ui_generations, const std::size_t ui_crossPoints, const std::size_t ui_popSize, const double d_crossRate,	const double d_elitismRate, 
			const double d_mutationRate, const double d_mutationRange, const double d_mutationPrecision, const int i_min, const int i_max)
{
	mutInfo = Mutation_Info(d_mutationRate, d_mutationRange, d_mutationPrecision);
	CO_Info = Crossing_Over_Info(ui_crossPoints, d_crossRate);
	popInfo = Population_Info(ui_popSize, DIM, ui_generations, d_elitismRate);
	bounds  = Bounds(i_min, i_max);
	
	compute_start = compute_end = highRes_Clock::now();
} // end Constructor 4


Test::~Test(void)
{

} // end Destructor


void Test::RunGA(size_t ui_iterations, size_t ui_strat, FitnessFunction f)
{
	// Locals Variables:
	results_t* res;
	int i = 0;

	double ** dp_data = new double*[ui_iterations];

	compute_start = highRes_Clock::now();

#pragma omp parallel for private(i) num_threads(NUM_THREADS)
	for (; i < ui_iterations; i++)
	{
		res = geneticAlgorithm(f, popInfo, bounds, mutInfo, CO_Info);

		for (size_t j = 0; j < popInfo.ui_GENERATIONS; j++)
		{
			data[k] = std::move(res->)
		} // end for j

		delete res;
	} // end for i

	compute_end = highRes_Clock::now();

	time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);
	std::cout << "Overall time of test: " << time_to_compute.count() << endl;
}


void Test::dumpDataToFile(string s_name, results_t* res)
{
	ofstream file(s_name, ios::out | ios::app);

	if (!file.bad() && file.is_open())
	{
		file << res->d_bestValue << "\n";
	} // end if

	file.close();
} // end dumpDataToFile


void Test::writeResultsToFile(results_t* res)
{
	ofstream file("results.csv", ios::out | ios::app);

	if (!file.bad() && file.is_open())
	{
		file << *res;
	} // end if

	file.close();
} // end method 


string Test::makeFileName(size_t ui_dim, int i_functionNumber)
{
	stringstream name;

	name << "DE3_" << ui_dim << "_f" << (i_functionNumber + 1) << ".csv" ;

	return name.str();
}


