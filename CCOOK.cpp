//https://www.codechef.com/problems/CCOOK
//The problem statement is contained in the link above.
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout; using std::cin; using std::string; using std::vector;
int main(){
    vector<string>groups{"Beginner", "Junior Developer",
                    "Middle Developer", "Senior Developer",
                    "Hacker", "Jeff Dean"};
    
    vector<string> rank; //Store ranks for multiple inputs

    //No of inputs
    int A{};
    cin >> A;
    if(A==0 || A>5000) {   return -1; } //Constraint

    int R[5] = {0, 0, 0, 0, 0}; //Results for each problem

    for(; A>0; A--){
        cin >> R[0] >> R[1] >> R[2] >> R[3] >> R[4];
        rank.push_back(groups[ R[0] + R[1] + R[2] + R[3] + R[4] ]);
    }

    for(auto user_rank : rank){
        cout << user_rank << std::endl;
    }
    return 0;
}
