/*
 * Name             waterjugpuzzle.cpp
 * Author           Krystal Hong
 * Date             10 October 2021
 * Description      Solving the water jug puzzle
 * Pledge           I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;


// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    State(int _a, int _b, int _c, string _directions, State *_parent) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }

    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};
string bfs(int size_a, int size_b, int size_c, int goal_a, int goal_b, int goal_c, State s){
	string result;

	vector<State*> p;
	queue<State> states;
	states.push(s); 

	struct State empty = State(0, 0, 0, "");
	vector<vector<State>> matrix(size_a+1, vector<State> (size_b + 1, empty)); 

	while (!states.empty()) { 
		struct State curr = states.front();
		states.pop();

		if (curr.a == goal_a && curr.b == goal_b && curr.c == goal_c) { //reached goal
					result = "Initial state. " + s.to_string() + "\n";
					vector<State> list;
					list.push_back(curr);

					while (curr.parent != nullptr) {
						list.push_back(curr);
						curr = *curr.parent;
					}




					for (int i = list.size() - 1; i != 0; i--) {
						if(!(i==0)){
							result = result + list[i].directions + " " + list[i].to_string() + "\n";
						}
                        else{
							result = result + list[i].directions + " " + list[i].to_string();

						}
					}
					for(unsigned int i = 0; i < p.size(); i++){ //delete pointers 
							delete p[i];
						}
			return result;
		}

		if (matrix[curr.a][curr.b].directions.empty()){ 
			matrix[curr.a][curr.b] = curr; 
			int pour;

			if (curr.c > 0 && curr.a < size_a){ //C -> A
				pour = min(curr.c, size_a-curr.a);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from C to A.";
				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from C to A.";
				}
            
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a+pour, curr.b, curr.c-pour, directions, del));
				p.push_back(del);
			}

			if (curr.b > 0 && curr.a < size_a){ //B -> A
				pour = min(curr.b, size_a-curr.a);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from B to A.";
				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from B to A.";
				}
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a+pour, curr.b-pour, curr.c, directions, del));
				p.push_back(del);
			}
			if (curr.c > 0 && curr.b < size_b){ //C -> B
				pour = min(curr.c, size_b-curr.b);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from C to B.";
				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from C to B.";
				}
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a, curr.b+pour, curr.c-pour, directions, del));
				p.push_back(del);
			}
			if (curr.a > 0 && curr.b < size_b){ //A -> B
				pour = min(curr.a, size_b-curr.b);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from A to B.";

				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from A to B.";
				}
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a-pour, curr.b+pour, curr.c, directions, del));
				p.push_back(del);
			}

			if (curr.b > 0 && curr.c < size_c){ //B -> C
				pour = min(curr.b, size_c-curr.c);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from B to C.";

				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from B to C.";

				}
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a, curr.b-pour, curr.c+pour, directions, del));
				p.push_back(del);

			}

			if (curr.a > 0 && curr.c < size_c){ //A -> C
				pour = min(curr.a, size_c-curr.c);
                string directions;
				if(pour == 1){
					directions = "Pour " + to_string(pour) + " gallon from A to C.";

				}
                else{
					directions = "Pour " + to_string(pour) + " gallons from A to C.";

				}
                State* del= new State(curr.a,curr.b,curr.c,curr.directions,curr.parent);
				states.push(State(curr.a-pour, curr.b, curr.c+pour, directions, del));
				p.push_back(del);

			}

		}

	}
	for(unsigned int i = 0; i < p.size(); i++){
		delete p[i];
	}
    return "No solution.";
}


int main(int argc, char * const argv[]) {
//<cap A> <cap B> <cap C> <goal A> <goal B> <goal C>
	string str;
	istringstream iss;
	int a,b,c,a_g,b_g,c_g;


		if(!(argc == 7)){
		     cerr << "Usage: " << argv[0] <<" <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		  	 return 1;
		}

		iss.str(argv[1]);
		if ( !(iss >> a) || a <= 0){
			cerr << "Error: Invalid capacity '"<< argv[1] <<"' for jug A." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[2]);
		if ( !(iss >> b) || b <= 0){
			cerr << "Error: Invalid capacity '" << argv[2] <<"' for jug B." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[3]);
		if ( !(iss >> c) || c <= 0){
			cerr << "Error: Invalid capacity '" << argv[3] <<"' for jug C." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[4]);
		if ( !(iss >> a_g) || a_g < 0){
			cerr << "Error: Invalid goal '" << argv[4] <<"' for jug A." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[5]);
		if ( !(iss >> b_g) || b_g < 0){
			cerr << "Error: Invalid goal '" << argv[5] <<"' for jug B." << endl;
			return 1;
		}

		iss.clear();
		iss.str(argv[6]);
		if ( !(iss >> c_g) || c_g < 0){
			cerr << "Error: Invalid goal '" << argv[6] <<"' for jug C." << endl;
			return 1;
		}

		if (a_g > a){
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 1;
		}
		if (b_g > b){
			cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 1;
		}
		if (c_g > c){
			cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 1;
		}
		iss.clear();

		if (c > a_g + b_g + c_g){
			cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
			return 1;
		}

    State s(0, 0, c, "Initial state.");
    cout << bfs(a,b,c,a_g,b_g,c_g,s) << endl;
    return 0;
}
