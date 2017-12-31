/*
 *	Performance in Development
 *
 *	Problem 1: sort a vector of chars in increasing and decreasing order
 *  
 *	Solution with STL
 *
 */

// Include Standard Library headers
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <iterator>

// Auxiliary function to populate input vector with random characters

// O( input_size ) (linear)
void initialize(std::vector<char> & myVec) {

	// RNG 
	std::default_random_engine engine;
	std::uniform_int<int> dist(0, 25);
	
	// Iterators
	auto begin = myVec.begin();
	auto end = myVec.end();

	// Assign random characters to each element
	for (; begin != end; ++begin) {
		engine.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		*begin = ('A' + (char)dist(engine));
	}
}

int main() {

	// Create a vector populated with characters
	const std::size_t SIZE = 20;
	std::vector<char> myVector(SIZE);
	initialize(myVector);

	// Result vectors
	std::vector<char> increasing, decreasing;

	// Sort 
	std::sort(myVector.begin(), myVector.end());  // O(n lg n)

	// Copy increasing
	std::copy(myVector.begin(), myVector.end(), std::back_inserter(increasing));  // O(n)

	// Copy decreasing
	std::reverse(myVector.begin(), myVector.end());								  // O(n)
	std::copy(myVector.begin(), myVector.end(), std::back_inserter(decreasing));  // O(n)

	// Print results
	std::cout << "Increasing:\n";
	for (const double & elem : increasing)
		std::cout << elem << " ";
	std::cout << "\n\n";

	std::cout << "Decreasing:\n";
	for (const double & elem : decreasing)
		std::cout << elem << " ";
	std::cout << "\n\n";

	return 0;
}