#pragma once

#ifndef _UTILITY_H
#define _UTILITY_H

#pragma region Includes
#include "MasterInclude.hpp"
#pragma endregion


#pragma region Defines
///<summary>Math constants.</summary>
#ifndef _MATH_CONSTANTS_
#define _MATH_CONSTANTS_
/// <summary>Pi</summary>
#ifndef _PI
#define _PI 3.141592653589793238462643383279
#endif // !_PI

/// <summary>E</summary>
#ifndef _E
#define _E  2.718281828459045235360287471352
#endif // !_E

///<summary>The double value 1 plus the minimum double value. This allows the range [0,1) to be turned into [0,1].</summary>
#ifndef _ONE
#define _ONE (1.0 + numeric_limits<double>::min())
#endif // !_ONE
#endif

/// <summary>Return values.</summary>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif // !EXIT_SUCCESS

/// <summary>Null</summary>
#ifndef NULL
#define NULL 0
#endif

/// <summary>Checks whether n elements are unique using bitwise xor.</summary>
#ifndef _UNIQUE_
#define _UNIQUE_
#define UNIQUE_3(a,b,c)         ((a^b) && (a^c) && (b^c))
#define UNIQUE_4(a,b,c,d)       (UNIQUE_3(a,b,c) && (a^d) && (b^d) && (c^d))
#define UNIQUE_5(a,b,c,d,e)     (UNIQUE_4(a,b,c,d) && (a^e) && (b^e) && (c^e) && (d^e))
#define UNIQUE_6(a,b,c,d,e,f)   (UNIQUE_5(a,b,c,d,e) && (a^f) && (b^f) && (c^f) && (d^f) && (e^f))
#define UNIQUE_7(a,b,c,d,e,f,g) (UNIQUE_6(a,b,c,d,e,f) && (a^g) && (b^g) && (c^g) && (d^g) && (e^g) && (f^g))
#endif

#ifndef _QS_DEFS_
#define _QS_DEFS_
#define SWITCH_TO_IS 16 // list size at which we swap to IS
#define SWITCH_TO_HS 50 // recursion depth at which we swap to HS
#endif


#pragma endregion


#pragma region Typedefs
/// <summary>Typedefs for convenience.</summary>
typedef unsigned int uint;
typedef std::chrono::high_resolution_clock::time_point	timePoint;
typedef std::chrono::duration<double>					duration;
typedef std::chrono::high_resolution_clock				highRes_Clock;
#pragma endregion


/// <summary>Gets a random number in the given range using a mersenne twister.</summary>
/// <typeparam name="T">Some std::RealType.</typeparam>
/// <param name="p_MIN">Pointer to the minimum value of the range.</param>
/// <param name="p_MAX">Pointer to the maximum value of the range.</param>
/// <returns>A random number between <paramref name="p_MIN"/> and <paramref name="p_MAX"/> (inclusive-exclusive).</returns>
template <typename T>
inline T getRandomRealInRange(const T p_MIN, const T p_MAX)
{
	static std::random_device rd{};
	static std::mt19937 engine{ rd() };
	std::uniform_real_distribution<T> dist{ p_MIN, p_MAX };

	return dist(engine);
} // end template getRandomNumberInRange


/// <summary>Gets a random number in the given range using a mersenne twister.</summary>
/// <typeparam name="T">Some std::IntType or std::UIntType.</typeparam>
/// <param name="p_MIN">Pointer to the minimum value of the range.</param>
/// <param name="p_MAX">Pointer to the maximum value of the range.</param>
/// <returns>A random number between <paramref name="p_MIN"/> and <paramref name="p_MAX"/> (both inclusive).</returns>
template <typename T>
inline T getRandomIntInRange(const T MIN, const T MAX)
{
	static std::random_device rd{};
	static std::mt19937 engine{ rd() };
	std::uniform_int_distribution<T> dist{ MIN, MAX };

	return dist(engine);
} // end template getRandomNumberInRange


