/*
 * 245. Uncompress
 * status: Accepted
 * TOPIC: binary heaps, heaps with updates, simulation, stl set, stl map
 */
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#define oo (1L << 29)
#define LEN 51
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define bubble (swap(heap[i],heap[j]),swap(pos[heap[i]],pos[heap[j]]))
using namespace std;

set<string> s;
map<string,int> m;
char buff[1L<<21],*ptr;
int heap[1 << 21],Cnt,pos[1 << 21],d[1 << 21],V,o[1 << 21],*tt;
map<int,string> a;

bool the_end( char *s ) {
    char *qtr = s;
    bool found_zero = false,
         smth_else = false;
    for (;*qtr && *qtr != '\n'; ++qtr ) 
        if ( isspace(*qtr) || *qtr != '0' )
            return false;
        else if ( *qtr == '0' )
            found_zero = true;
    return found_zero && !smth_else;
}

void heap_push( int x ) {
    int i,j;
    if ( pos[x] < 0 )
        pos[heap[Cnt]=x]=Cnt, ++Cnt;
    for ( j = pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j = i );
}

int heap_pop() {
    int i,j,x = *heap;
    if ( (pos[x] = -1, --Cnt) )
        pos[*heap=heap[Cnt]]=0;
    for ( j=0; (i=j,j<<=1,++j)<Cnt; bubble ) {
        if ( j<Cnt-1 && d[heap[j+1]]<=d[heap[j]] ) ++j;
        if ( d[heap[i]]<=d[heap[j]] ) break ;
    }
    return x;
}

bool is_word( string &s ) {
    for ( int i = 0; i < (int)s.size(); ++i )
        if ( isalpha(s[i]) )
            return true;
    return false;
}

int main() {
    int i,j,k,l,t;
    char w[0x400],*qtr;
    string e;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for (;FG && !the_end(buff); putchar(*ptr) ) {
        while ( *ptr && *ptr != '\n' ) {
            if ( !isalnum(*ptr) ) {
                putchar(*ptr++);
                continue ;
            }
            for ( qtr = w; *ptr && *ptr != '\n' && isalnum(*ptr); *qtr++ = *ptr++ );
            *qtr = '\0', e = string(w);
            if ( !is_word(e) ) {
                i = atoi(w);
                goto next;
            }
            if ( s.find(e) == s.end() ) {
                s.insert(e), pos[i=m[e]=++V]=-1, a[i]=e;
                if ( !Cnt ) d[i] = (1L<<16), heap_push(i);
                else { 
                    d[i]=d[*heap]-1,heap_push(i); 
                    assert( *heap==i ); 
                }
            }
            else {
                next:
                assert( Cnt >= i );
                for ( j = i, tt = o, k = 0; k < j-1 && Cnt; ++k )
                    *tt++ = heap_pop();
                i = heap_pop();
                if ( tt > o ) d[i] = d[o[0]]-1;
                for ( *tt++ = i; tt >= o; heap_push(*--tt) );
            }
            printf("%s",a[i].c_str());
        }
    }
    return 0;
}

