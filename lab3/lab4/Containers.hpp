#pragma once

#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "MasterInclude.hpp"

class Gene; // let the compiler know the class Gene exists


///<summary>Container for Parents.</summary>
struct Parents
{
	Gene* parent_A;
	Gene* parent_B;
}; // end Struct Parents


///<summary>Stores the offspring after a crossover.</summary>
struct Offspring
{
	/// <summary>Vector containing the genes that are offsprings of the parents.</summary>
	std::vector<Gene> offsprings;
}; // end Struct Offspring


/// <summary>Stores the problem bounds.</summary>
struct Bounds
{
	/// <summary>Lower bound.</summary>
	int		i_min, 
	/// <summary>Upper bound.</summary>
			i_max;

	Bounds(void) { i_min = i_max = 0; }
	
	Bounds(const int min, const int max)
	{
		i_min = min;
		i_max = max;
	} // end Constructor
}; // end Struct Bounds


/// <summary>Stores the mutation information.</summary>
struct Mutation_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Mutation_Info(void);

	/// <summary>Constructs a new structure containing the given values.</summary>
	/// <param name="rate">The rate at which mutations occur.</param>
	/// <param name="range">The range for mutations.</param>
	/// <param name="prec">The precision of mutations.</param>
	Mutation_Info(double rate, double range, double prec);

	/// <summary>Copy constructor.</summary>
	/// <param name="OTHER">The Mutation_Info to copy into this.</param>
	Mutation_Info(const Mutation_Info& OTHER);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Mutation_Info& OTHER);

	double	d_rate,
			d_range,
			d_precision;
}; // end struct Mutation_Info


   /// <summary>Stores the crossing-over information.</summary>
struct Crossing_Over_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Crossing_Over_Info(void);

	/// <summary>Constructs a structure with the given values.</summary>
	/// <param name="points">Number of crossing-points to generate.</param>
	/// <param name="rate">Chance of crossing-over to occur.</param>
	Crossing_Over_Info(std::size_t points, double rate);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Crossing_Over_Info& OTHER);

	/// <summary>The number of cross-over points to generate.</summary>
	std::size_t	ui_CROSSING_OVER_POINTS;

	/// <summary>The chance for crossing-over to occur.</summary>
	double		d_CROSSING_OVER_RATE;
};


/// <summary>Stores the population information.</summary>
struct Population_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Population_Info(void);

	/// <summary>Constructs a structure with the given values.</summary>
	/// <param name="size">Size of population.</param>
	/// <param name="dim">Length of genes.</param>
	/// <param name="gen">Number of generations to run.</param>
	/// <param name="ER">Elitism rate.</param>
	Population_Info(std::size_t size, std::size_t dim, std::size_t gen, double ER);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Population_Info& OTHER);

	/// <summary>Size of the population.</summary>
	std::size_t ui_SIZE,

	/// <summary>Gene length for population members.</summary>
				ui_GENE_DIM,

	/// <summary>Number of generations to run.</summary>
				ui_GENERATIONS;

	/// <summary>The elitism rate.</summary>
	double		d_ELITISM_RATE;
}; // end Struct Population Info

#endif // !_CONTAINER_H