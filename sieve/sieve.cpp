/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Krystal Hong
 * Date        : 13 September 2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);


};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}
//bool array is initailly all false
void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    int row_count = 0;

    //iterate through is_prime, if row full then make new row, if i is FALSE then print i into the row
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);


    for (int i = 2; i < limit_ + 1; i++) {
        if (row_count == primes_per_row) {
            row_count = 0;
            cout << endl;
        }

        if (!is_prime_[i]) {
            if (row_count != 0) {
                cout << " ";
            }

            if (num_primes() > primes_per_row) {  
                cout << setw(max_prime_width) << i;
            } else {  // print single row
                cout << i;
            }
            row_count++;
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // interate through is_prime, if FALSE then PRIME so count++
    int count = 0;
    for (int i = 2; i < limit_ + 1.; i++){
        if (!is_prime_[i]){
            count++;
        }
    }

    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // is_prime is initially all false, so the one changed to true NOT prime... FALSE = PRIME
    for (int i = 2; i <= sqrt(limit_); i++){
        if(!is_prime_[i]){
            for (int j = i*i; j <= limit_; j += i){
                is_prime_[j] = true;
            }
        }
    }
    for (int i = limit_; i > 2; i--){
        if(!is_prime_[i]){
            max_prime_ = i;
            break;
        }
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

    int count = 0;

    while(num != 0){
        num /= 10;
        count ++;
    }


    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve seive(limit);
    cout << "\nNumber of primes found: " << seive.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    seive.display_primes();
    




    return 0;
}
