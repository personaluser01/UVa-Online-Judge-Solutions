/*
 * 11664. Langton's Ant
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 16
typedef long long i64;
enum { 
	BASE = 10000LL, 
	DIGL = 4, 
	LEN = 32 
};
enum{NORTH,WEST,SOUTH,EAST};

int n,xx,yy,dir,dx[]={-1,0,1,0},
				dy[]={0,-1,0,1},
				g[N+N][N+N];
char s[0x400];

int is_zero( i64 *x ) {
	int i;
	for(i=LEN-1;i>=0&&!x[i];--i);
	return i<0;
}

i64 *read_int( char *s ) {
	i64 *x = (i64 *)calloc(LEN, sizeof *x),i,j,k,t,n;
	for(k=strlen(s),i=0,j=k-1;i<j;++i,--j)
		t=s[i],s[i]=s[j],s[j]=t;
	for(;k%DIGL;s[k++]='0');
	assert((n=k)/DIGL<LEN);
	for(i=0;i<n/DIGL;++i)
		for(x[i]=0,j=i*DIGL,k=j+DIGL-1;k>=j;x[i]=10*x[i]+((i64)(s[k--]-'0')));
	return x;
}

void dec2bin( i64 *x, char *p ) {
	i64 i,j,k,rem,tmp;
	for(k=0;!is_zero(x);p[k++]=rem+'0') 
		for(rem=0,i=LEN-1;i>=0;--i)
			tmp=((rem*BASE+x[i])&1),x[i]=((rem*BASE+x[i])>>1),rem=tmp;
	for (;k<n*n;p[k++] = '0');
	for(p[k]='\0',i=0,j=k-1;i<j;++i,--j)
		tmp=p[i],p[i]=p[j],p[j]=tmp;
}

int next_move(int *x, int*y, int *d) {
	((g[*x][*y]^=1)==1)?((*d)+=1,(*d)&=3,(*x)+=dx[*d],(*y)+=dy[*d]):((*d)+=3,(*d)&=3,(*x)+=dx[*d],(*y)+=dy[*d]);
	return !((*x)<0||(*x)>=n||(*y)<0||(*y)>=n);
}

int main() {
	int i,j,k;
	i64 *z;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(4==scanf("%d%s%d%d",&n,s,&xx,&yy)&&n){
		z=read_int(s),dec2bin(z,s);
		for(k=0,i=n-1;i>=0;--i)
			for(j=0;j<n;++j)
				g[i][j]=s[k++]-'0';
		for(--xx,--yy,i=n-1-yy,j=xx,xx=i,yy=j,dir=NORTH;!(xx==0&&yy==n-1)&&next_move(&xx,&yy,&dir););
		puts(xx==0&&yy==n-1?"Yes":"Kaputt!");
	}
	return 0;
}

