/*
 * 10203. Snow Clearing
 * status: Accepted
 */
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define N 0x80
#define S(x) ((x)*(x))
typedef long long i64;
using namespace std;
#define tol 1e-7
#define eps 1e-9

long double hungar_x,hungar_y,x[N],y[N],w;
char buff[0x400],*ptr;
int n;

int empty( char *ptr ) {
	while ( *ptr && *ptr != '\n' )
		if ( !isspace(*ptr) )
			return 0;
	return 1;
}

int main() {
	int ts,cs = 0,i,j,k;
	i64 hrs,mns;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts-- && (n=0)>=0; ) {
		if ( cs++ ) putchar('\n');
		scanf("%Lf %Lf\n",&hungar_x,&hungar_y);
		for ( w = 0; FG && !empty(ptr); ) {
			long double x0,y0,x1,y1;
			sscanf(buff,"%Lf %Lf %Lf %Lf",&x0,&y0,&x1,&y1);
			w += sqrt(S(x0-x1)+S(y0-y1));
		}
		w = (9*w)/25;
		hrs = (i64)(w/3600+tol); mns = (i64)(w/60-hrs*60+tol);
		if ( fabs(mns*60 - (w-3600*hrs)) > fabs((mns+1)*60-(w-3600*hrs)) )
			++mns;
		if ( mns == 60 ) 
			++hrs, mns = 0;
		printf("%lld:%02lld\n",hrs,mns);
	}
	return 0;
}
