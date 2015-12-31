#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <cstdio>

template <typename T>
T round ( T number ) {
	return number-number%5+5*(number%5>2);
}

unsigned solve ( std::vector<unsigned short>& products, const unsigned short& n, const unsigned short& k,
	const std::vector<unsigned>& partial_sum, 
	const std::vector<unsigned>& non_rounded_partial_sum) {
	
	std::vector<unsigned> data(partial_sum);
	
	for ( unsigned short k0 = 0 ; k0 < k; k0++ ){
		
		std::vector<unsigned> next_data(partial_sum);
		
		for ( unsigned short i = 0; i < n; i++ ){
			
			for ( unsigned short j = 0; j <= i; j++ ){
				
				unsigned temp = data[j] + round(non_rounded_partial_sum[i]-non_rounded_partial_sum[j]);
				if ( next_data[i] > temp )
	    			next_data[i] = temp;
			}

		}

		data = next_data;
	}
	
	std::vector<unsigned> next_data(partial_sum);
	
	for ( unsigned short j = 0; j <= n-1; j++ ){
		unsigned temp = data[j] + round(non_rounded_partial_sum[n-1]-non_rounded_partial_sum[j]);
		if ( next_data[n-1] > temp )
			next_data[n-1] = temp;
	}
	
	return data[n-1];
}

void print_data ( const std::vector<unsigned short>& products ){
	for ( const unsigned short& el : products )
		std::cout << el << " ";
	std::cout << std::endl;
}

void initialise_data( std::vector<unsigned short>& products, unsigned short& n, unsigned short& k,
	std::vector<unsigned>& partial_sum,
	std::vector<unsigned>& non_rounded_partial_sum) {
	
	std::cin >> n >> k;
	products.reserve( n );
	
	partial_sum.reserve( n );
	non_rounded_partial_sum.reserve( n );

	unsigned short input_cost;
	std::cin >> input_cost;
	products.push_back( input_cost ) ;
	partial_sum.push_back(round(input_cost));
	non_rounded_partial_sum.push_back(input_cost);

	for ( unsigned short i = 1; i < n; i++ ){
		std::cin >> input_cost;
		products.push_back( input_cost );
		non_rounded_partial_sum.push_back( non_rounded_partial_sum[i - 1] + input_cost );
		partial_sum.push_back( round(non_rounded_partial_sum[i]) );
	}
	/*std::cout << "[+]";
	std::copy(partial_sum.begin(), partial_sum.end(), std::ostream_iterator<unsigned>(std::cout, ", "));
	std::copy(products.begin(), products.end(), std::ostream_iterator<unsigned>(std::cout, ", "));
	std::cout << products.size();
	*/
}

int main ( ) {
	auto t1 = std::chrono::high_resolution_clock::now();

	unsigned short n;
	unsigned short k;
	std::vector<unsigned short> products;
	std::vector<unsigned> partial_sum;
	std::vector<unsigned> non_rounded_partial_sum; 

	initialise_data (products, n, k, partial_sum, non_rounded_partial_sum);
	//print_data(products);
	std::vector<unsigned> data;

	std::cout << solve(products, n, k, partial_sum, non_rounded_partial_sum) << '\n';

	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = t2-t1;
	printf("%lf", time.count());
	
	return 0;
}
