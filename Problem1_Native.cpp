/*
 *	Performance in Development
 *	
 *	Problem 1: sort a vector of chars in increasing and decreasing order
 *
 *	Solution with Native C++ and STL Containers
 *
 */

 // Include Standard Library headers
#include <iostream>
#include <vector>
#include <chrono>
#include <random>


// O(input_size) (linear)
void myCharInit(std::vector<char> & myVec) {

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


// Reverses a vector
template <typename PrimitiveType>
void myReverse(std::vector<PrimitiveType> & myVec) {

	// Get iterators
	auto begin = myVec.begin();
	auto end = myVec.begin() + myVec.size() / 2;

	auto last = myVec.end() - 1;
	
	// Reverse
	for (; begin != end; ++begin) {
		PrimitiveType temp = *begin;
		*begin = *last;
		*last-- = temp;	
	}
}

// O(n lg n) Quicksort

// Partition auxiliary function for quicksort
template <class Type>
int partition(std::vector<Type> & myVector, int begin, int end) {
	Type x = myVector[end];
	int i = begin - 1;
	for (unsigned j = begin; j < end; j++) {
		if (myVector[j] <= x) {
			i++;
			Type temp = myVector[j];
			myVector[j] = myVector[i];
			myVector[i] = temp;
		}
	}
	Type temp = myVector[i + 1];
	myVector[i + 1] = myVector[end];
	myVector[end] = temp;
	return i + 1;
}

// Recursive Quicksort algorithm
template <class Type>
void myQuicksort(std::vector<Type> & myVector, int begin, int end) {
	if (begin < end) {
		int mid = partition(myVector, begin, end);
		myQuicksort(myVector, begin, mid - 1);
		myQuicksort(myVector, mid + 1, end);
	}
}


int main() {

	// 1. Create a vector populated with characters

	const std::size_t size = 10;

	std::vector<char> myVector(size);
	myCharInit(myVector);

	
		// i. Print the initial values

	std::cout << "Original vector:\n";
	for (const double & elem : myVector)
		std::cout << elem << " ";
	std::cout << "\n\n";

	

	// 2. Sort
	myQuicksort<char>(myVector, 0, size - 1); // O(n lg n)



	// 3. Copy values to increasing-order vector

	std::vector<char> increasing;

	for (const double & elem : myVector)
		increasing.push_back(elem);



	// 4. Reverse
	myReverse<char>(myVector); // O(n)



	// 5. Copy values to increasing-order vector
	
	std::vector<char> decreasing;

	// Copy to the decreasing vector
	for (const double & elem : myVector)
		decreasing.push_back(elem);



	// 6. Print results

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