/// <summary>Generates a random permutation of <paramref name="numbers"/> of length <paramref name="M"/> and stores this in <paramref name="results"/>.</summary>
/// <typeparam name="T">The type of <paramref name="numbers"/> and <paramref name="results"/>.</typeparam>
/// <param name="numbers">The list of things to generate a permutation from.</param>
/// <param name="N">The length of <paramref name="numbers"/>.</param>
/// <param name="results">The list to store the permutation in.</param>
/// <param name="M">The length of the permutation to generate.</param>
/// <param name="excluded">A value that should not be included in the permutation.</param>
/// <remarks>The order of <paramref name="numbers"/> will be changed by this function.</remarks>
template <typename T>
void genPermutation(T* numbers, std::size_t N, T* results, const std::size_t M, const T excluded)
{
	static std::random_device rd{};
	static std::mt19937 engine{ rd() };

	// randomly shuffle the array elements around
	for (size_t i = 0; i < M+1; i++) 
	{
		size_t j = getRandomIntInRange<size_t>(i, N-1);
		auto temp = numbers[i]; 
		numbers[i] = numbers[j];
		numbers[j] = temp;
	} // end for
	// get the permutation from the first n indeces
	for (size_t i = 0, j = 0; j < M; i++)
	{
		if (numbers[i] != excluded)
		{
			results[j] = numbers[i];
			j++;
		} // end if
	} // end for
} // end template genPermutation


/// <summary>Gets a vector of specified size with random values.</summary>
/// <typeparam name="T">Type that the mersenne twister can generate.</typeparam>
/// <param name="ui_SIZE">Size of the vector.</param>
/// <param name="p_MIN">Pointer to the minimum value of the range.</param>
/// <param name="p_MAX">Pointer to the maximum value of the range.</param>
/// <returns>A vector containing <paramref name="ui_SIZE"/> random numbers between <paramref name="p_MIN"/> and <paramref name="p_MAX"/> (both inclusive).</returns>
template <typename T>
std::vector<T>* getRandomVector(const std::size_t ui_SIZE, const T p_MIN, const T p_MAX)
{
	std::vector<T>* vec = new std::vector<T>(ui_SIZE);

	for (std::size_t i = 0; i < ui_SIZE; i++)
	{
		vec->at(i) = (getRandomNumberInRange(p_MIN, p_MAX));
	} // end for

	return vec;
} // end template getRandomVector


  /// <summary>Gets a vector of size <paramref name="ui_LENGTH"/> that contains a random binary string.</summary>
  /// <typeparam name="T">A numeric type that implements operator%.</typeparam>
  /// <param name="ui_LENGTH">The number of 'bits' to generate.</param>
  /// <returns>A pointer to a vector containing a random binary string.</returns>
template <typename T>
inline std::vector<T>* getRandomBinaryString(const std::size_t ui_LENGTH)
{
	std::vector<T>* vec = new std::vector<T>();

	for (std::size_t i = 0; i < ui_LENGTH; i++)
	{
		vec->push_back(getRandomIntInRange<T>(0, 2) % 2);
	} // end for

	return vec;
} // end template getRandomBinaryString


/// <summary>Calculates the standard deviation of the given set.</summary>
/// <typeparam name="T">Type that implements operator+, operator-, operator*, operator/, and double(T) (explicit cast).</typeparam>
/// <param name="p_data">Vector containing the set.</param>
/// <param name="d_mean">The mean of the set.</param>
/// <returns>The standard deviation of the given set as a double.</returns>
/// <exception cref="std::bad_cast">Thrown if T does not implement the explicit conversion operator double(T).</exception>
template <typename T>
double getStandardDeviation(const std::vector<T>* p_data, const double d_mean)
{
	double d_standardDeviation = 0.0;

#pragma loop(hint_parallel(0))
	for (size_t i = 0; i < p_data->size(); i++)
	{
		d_standardDeviation += pow(p_data->at(i) - d_mean, 2);
	} // end for

	return sqrt(d_standardDeviation / static_cast<double>(p_data->size()));
} // end template getStandardDeviation


/// <summary>Calculates the range of the given set.</summary>
/// <typeparam name="T">Type that implements operator- and double(T) (explicit cast).</typeparam>
/// <param name="p_data">Vector containing the set.</param>
/// <returns>The range of the given set as a double.</returns>
/// <exception cref="std::bad_cast">Thrown if T does not implement the explicit conversion operator double(T).</exception>
template <typename T>
inline double getRange(const std::vector<T>* p_data)
{
	double	result;
	T		min = p_data->at(0),
			max = p_data->at(0);


	for (size_t i = 0; i < p_data->size(); i++)
	{
		if (p_data->at(i) < min)
		{
			min = p_data->at(i);
		} // end if
		if (p_data->at(i) > max)
		{
			max = p_data->at(i);
		} // end if
	} // end if

	result = static_cast<double>(max - min);

	return result;
} // end template getRange


