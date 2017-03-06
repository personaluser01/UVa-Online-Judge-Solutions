/*
 * 638. Finding Rectangles
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#define N 32
#define x first
#define y second
#include <fstream>
#define M 64
typedef long long i64;
using namespace std;

int n,cs,m;
char id[M][M];
pair<i64,i64> p[N];
set<string> q;
typedef pair<i64,i64> tp;

string rect( tp &a, tp &b, tp &c, tp &d ) {
  string s;
}

int main() {
  int i,j,k;
  string s;
  char tmp[0x400];
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif
  for ( ;1 == scanf("%d",&n) && n > 0; ) {
    memset(id,0,sizeof id);
    for ( i = 0; i < n; ++i ) {
      assert( 3 == scanf("%s %lld %lld",tmp,&p[i].x,&p[i].y) );
      id[p[i].x][p[i].y] = *tmp;
    }
    printf("Point set %d:",++cs);
    for ( sort(p,p+n), q.clear(), i = 0; i < n; ++i )
        for ( j = i+1; j < n; ++j )
            if ( p[i].x < p[j].x && p[i].y < p[j].y ) {
              if ( !id[p[i].x][p[j].y] || !id[p[j].x][p[i].y] )
                 continue ;
              stringstream str;
              str << id[p[i].x][p[j].y] << id[p[j].x][p[j].y] << id[p[j].x][p[i].y] << id[p[i].x][p[i].y];
              q.insert(str.str());
            }
    if ( !q.size() ) puts(" No rectangles");
    else {
      set<string>::iterator it,jt;
      for ( putchar('\n'), it = q.begin(); it != q.end(); it = jt ) {
        for ( k = 0, jt = it; jt != q.end() && k < 10; ++k, ++jt )
            printf(" %s",(*jt).c_str());
        putchar('\n');
      }
    }
  }
  return 0;
}

