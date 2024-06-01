//https://www.codechef.com/problems/SUPCHEF
//The problem explanation is long and is better viewed at the source linked above
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;

inline bool constrain(int check, int l_constraint, long long u_constraint){
    //Check if the values passed {T, M, N, K} fall within the required range
    if(check < l_constraint || check > u_constraint)
        return false;
    return true;
}
int main(){
    int T{}, N{}, M{}, K{};

    //All the results for all test cases are put into one string, result.
    std:: string result;
    
    cin >> T; //no of test cases
    
    for(int i=0; i<T; i++){
        cin >> M >> N >> K;

        //assert that the values fall within the required range.
        if(!constrain(T, 1, 10000)){return -1;}
        if(!constrain(M, 1, 1000000000)){return -1;}
        if(!constrain(N, 1, 10000)){return -1;}
        if(!constrain(K, 1, 10000)){return -1;}

        if(N*K < M)
        {   result.append("YES\n");}
        else
        {   result.append("NO\n"); }
    }

    cout << result;
    return 0;
}
