/*
 *	Performance in Development
 *
 *	Problem 2: Computing basic and nth order statistics: average, median, variance, max, min, range, max 5
 *
 *	Solution with STL Algorithms
 *
 */

 // Include Standard Library headers
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
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
	daily_average = std::accumulate(std::begin(prices), std::end(prices), 0.0);
	daily_average /= (double)size;
	

		// ii. Median price

	// std::partial_sort
	// http://en.cppreference.com/w/cpp/algorithm/partial_sort

	double daily_median = 0.0;
	std::partial_sort(std::begin(prices), std::begin(prices) + (size / 2) + 1, std::end(prices));

	daily_median = prices[size / 2  - 1];


		// iii. Max price

	// std::max_element
	// http://en.cppreference.com/w/cpp/algorithm/max_element
	// Notice: max_element returns the iterator to the max element

	double max_price = 0.0;
	std::vector<double>::iterator max_price_position = std::max_element(std::begin(prices), std::end(prices));
	if (max_price_position != prices.end())
		max_price = *max_price_position;


		// iv. Min price

	// std::min_element
	// http://en.cppreference.com/w/cpp/algorithm/min_element
	// Notice: min_element returns the iterator to the min element

	double min_price = 0.0;
	auto min_price_position = std::min_element(std::begin(prices), std::end(prices));
	if (min_price_position != std::end(prices)) 
		min_price = *min_price_position;
	

		// v. Price range

	double price_range = 0.0;
	price_range = std::abs(max_price - min_price);


		// v. Max 5 prices

	// std::nth_element
	// http://en.cppreference.com/w/cpp/algorithm/nth_element

	std::vector<double> max_5_prices;
	std::nth_element(std::begin(prices), std::begin(prices) + 5, std::end(prices), decreasing_order<double>());
	
	std::copy(std::begin(prices), std::begin(prices) + 5, std::back_inserter(max_5_prices));


		// vi. Variance

	// std::for_each with a lambda function (Bonus: what is lambda function?)
	// http://en.cppreference.com/w/cpp/algorithm/for_each
	// http://en.cppreference.com/w/cpp/language/lambda

	double variance = 0.0;
	std::for_each(std::begin(prices), std::end(prices), [&](double elem) {
		variance += std::pow(elem - daily_average, 2);
	});

	// Compute the unbiased variance
	variance /= (double)(size - 1);



	// 4. Print statistics

	// Print input prices
	std::cout << "Daily prices: [$]\n\n";
	for (const auto & price_pair : input_prices) {
		std::cout << price_pair.first << "\t" << price_pair.second << "\n";
	}

	// Print statistics

	std::cout   	<< "\n\n";
	std::cout   	<< "Open: "			<< input_prices.begin()->second		<< " [$]\n" 
			<< "Close: "			<< (input_prices.end() - 1)->second	<< " [$]\n\n"
			<< "Average price: "		<< daily_average			<< " [$]\n"
			<< "Variance: " 		<< variance				<< "\n"
			<< "Median price: "		<< daily_median				<< " [$]\n\n"
			<< "Max price: "		<< max_price				<< " [$]\n"
			<< "Min price: "		<< min_price				<< " [$]\n"
			<< "Price range: "		<< price_range				<< " [$]\n\n"
			<< "Top 5 price peaks: [$]\t";
	
	for (const double & elem : max_5_prices)
		std::cout << elem << "\t";
	std::cout << "\n\n";
	
	return 0;
}

