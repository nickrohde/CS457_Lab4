#include "GA_Population.hpp" // class header

using namespace std;

GA_Population::GA_Population(const GA_Population & other) : Population(other)
{
	this->d_totalFitness = other.d_totalFitness;
	this->probabilities = other.probabilities;
} // end Copy Constructor


void GA_Population::evaluateAll(fitnessFunction f)
{
	b_isSorted = false;

	for (auto& g : genes)
	{
		g.evaluate(f);
	} // end for
} // end method evaluateAll


void GA_Population::findProbabilities()
{
	sort(); // ensure population is sorted

	double  d_worst = (genes[size() - 1].fitness() > abs(genes[0].fitness())) ? genes[size() - 1].fitness() : abs(genes[0].fitness()),
			d_offset = 0.0;

	// find total fitness of population
	for (auto& g : genes)
	{
		d_totalFitness += (d_worst - abs(g.fitness()));
	} // end for

	for (size_t i = 0; i < size(); i++)
	{
		// we are mapping the set of fitness values into the positive real numbers by subtracting all values
		// from the largest (worst) fitness value. This will result in the range [0,1]
		// the offset is the running total of probabilities, as the individual's fitness increases, it's probability 
		// decreases proportional to the best solution
		probabilities.push_back(d_offset + ((d_worst - abs(genes[i].fitness())) / d_totalFitness));
		d_offset = probabilities.at(i);
	} // end for

} // end method findProbabilities


std::size_t GA_Population::best(void)
{
	size_t	i = ceil(static_cast<double>(ui_size) / 2.0),
			ui_max = ui_size-2, // smallest index with a positive value
			ui_min = 0; // largest index with a negative value

	// list is sorted, manually check 0 as this is most likely the right one
	if ((*this)[0].fitness() == 0 || (*this)[0].fitness() > 0)
	{
		return 0;
	} // end if

	// binary search for 0 or closest positive value to 0
	while (ui_min != ui_max)
	{
		if ((*this)[i].fitness() == 0)
		{
			return i;
		} // end if
		if ((*this)[i - 1].fitness() < 0 && (*this)[i].fitness() > 0)
		{
			return i;
		} // end if
		if ((*this)[i].fitness() < 0 && (*this)[i+1].fitness() > 0)
		{
			return i;
		} // end if
		if ((*this)[i].fitness() < 0)
		{
			if (i > ui_max)
			{
				i = ui_max;
			} // end if
			else if (i > ui_min)
			{
				ui_min = i;
			} // end elif
			i = i + ceil(static_cast<double>(ui_max-ui_min) / 2.0);			
		} // end if
		if ((*this)[i].fitness() > 0)
		{
			if (i < ui_min)
			{
				i = ui_min;
			} // end if
			else if (i < ui_max)
			{
				ui_max = i;
			} // end elif
			i = i - ceil(static_cast<double>(ui_max - ui_min) / 2.0);			
		} // end if
	} // end while

	return i;
} // end method best


GA_Population & operator<<(GA_Population & pop, const Offspring * newGenes)
{
	for (auto& g : newGenes->offsprings)
	{
		pop << &g;
	} // end for

	return pop;
} // end operator<<(Population&, const Offspring *)
