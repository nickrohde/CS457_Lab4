#pragma once

#ifndef _GENETIC_ALG_H
#define _GENETIC_ALG_H

#include "MasterInclude.hpp"
#include "GA_Population.hpp"

#define NUM_OFFSPRING 2

/// <summary>
///			 Finds the optimal solution to <paramref name="f"/> by generating an initial population and then generating new populations 
///			 based on the previous one until a certain number of generations have been created.
/// </summary>
/// <param name="f">The cost function to optimize.</param>
/// <param name="POP_INFO">Various info about the population, such as size, gene size, etc.</param>
/// <param name="BOUNDS">The upper and lower problem bounds.</param>
/// <param name="MUT_INFO">The rate, precision, and range at which mutations occur.</param>
/// <param name="CR_INFO">The rate, number of offsprings, and number of points for crossing over.</param>
/// <returns>The optimal solution to <paramref name="f"/> found after the given number of generations.</returns>
int* geneticAlgorithm(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO);

/// <summary>Moves the elite individuals from the old population into the new population.</summary>
/// <param name="old_pop">The old population containing the elite.</param>
/// <param name="new_pop">The population to move the elite to.</param>
/// <param name="ER">The elitism rate that the determines how many individuals are considered elite.</param>
void moveElite(const GA_Population* old_pop, GA_Population* new_pop, const double ER);



#endif 
