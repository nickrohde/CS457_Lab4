#include "Population.hpp" // class header

using namespace std;

Population::Population(void)
{
	ui_size = 0;
	b_isSorted = false;
} // end Default Constructor


Population::Population(const size_t ui_SIZE, const size_t ui_DIM, const Bounds& BOUNDS)
{
	ui_size = ui_SIZE;
	b_isSorted = false;
	bounds = BOUNDS;

	genes = GenePool(ui_SIZE);

	for (size_t i = 0; i < ui_size; i++)
	{
		genes[i] = Gene(ui_DIM, BOUNDS);
	} // end for
} // end Constructor 4

void Population::sort(void)
{
	if (!b_isSorted) // only sort if needed
	{
		b_isSorted = true;

		vector_quickSort(genes.begin(), genes.end());
	} // end if
} // end method sort


Population::Population(const Population & other)
{
	ui_size = other.ui_size;
	b_isSorted = other.b_isSorted;

	std::copy(other.genes.begin(), other.genes.end(), genes.begin());
} // end Copy Constructor


inline Gene& Population::operator[](const size_t i)
{
	if (i >= ui_size)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return genes.at(i);
} // end operator[]


inline Gene Population::operator[](const size_t i) const
{
	if (i >= ui_size)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return genes.at(i);
} // end operator[]


ostream& operator<<(ostream& stream, const Population& pop)
{
	stream << endl;

	for (auto& g : pop.genes)
	{
		stream << g << endl;
	} // end for

	return stream;
} // end operator<<


Population & operator<<(Population & pop, const Gene * newGene)
{
	pop.b_isSorted = false;

	if (pop.genes.size() > 0)
	{
		if (newGene->length() != pop.genes.at(0).length())
		{
			throw invalid_argument("New genes are not of the same size as genes in population.");
		} // end if
	} // end if

	pop.genes.push_back(*newGene);
	pop.ui_size++;

	return pop;
} // end operator<<(Population &, const Gene *)