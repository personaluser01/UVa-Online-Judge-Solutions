/*
 * 1042. Lots of Sunlight
 * TOPIC: trigonometry
 * status: WA
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define pi (2*acos(0.00))
#define tol 1e-7
#define N 0x80
#include <float.h>
#define oo (DBL_MAX-0x400)

long double min( long double x, long double y ) { return x<y?x:y; }
long double max( long double x, long double y ) { return x>y?x:y; }
int f( long double x )  { return (int)(x+tol); }
int hr( long double x ) { return (int)(x/3600+tol); }
int mi( long double x ) { return (int)((x-3600*hr(x))/60+tol); }

int n,cs;
long double m[N],d[N],w,h,left[N],right[N],H,L,R,T,t,morning;

int sec( long double x ) {
	long double y = (x-60*mi(x)-60*60*hr(x));
	int d = (int)(y+tol), u = d+1;
	return d;
}

int main() {
	int i,j,k,idx;
	char a[N];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( T = 12*60*60+40*60, morning = 5*60*60+37*60, t = T/pi; 1 == scanf("%d",&n) && n > 0; ) {
		scanf("%Lf %Lf",&w,&h), printf("Apartment Complex: %d\n\n",++cs);
		for ( i = 0; i < n-1; scanf("%Lf %Lf",m+i,d+i), ++i );
		for ( scanf("%Lf",m+i), (right[0]=(left[0]=0)+w), i = 1; i < n; ++i )
			right[i]=(left[i]=d[i-1]+right[i-1])+w;
		for(;1==scanf("%s",a)&&0!=atoi(a);) {
			printf("Apartment %s: ",a), k = atoi(a);
			if ( (k/100) == 0 || (k%100)==0 || (k%100)>n || (k/100)>m[(k%100)-1] ) { puts("Does not exist\n"); continue ; }
			H = ((k/100)-1)*h, L = R = 0;
			for ( idx = (k%100)-1, i = idx-1; i >= 0;--i ) L = max(L,atan((m[i]*h-H)/(left[idx]-right[i])));
			for ( idx = (k%100)-1, i = idx+1; i < n; ++i ) R = max(R,atan((m[i]*h-H)/(left[i]-right[idx])));
			L = T*L/pi+morning, R = T-T*R/pi+morning;
			/*L = t*L+morning, R = t*(pi-R)+morning;*/
			printf("%02d:%02d:%02d - %02d:%02d:%02d\n\n",hr(L),mi(L),sec(L),hr(R),mi(R),sec(R));
		}
	}
	return 0;
}

