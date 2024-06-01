//https://www.codechef.com/problems/LAZYCHF
/*
  The problem reads:

  Chef is a very lazy person. Whatever work is supposed to be finished in 
  x units of time, he finishes it in m∗x units of time. But there is always a 
  limit to laziness, so he delays the work by at max d units of time. Given 
  x,m,d, find the maximum time taken by Chef to complete the work.
*/

#include <iostream>
#include <string>
using std::cin; using std::cout;

int main()
{
    std::string result;
    int t{}, x{}, m{}, d{};

    //Get test cases
    cin>>t; cin.ignore();

    for(; t>0; --t){
        cin >> x >> m >> d;

        if (x*m < x+d){
            result.append(std::to_string(x*m));
        }
        else{
            result.append( std::to_string(x+d));
        }
    }

    for(auto res : result)
        cout << res << "\n";
    return 0;
}
