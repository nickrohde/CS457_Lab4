#include "Containers.hpp" // class header

using namespace std;


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


Mutation_Info::Mutation_Info(void)
{
	d_rate = d_precision = d_range = 0;
} // end Default Constructor


Mutation_Info::Mutation_Info(double rate, double range, double prec)
{
	if (rate < 0.0 || rate > 1.0)
	{
		throw out_of_range("Mutation rate must be in range [0,1].");
	} // end if;

	d_rate = rate; d_range = range; d_precision = prec;
} // end Constructor


Mutation_Info::Mutation_Info(const Mutation_Info & OTHER)
{
	d_precision = OTHER.d_precision;
	d_range = OTHER.d_range;
	d_rate = OTHER.d_rate;
} // end Copy Constructor


void Mutation_Info::operator=(const Mutation_Info & OTHER)
{
	d_precision = OTHER.d_precision;
	d_range = OTHER.d_range;
	d_rate = OTHER.d_rate;
} // end operator=


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


Crossing_Over_Info::Crossing_Over_Info(void)
{
	ui_CROSSING_OVER_POINTS = 0;
	d_CROSSING_OVER_RATE = 0.0;
} // end Default Constructor


Crossing_Over_Info::Crossing_Over_Info(std::size_t points, double rate)
{
	ui_CROSSING_OVER_POINTS = points;
	d_CROSSING_OVER_RATE = rate;
} // end Constructor 3


void Crossing_Over_Info::operator=(const Crossing_Over_Info & OTHER)
{
	ui_CROSSING_OVER_POINTS = OTHER.ui_CROSSING_OVER_POINTS;
	d_CROSSING_OVER_RATE = OTHER.d_CROSSING_OVER_RATE;
} // end operator=


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


Population_Info::Population_Info(void)
{
	ui_GENERATIONS = ui_GENE_DIM = ui_SIZE = 0;
	d_ELITISM_RATE = 0.0;
} // end Default Constructor


Population_Info::Population_Info(std::size_t size, std::size_t dim, std::size_t gen, double ER)
{
	ui_SIZE = size;
	ui_GENE_DIM = dim;
	ui_GENERATIONS = gen;
	d_ELITISM_RATE = ER;
} // end Constructor 6


void Population_Info::operator=(const Population_Info & OTHER)
{
	ui_SIZE = OTHER.ui_SIZE;
	ui_GENE_DIM = OTHER.ui_GENE_DIM;
	ui_GENERATIONS = OTHER.ui_GENERATIONS;
	d_ELITISM_RATE = OTHER.d_ELITISM_RATE;
} // end operator=

