#include "SelectionStrategy.hpp" // class header

using namespace std;


typedef function<size_t(const GA_Population&)> StrategyFunction;


Parents* SelectionStrategy::selectParents(const GA_Population& pop, StrategyType t)
{
	Parents* p = new Parents();
	StrategyFunction f;

	switch (t)
	{
	case SelectionStrategy::StrategyType::Roulette:
		f = roulette;
		break;
	case SelectionStrategy::StrategyType::Rank:
		f = rank;
		break;	
	case SelectionStrategy::StrategyType::SteadyState:
		f = steadyState;
		break;
	case SelectionStrategy::StrategyType::Tournament:
		f = tournament;
		break;
	default:
		throw invalid_argument("Invalid type received by selectParents.");
	} // end switch

	size_t	P1 = f(pop),
			P2 = f(pop);

	// ensure parents are unique
	while (P1 == P2)
	{
		P1 = f(pop);
	} // end while

	p->parent_A = new Gene(pop[P1]);
	p->parent_B = new Gene(pop[P2]);

	return p;
} // end method selectParents


std::size_t SelectionStrategy::tournament(const GA_Population & pop)
{
	throw std::logic_error("Not Implemented");
} // end method tournament


std::size_t SelectionStrategy::roulette(const GA_Population & pop)
{
	// our random number is in the range [0, 1]
	double	d_rand = getRandomRealInRange<double>(0.0, (1.0 + std::numeric_limits<double>::min()));

	for (size_t i = 1; i < pop.probabilities.size(); i++)
	{
		// if probability[i] <= rand < probability[i+1], the individual i was selected
		// if probability[size] <= rand <= sum_probabilities, the last individual was selected
		if (pop.probabilities.at(i) > d_rand)
		{
			return (i - 1);
		} // end if
	} // end for

	return (pop.probabilities.size() - 1);
} // end method roulette


std::size_t SelectionStrategy::rank(const GA_Population & pop)
{
	throw std::logic_error("Not Implemented");
} // end method rank


std::size_t SelectionStrategy::steadyState(const GA_Population & pop)
{
	throw std::logic_error("Not Implemented");
} // end method steadyState

