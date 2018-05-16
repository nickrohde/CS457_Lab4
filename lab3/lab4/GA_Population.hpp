#pragma once

#ifndef _GA_POP_H
#define _GA_POP_H

#include "MasterInclude.hpp"
#include "Population.hpp"

///<summary><see cref="Population"/> specific to Genetic Algorithm.</summary>
class GA_Population : public Population
{
public:
	// Constructors:
	/// <summary>Constructs an empty population for the Genetic Algorithm.</summary>
	/// <remarks>There is nothing this constructor must deal with, thus, it is empty.</remarks>
	GA_Population(void) : Population() { d_totalFitness = 0; }

	/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
	/// <param name="ui_SIZE">The size of the population.</param>
	/// <param name="ui_DIM">The size of each gene in the population.</param>
	/// <param name="bounds">The min/max value that may be stored in a gene.</param>
	/// <remarks>There is nothing this constructor must deal with, thus, it is empty.</remarks>
	GA_Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& bounds) : Population(ui_SIZE, ui_DIM, bounds) { d_totalFitness = 0; }

	/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
	/// <param name="other">The population to copy.</param>
	GA_Population(const GA_Population& other);

	// Destructor:
	/// <summary>Releases all dynamic memory owned by this object.</summary>
	~GA_Population(void) {	probabilities.clear(); } 

	// Operations:
	/// <summary>Finds the fitness of all members of the population and calculates the total fitness of the population.</summary>
	/// <param name="f">The fitness function to evaluate the population on.</param>
	virtual void evaluateAll(fitnessFunction f);

	/// <summary>Determines the propability distribution for this population by mapping the fitness values into the positive reals.</summary>
	void findProbabilities(void);

	/// <summary>Helper for recursive version.</summary>
	/// <returns>Index of smallest positive fitness value in the population, or size of population if no such value exists.</returns>
	std::size_t best(void);


	// Friend Declarations:
	/// <remarks>The selection strategy requires access to the probabilities stored in the population. This allows efficient access.</remarks>
	friend class SelectionStrategy;

	/// <remarks>Move elite needs to remove old members of the population.</remarks>
	friend void moveElite(const GA_Population * old_pop, GA_Population * new_pop, const double ER);

	/// <summary>Inserts the genes <paramref name="newGenes"/> into this population.</summary>
	/// <param name="pop">The population to insert <paramref name="newGenes"/> into.</param>
	/// <param name="newGenes">The new genes that will be added to this population.</param>
	/// <remarks>All genes to be added must be compatible, i.e. of the same length as the genes already in this population.</remarks>
	/// <exception name="std::invalid_argument">Thrown if any gene in <paramref name="newGenes"/> is not the same length as all other genes in this population.</exception>
	friend GA_Population& operator<<(GA_Population& pop, const Offspring* newGenes);

private:
	// Private Data Members:
	/// <summary>The total fitness of all members of this population</summary>
	double d_totalFitness;

	/// <summary>Parallel vector to the outer vector of genes, containing the probability an individual is selected by the roulette rule.</summary>
	std::vector<double> probabilities;

}; // end Class GA_Population



#endif // !_GA_POP_H
