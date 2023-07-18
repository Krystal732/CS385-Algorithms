/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Krystal Hong   
 * Date        : 28 September 2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int num_digits(int num) {
    int count = 0;

    while(num != 0){
        num /= 10;
        count ++;
    }


    return count;
}
vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector< vector<int> > ways;
    vector< vector<int> > result;
    vector<int> empty;
	if (num_stairs <= 0) {
		ways.push_back(empty);
	} 
    else {
		for (int i = 1; i < 4; i++) {
			if (num_stairs >= i) {
				result = get_ways(num_stairs - i);
				for (unsigned int j = 0; j < result.size(); j++) {
                    result.at(j).insert(result.at(j).begin(), i);			
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}


void display_ways(const vector<vector<int> > &ways) {
	// Display the ways to climb stairs by iterating over
	// the vector of vectors and printing each combination.
    const int max = ways.size(), width = num_digits(max);


	for (int i; i < max; i++) {
		cout << setw(width) << i + 1 << ". [";

        for (unsigned int j = 0; j < ways[i].size() - 1; j++) {
			cout << ways[i][j] << ", ";
		}
		cout << ways[i][ways[i].size() - 1];
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int num;
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
	if(!(iss >> num) | (num <= 0)){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss.clear();

    vector<vector<int>> ways = get_ways(num);
    if (num == 1){
        cout << "1 way to climb 1 stair.\n1. [1]" << endl;
    }else{
        cout << ways.size() << " ways to climb " << num << " stairs.\n";
        display_ways(ways);
    }
    return 1;

    

}
