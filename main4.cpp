#include <iostream>
#include "Array.h"

#include <cstdio>
#include <chrono>

template<typename T>
inline T round ( T number ) noexcept
{
	constexpr static int add[5] = {0, -1, -2, 2, 1};
	return number+add[number%5];
}

unsigned solve (const unsigned short& n, const unsigned short& k,
		const Array<unsigned>& partial_sum, 
		const Array<unsigned>& non_rounded_partial_sum) 
{
	Array<unsigned> data(partial_sum);
	Array<unsigned> next_data(partial_sum);
	unsigned temp;

	for(unsigned short k0 = 0 ; k0 < k-1; k0++) {
		for (unsigned short i = 0; i < n; i++ ){
			for (unsigned short j = 0; j <= i; j++ ){
				temp = data[j] + round(non_rounded_partial_sum[i]-non_rounded_partial_sum[j]);
				if( next_data[i] > temp ) {
	    				next_data[i] = temp;
					if( temp==0 ) break;
				}
			}
		}
		data = next_data;
	}
	
	for (unsigned short j = 0; j <= n-1; j++ ){
		temp = data[j] + round(non_rounded_partial_sum[n-1]-non_rounded_partial_sum[j]);
		if ( next_data[n-1] > temp )
			next_data[n-1] = temp;
	}
	return next_data[n-1];
}

void initialise_data(unsigned short& n, unsigned short& k,
		Array<unsigned>& partial_sum,
		Array<unsigned>& non_rounded_partial_sum) 
{
	std::cin >> n >> k;
	
	partial_sum.reserve(n);
	non_rounded_partial_sum.reserve(n);

	unsigned short input_cost;
	std::cin >> input_cost;
	partial_sum[0] = round(input_cost);
	non_rounded_partial_sum[0] = input_cost;

	for (unsigned short i = 1; i < n; i++ ){
		std::cin >> input_cost;
		non_rounded_partial_sum[i] = non_rounded_partial_sum[i - 1] + input_cost;
		partial_sum[i] = round(non_rounded_partial_sum[i]) ;
	}
}

int main() 
{
	auto t1 = std::chrono::high_resolution_clock::now();

	unsigned short n;
	unsigned short k;
	Array<unsigned> partial_sum;
	Array<unsigned> non_rounded_partial_sum; 

	initialise_data (n, k, partial_sum, non_rounded_partial_sum);
	std::cout << solve(n, k, partial_sum, non_rounded_partial_sum) << '\n';

	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = t2-t1;
	printf("%lf\n", time.count());
	
	return 0;
}

