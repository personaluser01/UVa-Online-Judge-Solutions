#include "stdio.h"
#include "math.h"

#define max(a,b) ((a)<(b)?(b):(a))
#define FOR(i,a) for(i=0;i<a;++i)
#define REP(i,a,b) for(i=a; i<b; ++i)
#define G 9.8

#define MAXM 10001
#define MAXN 1005
#define EPS 0.000001

long long S[MAXN], L[MAXN], T[MAXN], C[MAXN];
int n;
double v[MAXM];
double LOG[MAXM];

inline double Cal(int i, long long M)
{   
   return ( (double)T[i]*(LOG[M] - LOG[M - L[i]]) - G * (double)L[i] )/ ( (double)C[i] );
}

void process()
{   
   long long j, M;
   int i;
   double vv;
   double mmax = 0;
   FOR(i,MAXM) v[i] = 0;

   if (S[0] + L[0] < MAXM)
   {
      double res = Cal(0,S[0]+L[0]);
      if (res > 0) v[S[0] + L[0]] = res;
   }

   int kk;
   REP(i,1,n)
   {   
      for(j=10000 - S[i] - L[i]; j>=0; --j)
      {
         if (j==0 || fabs(v[j]) > EPS )
         {
            M = j + S[i] + L[i];
            vv = Cal(i,M);
            if (vv>0)
               v[M] = max(v[M],v[j] + vv);
         }
      }   
   }

   FOR(i,MAXM)
      mmax = max(mmax, v[i]);

   printf("%0.0lf\n", mmax);
}

int main()
{
   freopen("input.txt", "r", stdin);
   int t;
   int i,j;
   scanf("%d", &t);
   REP(i,1,MAXM)
      LOG[i] = log((double)i);
   FOR(i,t)
   {
      scanf("%d", &n);
      FOR(j,n)
      {
         unsigned int sj,lj,tj,cj;
         scanf("%u%u%u%u", &sj, &lj, &tj, &cj);
         S[j] = sj;
         L[j] = lj;
         T[j] = tj;
         C[j] = cj;
      }
      process();
   }
   return 0;
}

