#include "Gene.hpp" // class header

using namespace std;


Gene::Gene(const size_t ui_SIZE, const Bounds& BOUNDS)
{
	ui_length = ui_SIZE;

	for (size_t i = 0; i < ui_length; i++)
	{
		gene.push_back(getRandomIntInRange<int>(BOUNDS.i_min, BOUNDS.i_max));
	} // end for
} // end Constructor 3

void Gene::evaluate(fitnessFunction f)
{
	i_fitness = f(gene);
} // end method evaluate


Gene::Gene(const Gene& PARENT_A, const Gene& PARENT_B, std::size_t ui_CO_POINTS)
{
	ui_length = PARENT_A.length();

	vector<size_t> indeces;

	for (size_t i = 0; i < ui_CO_POINTS; i++)
	{
		indeces.push_back(getRandomIntInRange<size_t>(0, PARENT_A.length() - 1));
	} // end for

	// order cross over points
	std::sort(indeces.begin(), indeces.end());

	// add the end of the gene to the indeces as we need to copy the whole gene
	indeces.push_back(ui_length);

	recombine(PARENT_A, PARENT_B, &indeces);

	indeces.clear();
} // end Constructor 3


Gene::Gene(const Gene& other)
{
	ui_length = other.length();

	for (auto& d : other.gene)
	{
		gene.push_back(d);
	} // end foreach

	i_fitness = other.i_fitness;
} // end Copy Constructor


void Gene::mutate(const Mutation_Info& MUT_INFO, const Bounds& BOUNDS)
{
	for (auto& val : gene)
	{
		// getRandomRealInRage returns a number in range [a,b), thus we need to add a little bit to b to make the range [a,b]
		if (getRandomRealInRange<double>(0.0, (1.0 + std::numeric_limits<double>::min())) < MUT_INFO.d_rate)
		{
			int temp = (BOUNDS.i_max - BOUNDS.i_min) * MUT_INFO.d_range * pow((-1.0 * getRandomRealInRange<double>(0.0, 1.0) * MUT_INFO.d_precision), 2.0);

			// randomly pick the sign of the mutation
			val += (getRandomIntInRange<int>(0, 1) % 2) ? (temp * -1) : (temp);
		} // end if

		// ensure this mutation did not go out of bounds
		while (val > BOUNDS.i_max)
		{
			val = (val - BOUNDS.i_max);
		} // end while
		while (val < BOUNDS.i_max)
		{
			val = (val - BOUNDS.i_max);
		} // end while
	} // end foreach
} // end method mutate


inline size_t Gene::length(void) const
{
	return ui_length;
} // end method length


int& Gene::operator[](const size_t i)
{
	if (i >= ui_length)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return gene.at(i);
} // end operator[]


int Gene::operator[](const size_t i) const
{
	if (i >= ui_length)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return gene.at(i);
} // end operator[]

 
void Gene::recombine(const Gene & PARENT_A, const Gene & PARENT_B, const std::vector<size_t>* indeces)
{
	// this binary string is the template for the new gene
	// 0 means take from parent a, 1 means take from parent b
	vector<size_t>* distribution = getRandomBinaryString<size_t>(indeces->size());

	// indeces we are compying
	size_t	start = 0,
			end = 0;

	// iterate over all cross-over points
	for (size_t j = 0; j < distribution->size(); j++)
	{
		start = end;
		end = indeces->at(j);

		// pointer to current parent to avoid redundant code
		const Gene* temp = (distribution->at(j) == 0) ? (&PARENT_A) : (&PARENT_B);

		// do the cross over for all parts in the current region
		for (size_t k = start; k < end; k++)
		{
			gene.push_back(temp->gene.at(k));
		} // end for k
	} // end for j

	delete distribution;
} // end method recombine


std::ostream& operator<<(std::ostream& stream, const Gene& gene)
{
	if (gene.length() > 0)
	{
		stream << gene[0];

		for (size_t i = 1; i < gene.length(); i++)
		{
			stream << ", " << gene[i];
		} // end for

		stream << endl;
	} // end if

	return stream;
} // end operator<<

  // Relational Operators:

inline bool operator==(const Gene & LHS, const Gene & RHS)
{
	return LHS.i_fitness == RHS.i_fitness;
} // end operator>


  /// <summary>Determines if the fitness of gene <paramref name="LHS"/> is less than or equal to that of gene <paramref name="RHS"/>.</summary>
  /// <param name="LHS">The LHS argument.</param>
  /// <param name="RHS">The RHS argument.</param>
  /// <returns>True if the fitness of <paramref name="LHS"/> is less than or equal to that of <paramref name="RHS"/>, otherwise false.</returns>
inline bool operator<=(const Gene & LHS, const Gene & RHS)
{
	return (LHS < RHS || LHS == RHS);
} // end operator<


  /// <summary>Determines if the fitness of gene <paramref name="LHS"/> unequal to that of gene <paramref name="RHS"/>.</summary>
  /// <param name="LHS">The LHS argument.</param>
  /// <param name="RHS">The RHS argument.</param>
  /// <returns>True if the fitness of <paramref name="LHS"/> is unequal to that of <paramref name="RHS"/>, otherwise false.</returns>
inline bool operator!=(const Gene & LHS, const Gene & RHS)
{
	return !(LHS == RHS);
} // end operator>


  /// <summary>Determines if the fitness of gene <paramref name="LHS"/> is greater than that of gene <paramref name="RHS"/>.</summary>
  /// <param name="LHS">The LHS argument.</param>
  /// <param name="RHS">The RHS argument.</param>
  /// <returns>True if the fitness of <paramref name="LHS"/> is greater than that of <paramref name="RHS"/>, otherwise false.</returns>
inline bool operator>(const Gene & LHS, const Gene & RHS)
{
	return !(RHS <= LHS);
} // end operator>


  /// <summary>Determines if the fitness of gene <paramref name="LHS"/> is greater than or equal to that of gene <paramref name="RHS"/>.</summary>
  /// <param name="LHS">The LHS argument.</param>
  /// <param name="RHS">The RHS argument.</param>
  /// <returns>True if the fitness of <paramref name="LHS"/> is greater than or equal to that of <paramref name="RHS"/>, otherwise false.</returns>
inline bool operator>=(const Gene & LHS, const Gene & RHS)
{
	return !(LHS < RHS);
} // end operator>
