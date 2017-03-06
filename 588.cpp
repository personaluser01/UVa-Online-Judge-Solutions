/*
 * 588. Video Surveillance
 * TOPIC: nice neat ad hoc, polygons, geometry, point visibility, geometric loci
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;
#define N 0x200
#define oo (1LL << 43)

int n;
i64 x[N],y[N];

struct segment {
  i64 x,y;
  segment( i64 x, i64 y ) {
    this->x = x;
    this->y = y;
  }
};

segment make_segment( i64 x, i64 y ) {
  segment s(x,y);
  if ( x > y )
    s.x = 0, s.y = -1;
  return s;
}

segment operator *( const segment &I, const segment &J ) {
  i64 x = max(I.x,J.x), y = min(I.y,J.y);
  return make_segment(x,y);
}

bool is_empty( const segment &I ) { return I.x > I.y; }

segment ms( i64 x, i64 y ) {
  segment s(min(x,y),max(x,y));
  return s;
}

int f() {
  segment H(-oo,+oo),V(-oo,+oo);
  int i,j,k,h;

  for ( i = 0; i < n; ++i ) {
    h = ((i-1+n)%n), j = ((i+1)%n);
    if ( x[i] == x[j] ) {
      if ( y[i] > y[j] && x[h] < x[i] ) {
        H = H*ms(x[i],+oo);
        V = V*ms(y[i],+oo);
      }
      if ( y[i]> y[j] && x[h] > x[i] ) {
        H = H*ms(x[i],+oo);
        V = V*ms(-oo,y[i]);
      }
      if ( y[i] < y[j] && x[h] > x[i] ) {
        H = H*ms(-oo,x[i]);
        V = V*ms(-oo,y[i]);
      }
      if ( y[i] < y[j] && x[h] < x[i] ) {
        H = H*ms(-oo,x[i]);
        V = V*ms(y[i],+oo);
      }
    }
    else {
      assert( y[i] == y[j] );
      if ( x[i] < x[j] && y[h] > y[i] ) {
        H = H*ms(x[i],+oo);
        V = V*ms(y[i],+oo);
      }
      if ( x[i] < x[j] && y[h] < y[i] ) {
        H = H*ms(-oo,x[i]);
        V = V*ms(y[i],+oo);
      }
      if ( x[i] > x[j] && y[h] > y[i] ) {
        H = H*ms(x[i],+oo);
        V = V*ms(-oo,y[i]);
      }
      if ( x[i] > x[j] && y[h] < y[i] ) {
        H = H*ms(-oo,x[i]);
        V = V*ms(-oo,y[i]);
      }
    }
  }
  return !is_empty(H)&&!is_empty(V);
}

int main() {
  int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
#endif
  for (;1 == scanf("%d",&n) && n > 0 && printf("Floor #%d\n",++cs); ) {
    for ( i = n-1; i >= 0; --i )
      scanf("%lld %lld",x+i,y+i);
    if ( f() ) puts("Surveillance is possible.\n");
    else puts("Surveillance is impossible.\n");
  }
}
