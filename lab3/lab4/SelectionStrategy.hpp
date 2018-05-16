#pragma once

#ifndef _SELECTION_STRAT_H
#define _SELECTION_STRAT_H

#include "MasterInclude.hpp"
#include "GA_Population.hpp"

/// <summary>Wrapper class for selection strategies.</summary>
class SelectionStrategy
{
public:
	/// <summary>Types of selection strategies.</summary>
	enum StrategyType
	{
		Tournament,
		Roulette,
		Rank,
		SteadyState
	}; // end enum Type

	/// <summary>Selects two parents from the population <paramref name="pop"/> using strategy <paramref name="t"/>.</summary>
	/// <param name="pop">The population to select parents from.</param>
	/// <param name="t">(Optional) The strategy to use. DEFAULT: Roulette</param>
	/// <returns>A parent structure with two pointers to two genes in the population <paramref name="pop"/>.</returns>
	static Parents* selectParents(const GA_Population& pop, StrategyType t = StrategyType::Roulette);

private:
	/// <summary>Selects a parent from the population <paramref name="pop"/> using the tournament selection strategy.</summary>
	/// <param name="pop">The population to select parents from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static std::size_t tournament(const GA_Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the roulette selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static std::size_t roulette(const GA_Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the rank selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static std::size_t rank(const GA_Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the steady-state selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static std::size_t steadyState(const GA_Population& pop);

}; // end Class SelectionStrategy

#endif // !_SELECTION_STRAT_H