/// <summary>Calculates the median of the given set.</summary>
/// <typeparam name="T">Type that implements operator+ and operator/.</typeparam>
/// <param name="p_data">Vector containing the set.</param>
/// <returns>The median of the given set as a double.</returns>
template <typename T>
inline T getMedian(std::vector<T>* p_data)
{
	std::sort(p_data->begin(), p_data->end());

	if (p_data->size() % 2)
	{
		return p_data->at(p_data->size() / 2);
	} // end if
	else
	{
		T temp = p_data->at(p_data->size() / 2);
		temp += p_data->at((p_data->size() / 2) + 1);
		return (temp / 2);
	} // end else
} // end template getMedian


/// <summary>Finds the maximum of the given set.</summary>
/// <typeparam name="T">Type that implements std::less.</typeparam>
/// <param name="p_vect">Vector containing the set.</param>
/// <returns>The maximum of the given set as a double.</returns>
template <typename T>
inline T maxValueInVector(std::vector<T>* p_vect)
{
	std::sort(p_vect->begin(), p_vect->end());

	return p_vect->at(p_vect->size() - 1);
} // end template maxValueInVector


/// <summary>Finds the minimum of the given set.</summary>
/// <typeparam name="T">Type that implements std::less.</typeparam>
/// <param name="p_vect">Vector containing the set.</param>
/// <returns>The minimum of the given set as a double.</returns>
template <typename T>
inline T minValueInVector(std::vector<T>* p_vect)
{
	std::sort(p_vect->begin(), p_vect->end());

	return p_vect->at(0);
} // end template minValueInVector


/// <summary>Finds the sum of the given set.</summary>
/// <typeparam name="T">Type that implements std::less.</typeparam>
/// <param name="p_vect">Vector containing the set.</param>
/// <returns>The sum of all elements in the given set.</returns>
template <typename T>
inline T vectorSum(const std::vector<T>* p_vect)
{
	T sum = 0;

	for (auto & e : *p_vect)
	{
		sum += e;
	} // end for

	return sum;
} // end template vectorSum


/// <summary>Finds the distance between point A and point B.</summary>
/// <typeparam name="T">A type that implements double(T) (explicit cast).</typeparam>
/// <param name="a">The first point.</param>
/// <param name="b">The second point.</param>
/// <returns>The distance between points <paramref name="a"/> and <paramref name="b">.</returns>
template <typename T>
inline double getDistance(T a, T b)
{
	return sqrt(pow((b - a), 2));
} // end template getDistance


/// <summary>Sorts the given vector section between <paramref name="left"/> and <paramref name="right"/> using IS.</summary>
/// <typeparam name="Iter">Iterator of a comparable type.</typeparam>
/// <param name="left">Iterator to front of section.</param>
/// <param name="right">Iterator past the end of the section.</param>
template<typename Iter>
void vector_insertionSort(Iter left, Iter right)
{
	auto initial_left = left;

	while (left != right)
	{
		auto curr = left;
		auto temp = *left;

		while (curr != initial_left && temp < *(curr - 1))
		{
			*curr = *(curr - 1);
			curr--;
		} // end while
		*curr = temp;
		left++;
	} // end for
} // end template vector_insertionSort


/// <summary>Sorts the given vector section between <paramref name="left"/> and <paramref name="right"/> using hybrid QS.</summary>
/// <typeparam name="Iter">Iterator of a comparable type.</typeparam>
/// <param name="left">Iterator to front of section.</param>
/// <param name="right">Iterator past the end of the section.</param>
template<typename Iter>
void vector_quickSort(Iter left, Iter right)
{
	auto size = std::distance(left, right);

	if (size <= 1)
	{
		return;
	} // end if
	if (size <= SWITCH_TO_IS)
	{
		vector_insertionSort(left, right); // swap to IS once partition is small
		return;
	} // end if

	auto pivot = right - 1; // use last element as pivot as vector will usually be almost sorted except last part

	auto partition = left; // partitioning point
	auto curr = left; // iterator

	// partition vector
	while (curr != right)
	{
		if (*curr < *pivot)
		{
			std::iter_swap(partition, curr);
			partition++;
		} // end if
		curr++;
	} // end while

	std::iter_swap(pivot, partition);
	vector_quickSort(left, partition);
	vector_quickSort(partition + 1, right);
} // end template vector_quickSort


#endif

