#include "GA.hpp"				 // class header
#include "SelectionStrategy.hpp" // SelectionStrategy class

using namespace std;


int* geneticAlgorithm(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO)
{
	int	 i_best = std::numeric_limits<int>::max(),
	 	 i_temp;
	int* ip_data = new int[POP_INFO.ui_GENERATIONS+1];

	// initial population
	GA_Population* current = new GA_Population(POP_INFO.ui_SIZE, POP_INFO.ui_GENE_DIM, BOUNDS);
	duration compute_time;
	timePoint end = highRes_Clock::now();
	timePoint start = highRes_Clock::now();

	for (size_t i = 0; i < POP_INFO.ui_GENERATIONS; i++)
	{
		GA_Population* next_pop = new GA_Population();

		// find the fitness of the population and sort it
		current->evaluateAll(f);
		current->sort();

		i_temp = (*current)[current->best()].fitness();
		ip_data[i] = i_temp;

		// check if a new best was found
		if (i_temp >= 0 && i_best > i_temp)
		{
			i_best = i_temp;
		} // end if		

		// calculate probabilities for selecting an individual from the population
		current->findProbabilities();

		moveElite(current, next_pop, POP_INFO.d_ELITISM_RATE);

		// fill up the next population
		while(next_pop->size() < POP_INFO.ui_SIZE)
		{
			Parents* parents = SelectionStrategy::selectParents(*current);
			Offspring* offspring = crossingOver(parents->parent_A, parents->parent_B, CR_INFO);

			for(auto & g : offspring->offsprings)
			{
				g.mutate(MUT_INFO, BOUNDS);
				(*next_pop) << &g;
			} // end for 

			// pointers need to be manually deleted as Parents/Offspring does not know about Gene class
			delete parents->parent_A;
			delete parents->parent_B;
			delete parents;

			offspring->offsprings.clear();
			delete offspring;
		} // end for 

		delete current;
		current = next_pop;
	} // end for

	end = highRes_Clock::now();

	compute_time = std::chrono::duration_cast<duration>(end - start);

	// find final solution
	current->evaluateAll(f);
	current->sort();

	i_temp = (*current)[current->best()].fitness();
	ip_data[POP_INFO.ui_GENERATIONS] = i_temp;

	// check if a new best was found
	if (i_temp >= 0 && i_best > i_temp)
	{
		i_best = i_temp;
	} // end if	

	cout << "Time to compute results: " << compute_time.count() << endl;
	cout << "Best solution found: " << i_best << endl;

	delete current;

	return ip_data;
} // end method geneticAlgorithm


void moveElite(const GA_Population * old_pop, GA_Population * new_pop, const double ER)
{
	// find number of elite individuals
	size_t elite = static_cast<size_t>(static_cast<double>(old_pop->size()) * ER);

	for (size_t i = 0; i < elite; i++)
	{
		(*new_pop) << &((*old_pop)[i]);
	} // end for
} // end method moveElite


Offspring* crossingOver(const Gene* PARENT_A, const Gene* PARENT_B, const Crossing_Over_Info& CO_INFO)
{
	Offspring* res = new Offspring();

	// getRandomNumberInRage returns a number in range [a,b), thus we need to add a little bit to b to make it range [0,1]
	if (getRandomRealInRange<double>(0.0, (1.0 + numeric_limits<double>::min())) < CO_INFO.d_CROSSING_OVER_RATE)
	{
			res->offsprings.push_back(Gene(*PARENT_A, *PARENT_B, CO_INFO.ui_CROSSING_OVER_POINTS));
			res->offsprings.push_back(Gene(*PARENT_A, *PARENT_B, CO_INFO.ui_CROSSING_OVER_POINTS));
	} // end if
	else
	{
		res->offsprings.push_back((*PARENT_A));
		res->offsprings.push_back((*PARENT_B));
	} // end else

	return res;
} // end method crossingOver

