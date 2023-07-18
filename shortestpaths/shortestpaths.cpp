/*******************************************************************************
 * Name        : rbtree.h
 * Author      : Krystal Hong
 * Version     : 1.0
 * Date        : 1 December 2021
 * Description : Shortest path with Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <climits>

using namespace std;
long range;
long** matrix;
long** length;
long** intermediate;




void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			long cell = matrix[i][j];
			if (cell < LONG_MAX && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? to_string(max_val).length() :
			to_string(max(static_cast<long>(range), max_val)).length();
	cout << ' ';
	for (int j = 0; j < range; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < range; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < range; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == LONG_MAX) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool startV(string vertex, int line) {
	if (vertex.length() != 1 || vertex[0] < 'A' || vertex[0] >= 'A' + range) {
		cerr << "Error: Starting vertex '" << vertex << "' on line " << line << " is not among valid values A-" << char(range + 'A'-1) << "." << endl;
		return false;
	}
	return true;
}
bool endV(string vertex, int line) {
	if (vertex.length() != 1 || vertex[0] < 'A' || vertex[0] >= 'A' + range) {
		cerr << "Error: Ending vertex '" << vertex << "' on line " << line << " is not among valid values A-" << char(range + 'A'-1) << "." << endl;
		return false;
	}
	return true;
}

bool num(const string& s){
    return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}
bool weight(string distance, int line) {
	if (!num(distance) || distance[0] == '0') {
		cerr << "Error: Invalid edge weight '" << distance << "' on line " << line << "." << endl;
		return false;
	}
	return true;
}



void initializeMatrix() {
	matrix = new long*[range];
	for (int i = 0; i < range; i++) { 
		matrix[i] = new long[range];
	}
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			if (i == j) { 
				matrix[i][j] = 0;
			} 
			else { 
				matrix[i][j] = LONG_MAX;
			}
		}
	}



}


void dele() {
	for (int i = 0; i < range; i++) {
		delete[] matrix[i];
	}
	delete matrix;
	for (int i = 0; i < range; i++) {;
		delete[] length[i];
	}
	delete length;
	for (int i = 0; i < range; i++) {
		delete[] intermediate[i];
	}
	delete intermediate;

}


void fill(string from, string to, string distance){
	char vertex1 = from[0];
	char vertex2 = to[0];
	long weight = stol(distance);
	matrix[vertex1 - 'A'][vertex2 - 'A'] = weight;
}

void path() {
	length = new long*[range];
	for (int i = 0; i < range; i++) { 
		length[i] = new long[range];
	}
	intermediate = new long*[range];
	for (int i = 0; i < range; i++) { 
		intermediate[i] = new long[range];
	}
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			intermediate[i][j] = LONG_MAX;
		}
	}
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			length[i][j] = matrix[i][j];
		}
	}
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			for (int k = 0; k < range; k++) {
				if (k != i && j != i) {
					long current = length[j][k];
					if (length[j][i] != LONG_MAX &&
						length[i][k] != LONG_MAX &&
						current > length[j][i] + length[i][k]){
						length[j][k] = length[j][i] + length[i][k];
						intermediate[j][k] = i;
					}
				}

			}
		}


	}
}

string pathHelp(long from, long to) {
	long inter_vert = intermediate[from][to];
	if (intermediate[from][to] < LONG_MAX) {
		return pathHelp(from, inter_vert) + char(inter_vert + 'A') + pathHelp(inter_vert, to);
	}
	return "";
}

string findPath(long from, long to) {
	if (from == to) {
		return string(1,(from+'A'));
	} 

	else {
		string to_return = char(from+'A') + pathHelp(from, to) + char(to + 'A');
		for (int i = to_return.length()-1; i > 0; i--) {
			to_return.insert(i, " -> ");
		}
		return to_return;
	}

}



void findPaths(){
	for (int i = 0; i < range; i++){
		for (int j = 0; j < range; j++) {
			cout << (char)(i + 'A') << " -> " << (char)(j + 'A') << ", ";
			cout << "distance: ";
			if (length[i][j] < LONG_MAX) {
				cout << length[i][j] << ", ";
				cout << "path: " << findPath(i, j) << endl;
			} 
			else {
				cout << "infinity, path: none" << endl;
			}
		}

	}
}

int main(int argc, char * const argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}


	string filename = argv[1];
	string line;
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error: Cannot open file '" << filename << "'." << endl;
		return 1;
	}



	int count_line = 2;
	getline(file, line);
	istringstream ss(line);
	if (!(ss >> range && range >= 1 && range <= 26)) {
		string error;
		ss >> error;
		cerr << "Error: Invalid number of vertices '" << line << "' on line " << count_line-1 << "." << endl;
		return 1;
	}

	initializeMatrix();
	while (getline(file, line)) { 
		istringstream iss(line);
		string x;
		int count_word = 0;
		string to;
		string from;
		string distance;
		while (iss >> x) {
			count_word++;
			if (count_word == 1) {
				to = x;
				if (!startV(to, count_line)) {
					return 1;
				}
			} 
			else if (count_word == 2) {
				from = x;
				if (!endV(from, count_line)) {
					return 1;
				}
			} 
			else if (count_word == 3){
				distance = x;
				if (!weight(distance, count_line)) {
					return 1;
				}
				fill(to, from, distance); 

			}
		}
		
		if (count_word != 3) { 
			cerr << "Error: Invalid edge data '" << line << "' on line " << count_line << "." << endl;
			return 1;
		}
		count_line++;
	}
	file.close();
	display_table(matrix, "Distance matrix:", false);
	path();
	display_table(length, "Path lengths:", false);
	display_table(intermediate, "Intermediate vertices:", true);
	findPaths();
	dele();
	return 0;
}
