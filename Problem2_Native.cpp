/*
*	Performance in Development
*
*	Problem 2: Computing basic and nth order statistics: average, median, variance, max, min, range, max 5
*
*	Solution with Native C++ and STL Containers
*
*/

// Include Standard Library headers
#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::pair


// O(n lg n) Quicksort

// Partition auxiliary function for quicksort
template <class Type>
int partition(std::vector<Type> & myVector, int begin, int end) {
	Type x = myVector[end];
	int i = begin - 1;
	for (unsigned j = begin; j < end; j++) {
		if (myVector[j] <= x) {
			i++;
			std::swap(myVector[j], myVector[i]);
		}
	}
	std::swap(myVector[i + 1], myVector[end]);
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

	// 1. Get the prices

	// Daily stock prices, updated every 30 minutes
	// std::pair
	// http://en.cppreference.com/w/cpp/utility/pair

	std::vector<std::pair<std::string, double>> input_prices =

	{ { "09:30AM", 23.29 },{ "10:00AM", 22.11 },{ "10:30AM", 23.42 },{ "11:00AM", 23.64 },{ "11:30AM", 22.95 },
	{ "12:00PM", 22.81 },{ "12:30PM", 22.98 },{ "01:00PM", 24.65 },{ "01:30PM", 25.10 },{ "02:00PM", 25.12 },
	{ "02:30PM", 25.96 },{ "03:00PM", 24.98 },{ "03:30PM", 24.65 },{ "04:00PM", 23.45 } };




	// 2. Process the prices 

	// Get a non-zero size
	std::size_t size;
	(input_prices.size() != 0) ? size = input_prices.size() : size = 1;

	// Convert values to a vector
	std::vector<double> prices;

	// C++ ranged-based for loop 
	// Get the numeric values i.e. 
	// elem.first = key
	// elem.second = value

	for (auto & elem : input_prices) 
		prices.push_back(elem.second);



	// 3. Compute statistics

		// i. Average price

	double daily_average = 0.0;

	for (const double & elem : prices)
		daily_average += elem;

	daily_average /= (double)size;

	


		// ii. Median price

	double daily_median = 0.0;

	myQuicksort(prices, 0, size - 1);
	
	daily_median = prices[size / 2 - 1];


		// iii. Max price

	double max_price = 0.0;
	
	auto first = std::begin(prices);
	auto last = std::end(prices);

	if (first != last)
		max_price = *first++;

	for (const double & elem : prices) 
		if (elem > max_price)
			max_price = elem;
	
	
	// Since 'prices' is a sorted vector from computing the median,
	// we could instead do the following:
	// max_price = prices[size - 1]; // last element is the largest


		// iv. Min price
	
	double min_price = 0.0;

	first = prices.begin();
	last = prices.end();

	if (first != last)
		min_price = *first++;

	for (const double & elem : prices)
		if (elem < min_price)
			min_price = elem;

	// Since 'prices' is a sorted vector from computing the median,
	// we could instead do the following:
	// max_price = prices[0]; // first element is the smallest


		// v. Price range

	double price_range = 0.0;
	price_range = std::abs(max_price - min_price);


		// v. Max 5 prices

	std::vector<double> max_5_prices(5);
	
	// Since 'prices' is a sorted vector from computing the median,
	// we can do the following:
	for (unsigned i = 0; i < 5; ++i)
		max_5_prices[i] = prices[size - 1 - i];

	// Alternatively, we would have to sort the vector first and then copy the values


		// vi. Variance

	double variance = 0.0;

	for (const double & elem : prices) 
		variance += std::pow(elem - daily_average, 2);
	
	// Compute the unbiased variance
	variance /= (size - 1);




	// 4. Print statistics

	// Print input prices

	std::cout << "Daily prices: [$]\n\n";
	for (const auto & price_pair : input_prices) {
		std::cout << price_pair.first << "\t" << price_pair.second << "\n";
	}
	

	// Print statistics

	std::cout	<< "\n\n";
	std::cout	<< "Open: "		<< input_prices.begin()->second		<< " [$]\n"
			<< "Close: "		<< (input_prices.end() - 1)->second	<< " [$]\n\n"
			<< "Average price: "	<< daily_average			<< " [$]\n"
			<< "Variance: "		<< variance				<< "\n"
			<< "Median price: "	<< daily_median				<< " [$]\n\n"
			<< "Max price: "	<< max_price				<< " [$]\n"
			<< "Min price: "	<< min_price				<< " [$]\n"
			<< "Price range: "	<< price_range				<< " [$]\n\n"
			<< "Top 5 price peaks: [$]\t";


	for (const double & elem : max_5_prices)
		std::cout << elem << "\t";
	std::cout << "\n\n";

	return 0;
}
