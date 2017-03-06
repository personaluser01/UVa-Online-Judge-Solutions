/*
 * status: Accepted
 * TOPIC: deque
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

deque<string> q;
char buff[1 << 21],*s;

int main() {
    int i,j,k,t,n;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for (;s = fgets(buff,sizeof buff,stdin);) {
        n = strlen(buff);
        if ( buff[n-1] == '\n' ) buff[n-1] = '\0';
        for ( t = 0, i = 0; i < n; i = ++j ) {
            for ( j = i; j < n && s[j] != '[' && s[j] != ']'; ++j );
            if ( t == 1 ) q.push_back(string(buff+i,buff+j));
            if ( t == 0 ) q.push_front(string(buff+i,buff+j));
            if ( s[j] == '[' ) t = 0;
            if ( s[j] == ']' ) t = 1;
        }
        for ( ;!q.empty(); printf("%s",q.front().c_str()), q.pop_front() );
        putchar('\n');
    }
    return 0;
}

