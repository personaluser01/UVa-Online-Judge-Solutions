#include <bits/stdc++.h>
using namespace std;
#define N 10000

default_random_engine engine;
uniform_int_distribution<int> distribution(1,N);

int main() {
    auto dice= bind(distribution,engine);
    freopen("11649.in","w",stdout);
    cout << 200 << endl;
    for ( int ts= 200; ts--; ) {
        cout << "100000 100000" << endl;
        cout << dice() << " " << dice() << " " << dice() << endl;
        cout << dice() << " " << dice() << " " << dice() << " " << dice() << " " << dice() << " " << dice() << endl;
    }
    return 0;
}
