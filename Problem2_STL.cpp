/*
 *	Performance in Development
 *
 *	Problem 2: Computring basic and nth order statistics: average, median, max, min, range, max 5
 *
 *	Solution with STL
 *
 */

 // Include Standard Library headers
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
#include <random>
#include <utility> // pair

// Policy (callable object / functor)

// Use this predicate for comparison sorting condition
// Will sort in decreasing order
template <class Numeric>
struct decreasing_order {
	bool operator()(const Numeric & a, const Numeric & b)
		{ return a > b;	}
};


int main() {

	// 1. Get the prices

	// Daily stock prices, updated every 30 minutes
	// std::pair
	// http://en.cppreference.com/w/cpp/utility/pair

	std::vector<std::pair<std::string, double>> input_prices =
	{ {"09:30AM", 23.29}, {"10:00AM", 22.11}, {"10:30AM", 23.42}, {"11:00AM", 23.64}, {"11:30AM", 22.95},
	  {"12:00PM", 22.81}, {"12:30PM", 22.98}, {"01:00PM", 24.65}, {"01:30PM", 25.10}, {"02:00PM", 25.12},
	  {"02:30PM", 25.96}, {"03:00PM", 24.98}, {"03:30PM", 24.65}, {"04:00PM", 23.45} };
	



	// 2. Process the prices 

	// Get a non-zero size
	std::size_t size;
	(input_prices.size() != 0) ? size = input_prices.size() : size = 1;

	// Convert values to a vector
	std::vector<double> prices;

	// Range-based C++11 for loop
	// http://en.cppreference.com/w/cpp/language/range-for
	// Get the numeric values i.e. 
	// elem.first = key
	// elem.second = value
	// Notice: In STL there is no built-in method to get all keys or values from a map

	for (const auto & elem : input_prices) 
		prices.push_back(elem.second);




	// 3. Compute statistics

		// i. Average price

	// std::accumulate
	// http://en.cppreference.com/w/cpp/algorithm/accumulate

	double daily_average = 0.0;
	daily_average = std::accumulate(prices.begin(), prices.end(), 0) / (double)size;
	

		// ii. Median price

	// std::partial_sort
	// http://en.cppreference.com/w/cpp/algorithm/partial_sort

	double daily_median = 0.0;
	std::partial_sort(prices.begin(), prices.begin() + (size / 2), prices.end());

	daily_median = prices[size / 2];


		// iii. Max price

	// std::max_element
	// http://en.cppreference.com/w/cpp/algorithm/max_element
	// Notice: max_element returns the iterator to the max element

	double max_price = 0.0;
	std::vector<double>::iterator max_price_position = std::max_element(prices.begin(), prices.end());
	if (max_price_position != prices.end())
		max_price = *max_price_position;


		// iv. Min price

	// std::min_element
	// http://en.cppreference.com/w/cpp/algorithm/min_element
	// Notice: min_element returns the iterator to the min element

	double min_price = 0.0;
	auto min_price_position = std::min_element(std::begin(prices), std::end(prices));
	if (min_price_position != prices.end()) 
		min_price = *min_price_position;
	

		// v. Price range

	double price_range = 0.0;
	price_range = std::abs(max_price - min_price);


		// v. Max 5 prices

	// std::nth_element
	// http://en.cppreference.com/w/cpp/algorithm/nth_element

	std::vector<double> max_5_prices;
	std::nth_element(prices.begin(), prices.begin() + 5, prices.end(), decreasing_order<double>());
	
	std::copy(prices.begin(), prices.begin() + 5, std::back_inserter(max_5_prices));





	// 4. Print statistics

	// Print input prices
	std::cout << "Daily prices: [$]\n\n";
	for (const auto & price_pair : input_prices) {
		std::cout << price_pair.first << "\t" << price_pair.second << "\n";
	}

	// Print statistics

	std::cout   << "\n\n";
	std::cout	<< "Open: "					<< input_prices.begin()->second		<< " [$]\n" 
				<< "Close: "				<< (input_prices.end() - 1)->second	<< " [$]\n\n"
				<< "Average price: "		<< daily_average					<< " [$]\n"
				<< "Median price: "			<< daily_median						<< " [$]\n\n"
				<< "Max price: "			<< max_price						<< " [$]\n"
				<< "Min price: "			<< min_price						<< " [$]\n"
				<< "Price range: "			<< price_range						<< " [$]\n\n"
				<< "Top 5 price peaks: [$]\t";
	
	std::copy(max_5_prices.begin(), max_5_prices.end(), std::ostream_iterator<double>(std::cout, "\t"));
	std::cout << "\n\n";
	
	return 0;
}

