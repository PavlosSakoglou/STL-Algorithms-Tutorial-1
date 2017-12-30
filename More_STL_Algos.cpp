/*
*	More STL Algorithms
*
*	Some further STL algorithm exploration and examples
*
*/

// Include Standard Library headers
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility> 
#include <cctype>


int main() {

	// 1. Set operations
	std::cout << "*** Set operations ***\n\n";

	std::vector<int> set1 = { 1,2,3,4,5 };
	std::vector<int> set2 = { 4,5,6 };

	std::sort(set1.begin(), set1.end());
	std::sort(set2.begin(), set2.end());


		// i. Print the sets

	std::cout << "Set1:\n";
	std::copy(std::begin(set1), std::end(set1), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";

	std::cout << "Set2:\n";
	std::copy(std::begin(set2), std::end(set2), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n"; 


		// ii. Compute set intersection

	std::vector<int> setIntersection;

	// std::set_intersection
	// http://en.cppreference.com/w/cpp/algorithm/set_intersection
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(setIntersection));

	// Print set intersection
	std::cout << "Set intersection:\n";
	std::copy(std::begin(setIntersection), std::end(setIntersection), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";
	


		// iii. Compute set union

	std::vector<int> setUnion;

	// std::set_union
	// http://en.cppreference.com/w/cpp/algorithm/set_union

	std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(setUnion));

	// Print set union
	std::cout << "Set union:\n";
	std::copy(std::begin(setUnion), std::end(setUnion), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";
	


		// iv. Compute set difference

	std::vector<int> setDifference;

	// std::set_difference
	// http://en.cppreference.com/w/cpp/algorithm/set_difference

	std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(setDifference, setDifference.begin()));

	// Print set difference
	std::cout << "Set difference: (set1 - set2) \n";
	std::copy(std::begin(setDifference), std::end(setDifference), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";




	
	// 2. Numeric Ranges
	std::cout << "\n\n*** Numeric ranges ***\n\n";


	std::vector<int> values(10);


		// i. Generate an increasing range

	// std::iota
	// http://en.cppreference.com/w/cpp/algorithm/iota

	std::iota(std::begin(values), std::end(values), 1);

	// Print values
	std::cout << "Initial range:\n";
	std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";



		// ii. Shuffle randomly

	// std::random_shuffle
	// http://en.cppreference.com/w/cpp/algorithm/random_shuffle

	std::random_shuffle(values.begin(), values.end());

	// Print shuffled values
	std::cout << "After shuffling:\n";
	std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n\n";



		// iii. If it's not a heap, make it a heap

	// std::is_heap
	// http://en.cppreference.com/w/cpp/algorithm/is_heap

	// std::make_heap
	// http://en.cppreference.com/w/cpp/algorithm/make_heap


	// If it's not a heap already, build max heap
	if (!std::is_heap(values.begin(), values.end()))
		std::make_heap(values.begin(), values.end());


	// Check 
	if (std::is_heap(values.begin(), values.end())) {
		std::cout << "It's a heap!\n";
		std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n\n";
	}


		// iv. Push value in the heap

	// std::push_heap
	// http://en.cppreference.com/w/cpp/algorithm/push_heap

	std::cout << "Pushing 0 in the heap...\n\n";
	values.push_back(0);

	std::push_heap(values.begin(), values.end());

	// Check 
	if (std::is_heap(values.begin(), values.end())) {
		std::cout << "It's a heap!\n";
		std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n\n";
	}



	// 3. String operations
	std::cout << "\n\n*** String operations ***\n\n";

		// i. Remove spaces from a string

	std::string text = "Hello darkness my old friend...";

	// Print string
	std::cout << "My string: \n'" << text << "'\n\n";

	// std::remove_if (with a lambda expression!)
	// http://en.cppreference.com/w/cpp/algorithm/remove

	text.erase(std::remove_if(text.begin(), text.end(), [](unsigned char x) {return std::isspace(x);}), text.end());

	// Print result
	std::cout << "My string after taking the spaces out:\n'" << text << "\n\n";



		// ii. Print all permutations of a string (without repetitions)

	std::string text2 = "abc";

	// std::next_permutation
	// http://en.cppreference.com/w/cpp/algorithm/next_permutation

	// Sort first
	std::sort(text2.begin(), text2.end());

	std::cout << "Permutations of '" << text2 << "' :\n";
	do {
		std::cout << text2 << "\n";
	} 
	while (std::next_permutation(text2.begin(), text2.end()));
	std::cout << "\n\n";

	
	std::string text3 = "aba";

	// Sort first
	std::sort(text3.begin(), text3.end());

	std::cout << "Permutations of '" << text3 << "' :\n";
	do {
		std::cout << text3 << "\n";
	} while (std::next_permutation(text3.begin(), text3.end()));
	std::cout << "\n\n";


	// !!!
	// Notice that std::next_permutation won't print ALL permutations of a string, 
	// but only the ones with distinct elements as it uses lexicographical comparison
	// internally, which treats same letters the same


	return 0;
}