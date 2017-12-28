/*
 *	Bugs when using STL tutorial
 *
 *	Common Bugs:
 *		1) Out-of-range iterators
 *		2) Dereferencing illegal iterators
 *		3) Poor container choices
 *		4) Const-correctness in STL
 *		5) Ignoring the return type
 */

// Include Standard Library headers
#include <iostream>
#include <array>
#include <set>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

// Policies (callable objects / functors)

// Returns true if a numeric element is negative
template <class NumericType>
struct is_negative {
public:
	bool operator()(const NumericType & value) { return value < 0; }
};

// Returns true if a numeric element is odd
struct is_odd {
	bool operator()(const int & number) { return number % 2 != 0; }
};


int main() {

	/** Out-of-range I/O iterators ***/

	std::vector<int> myVector = { 1, 2, 3, 4, 5 };

	int k = 2; // (int) k > 0

	std::size_t m = myVector.size() + k; 

	// The following lines will throw an exception:
	//		std::for_each(myVector.begin(), myVector.end() - m, is_odd());	// yikes!
	//		std::accumulate(myVector.begin() + m, myVector.end(), 0);		// ouch!
	//		std::accumulate(myVector.end(), myVector.begin(), 0);			// crash!



	/** Dereferencing illegal iterators ***/

	std::list<double> myList2 = { -1.1, 2.231, -3.23, 4.01, -9.1, -89.1, 12, 8.28 };

	std::vector<double> negatives;

	// The following line will throw an exception:
	//		std::copy_if(myList2.begin(), myList2.end(), negatives.begin(), is_negative<double>());

	// Correct version:
	std::copy_if(myList2.begin(), myList2.end(), std::back_inserter(negatives), is_negative<double>());



	/** Poor container choices and const correctness ***/

	std::set<int> mySet = { 2, 3, 5, 7, 9 };

	// Compiler error ! 
	//		std::reverse(mySet.begin(), mySet.end()); 


	std::unordered_map<int, int> myHash = { { 1,1 },{ 2,2 },{ 3,3 } };

	// Compiler errors !
	//		std::sort(myHash.begin(), myHash.end()); 



	/** Ignoring the return type ***/

	std::array<int, 10> intArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::array<int, 5> oddArray;

	std::array<int, 5U>::iterator d_first =
		std::copy_if(intArray.begin(), intArray.end(), oddArray.begin(), is_odd());

	// The following line will throw
	//		std::cout << *d_first << std::endl;


	return 0;
}