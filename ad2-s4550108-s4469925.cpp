/* 
 * For the best practical results, please build the code 
 * using the provided makefile.
 */

#include <iostream>
#include <vector>

//#include <cstdio>
//#include <chrono>

/*
 * Return value is number rounded to the closest multiple of 5.
 * 
 * This function is made template to be able to use is with both unsigned and unsigned short types
 */
template <typename T>
inline T round (T number) noexcept 
{
	static int add[5] = {0, -1, -2, 2, 1};
	return number+add[number%5];
}

/*
 * Main algorithm. Return value is the minimum cost Matteo has to pay.
 */
unsigned solve (const unsigned short& n, const unsigned short& k,
		const std::vector<unsigned>& partial_sum, 
		const std::vector<unsigned>& non_rounded_partial_sum) 
{
	std::vector<unsigned> data(partial_sum);
	std::vector<unsigned> next_data(partial_sum);
	unsigned temp=0;
	// iterating over the number of dividers
	for(auto k0 = 0 ; k0 < k-1; k0++) {
		// iterating over the number of products
		for (auto i = 0; i < n; i++ ){
			// where to place the last divider
			for (auto j = 0; j < i; j++){
				temp = data[j] + round(non_rounded_partial_sum[i]-non_rounded_partial_sum[j]);
				if(next_data[i] > temp) {
	    				next_data[i] = temp;
					if( temp==0 ) break;
				}
			}
		}
		data = next_data;
	}
	
	for(auto j = 0; j <= n-1; j++){
		temp = data[j] + round(non_rounded_partial_sum[n-1]-non_rounded_partial_sum[j]);
		if (next_data[n-1] > temp)
			next_data[n-1] = temp;
	}
	
	
	return next_data[n-1];
}

/*
 * Read data from stdin
 * n - number of products
 * k - number of dividers
 */
void initialise_data(unsigned short& n, unsigned short& k,
		std::vector<unsigned>& partial_sum,
		std::vector<unsigned>& non_rounded_partial_sum) 
{
	std::cin >> n >> k;
	
	partial_sum.reserve(n);
	non_rounded_partial_sum.reserve(n);

	unsigned short input_cost;
	std::cin >> input_cost;
	partial_sum.push_back(round(input_cost));
	non_rounded_partial_sum.push_back(input_cost);

	for (auto i = 1; i < n; i++){
		std::cin >> input_cost;
		non_rounded_partial_sum.push_back( non_rounded_partial_sum[i - 1] + input_cost );
		partial_sum.push_back( round(non_rounded_partial_sum[i]) );
	}
}

int main() 
{
	//auto t1 = std::chrono::high_resolution_clock::now();

	unsigned short n;
	unsigned short k;
	std::vector<unsigned short> products;
	std::vector<unsigned> partial_sum;
	std::vector<unsigned> non_rounded_partial_sum; 

	initialise_data (n, k, partial_sum, non_rounded_partial_sum);
	std::cout << solve(n, k, partial_sum, non_rounded_partial_sum) << '\n';

	//auto t2 = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> time = t2-t1;
	//printf("%lf\n", time.count());
	
	return 0;
}
