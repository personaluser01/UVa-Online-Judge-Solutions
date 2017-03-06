/*
 * 11317. GCD+LCM
 * TOPIC: number theory, combinatorics, direct counting, logarithms, number bases
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-12
typedef long long i64;
typedef long double ld;
#define TST(k) (a[(k)>>3] & BIT((k)&7))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define CLR(k) (a[(k)>>3] &= ~BIT((k)&7))
#define SET(k) (a[(k)>>3] |= BIT((k)&7))
#define M (1<<18)
#define N (1<<21)

i64 p[M],m,n;
unsigned char a[(N>>3)+8];
long double ans,s,A,P,Q,ans1,ans2;

i64 up( long double x ) {
   i64 dx = (i64)(x+tol);
   if ( x <= 0 ) return 1;
   if ( fabs(dx-x) < tol ) return dx;
   return dx+1;
}

i64 G( long double x ) { return (i64)(x+tol); }

int main() {
   i64 t,i,j,k,l,cs=0;
#ifndef ONLINE_JUDGE
   freopen("c.txt","r",stdin);
#endif
   for ( k = 3; k < N; SET(k), k += 2 );
   for ( SET(2), k = 3; k < N; k += 2 )
      for ( j = k+k; TST(k) && j < N; CLR(j), j += k );
   for ( m = 0, i = 0; i < N; ++i ) if ( TST(i) ) p[m++] = i;
   for ( ;1 == scanf("%lld",&n) && n > 0; ) {
      for ( ans1=0.00, l=0; l<m && p[l]<=n; ans1+=log(p[l++])*s  )
         for ( s=0.00, t=1, Q=p[l],P=Q,Q*=p[l]; P<=n; P=Q,Q*=p[l], ++t )
            A=G(n/P)-G(n/Q), s+=((long double)t)*(A*G(n/Q)+((A-1)*A)/2);
      for ( ans2=0.00, l=0; l<m && p[l]<=n; ans2+=log(p[l++])*s )
         for ( s=0.00, t=1, Q=p[l],P=Q,Q*=p[l]; P<=n; P=Q,Q*=p[l], ++t )
            A=G(n/P)-G(n/Q), s+=((long double)t)*(A*(n-G(n/P))+((A-1)*A)/2);
      printf("Case %lld: %lld %lld\n",++cs,up(ans1/(100*log(10.00))),up(ans2/(100*log(10.00))));
   }
   return 0;
}

