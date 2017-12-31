/*
 *	Elementary STL Algorithms
 *
 *	Algorithms:
 *		1) for_each
 *		2) transform
 *		3) find_if
 *		4) copy_if
 *		5) accumulate
 */

// Include Standard Library headers
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

// Policies (callable objects / functors)

// Prints an input number if even
struct print_if_even {
	void operator()(const int & number) {
		if (number % 2 == 0) std::cout << number << " ";
	}
};

// Returns true if an element is greater than a target element
// Type must support comparison operators, copy and default constructors, and proper destructor
template <class Type>
class is_greater {
public:
	is_greater(Type t = 0) : target(t) {}
	bool operator()(const Type & value) { return value > target; }
private:
	Type target;
};

// Returns true if a numeric element is negative
template <class NumericType>
struct is_negative {
public:
	bool operator()(const NumericType & value) { return value < 0; }
};

// Returns the exponentiation of a numeric element 'a' i.e. e^{a}, where 'e' is the Euler constant
template <class NumericType>
struct exponentiate {
	NumericType operator()(NumericType & element) { return std::exp(element); }
};

int main() {

	/** for_each ***/

	std::cout << "Testing for_each algorithm...\n";

	// Task: print the even values of a vector of integers

	std::vector<int> myVector = { 1,2,3,4,6,7,8,9,10 };

	// Print all evens of vector
	std::cout << "Print all evens: ";
	std::for_each(std::begin(myVector), std::end(myVector), print_if_even());
	std::cout << "\n";

	// Will apply the policy to each element and result to:
	// { print_if_even()(1),  print_if_even()(2), ...,  print_if_even()(10) } =  
	// { 1,	print(2),  3, print(4), ..., 9,  print(10) }

	// Task: print all even values of starting at the middle of the vector

	std::vector<int>::const_iterator middle = myVector.begin() + myVector.size() / 2;
	std::vector<int>::const_iterator end = myVector.end();

	std::cout << "Print half evens: ";
	auto printing_evens = std::for_each(middle, end, print_if_even());

	// will the following line compile?
	// int k = 100; printing_evens(k);

	std::cout << "\n\n\n";



	/** find_if ***/

	std::cout << "Testing find_if algorithm...\n";

	// Task: find the smallest element after the value 8.9

	std::list<double> myList = { -.01, 2.91, 5.9, 8.71, 8.91, 8.99, 10.45 };
	double target = 8.9;

	// Find element, if it is there
	std::list<double>::iterator found 
		= std::find_if(std::begin(myList), std::end(myList), is_greater<double>(target));

	// Print the element if it is found
	if (found != std::end(myList))
		std::cout << "First element greater than " << target << ": " << *found << "\n";
	else
		std::cout << "Element not found!\n";

	std::cout << "\n\n";



	/** transform ***/

	std::cout << "Testing transform algorithm...\n";

	// Task: exponentiate all values of an array in place

	std::array<double, 5> myArray = { 3.4, 2.5, 9,8, 12.01 };

	std::transform(std::begin(myArray), std::end(myArray), std::begin(myArray), exponentiate<double>());

	// Print results with C++11 range-based loop
	std::cout << "Exponentiated values\n";
	for (auto elem : myArray) {
		std::cout << elem << " ";
	}
	
	std::cout << "\n\n\n";



	/** copy_if ***/

	std::cout << "Testing copy_if algorithm...\n";

	// Task: copy all negative numbers from a list to a vector
	std::list<double> myList2 = { -1.1, 2.231, -3.23, 4.01, -9.1, -89.1, 12, 8.28 };

	// Print list by copying the elements in the ostream
	std::cout << "List: ";
	for (auto elem : myList2) 
		std::cout << elem << " ";


	// Get the negatives
	std::vector<double> negatives;
	std::copy_if(std::begin(myList2), std::end(myList2), std::back_inserter(negatives), is_negative<double>());

	std::cout << "\nNegatives: ";
	for (auto elem : negatives)
		std::cout << elem << " ";
	std::cout << "\n\n\n";



	/** accumulate ***/

	std::cout << "Testing accumulate algorithm...\n";

	// Task: compute new earnings

	double initial_earnings = 5123.98;

	// Weekly earnings
	std::array<double, 7> earnings = { 10.3, -12.01, -8.9, 5.1, -7.8, 12.0, 1.1 };

	// Compute the new earnings by accumulating the daily values
	double new_earnings =
		std::accumulate(std::begin(earnings), std::end(earnings), initial_earnings);

	// Check if we had profit
	if (new_earnings > initial_earnings)
		std::cout << "Good job!\n";
	else
		std::cout << "We had losses!\n";

	// Update the earnings
	initial_earnings = new_earnings;

	std::cout << "\n\n";

	return 0;
}