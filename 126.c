/*
 * 126. The Errant Physicist
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#define N 0x100
typedef long long i64;
#define FG(s) (fgets(s,sizeof(s),stdin))

typedef struct {
	i64 coeff;
	int m[2];
} monomial;

monomial c[2][0x400],r[0x400],q[0x400];
int len[2],n;
char s[2][0x400],*ptr,out[0x400],res[2][0x400],*qtr[2];

i64 getnum() {
	i64 n=0,sign=1;
	int k;
	if (*ptr=='-')sign=-1;
	if (*ptr=='-'||*ptr=='+') ++ptr;
	if (1!=sscanf(ptr,"%lld%n",&n,&k) && (n=1) );
	else ptr+=k;
	return n*sign;
}

int read_monomial( monomial *c ) {
	if (!*ptr||*ptr=='\n') {
		if ( c ) c = NULL;
		return 0;
	}
	c->m[0] = c->m[1] = 0;
	for ( c->coeff=getnum(); *ptr == 'x'||*ptr == 'y';) {
		if ( isdigit(*(ptr+1)) )
			++ptr, c->m[*(ptr-1)-'x'] += getnum();
		else c->m[*ptr-'x'] += 1, ++ptr;
	}
	/*
	printf("Read monomial %lldx^{%d}y^{%d}\n",c->coeff,c->m[0],c->m[1]);
	*/
	return 1;
}

int cmp( const void *a, const void *b ) {
	monomial *x = (monomial *)a,
			 *y = (monomial *)b;
	if ( x->m[0] == y->m[0] ) 
		return x->m[1]-y->m[1];
	return y->m[0]-x->m[0];
}

int main() {
	int i,j,k,t,is_const;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( FG(s[0]) && 0[s[0]] != '#' && FG(s[1]) ) {
		for ( t = 0; t <= 1; ++t ) 
			for ( ptr = s[t], len[t] = 0; read_monomial(c[t]+len[t]); ++len[t] );
		for ( k = 0, i = 0; i < len[0]; ++i )
			for ( j = 0; j < len[1]; ++j, r[k].coeff?(++k):1 )
				for ( r[k].coeff = c[0][i].coeff*c[1][j].coeff, t = 0; t <= 1; ++t )
					r[k].m[t] = c[0][i].m[t]+c[1][j].m[t];
		qsort(r,k,sizeof *r,cmp);
		for ( i = 0; i < k; q[i++].coeff = 0 );
		for ( n = 0, i = 0; i < k; i = j )  {
			for ( t = 0; t <= 1; ++t ) q[n].m[t] = r[i].m[t];
			for ( j = i; j<k && 0==cmp(r+i,r+j); q[n].coeff+=r[j++].coeff );
			if ( q[n].coeff && ++n );
		}
		for ( is_const = 1, i = 0; i < n && is_const; ++i )
			if (q[i].m[0]+q[i].m[1] ) is_const = 0;
		memset(res,'\0',sizeof(res[0]));
		if ( is_const ) {
			ptr = out, qtr[0] = res[0];
			ptr += sprintf(ptr,"%lld",q[0].coeff);
			for ( i = 0; out[i]; ++i )
				res[0][i] = ' ';
			puts(res[0]);
			puts(out);
			continue ;
		}
		for ( t = 0; t <= 1; qtr[t] = res[t], ++t );
		ptr = out, i = 0;
		if ( !(labs(q[i].coeff)==1&&(q[i].m[0]+q[i].m[1])) )
				ptr += sprintf(ptr,"%lld",q[i].coeff);
		else if ( q[i].coeff < 0 )
			ptr += sprintf(ptr,"%c",'-');

			if ( q[i].m[0] > 1 ) sprintf(res[0]+(ptr-out)+1,"%d",q[i].m[0]), ptr += sprintf(ptr,"x%d",q[i].m[0]);
			else if ( q[i].m[0] == 1 ) ptr += sprintf(ptr,"x");
			if ( q[i].m[1] > 1 ) sprintf(res[0]+(ptr-out)+1,"%d",q[i].m[1]), ptr += sprintf(ptr,"y%d",q[i].m[1]);
			else if ( q[i].m[1] == 1 ) ptr += sprintf(ptr,"y");

		for ( i = 1; i < n; ++i ) {
		 ptr+=!(labs(q[i].coeff)==1&&(q[i].m[0]+q[i].m[1]))?sprintf(ptr," %c %lld",q[i].coeff>0?'+':'-',(i64)labs(q[i].coeff)):sprintf(ptr," %c ",q[i].coeff>0?'+':'-');
			if ( q[i].m[0] > 1 ) sprintf(res[0]+(ptr-out)+1,"%d",q[i].m[0]), ptr += sprintf(ptr,"x%d",q[i].m[0]);
			else if ( q[i].m[0] == 1 ) ptr += sprintf(ptr,"x");
			if ( q[i].m[1] > 1 ) sprintf(res[0]+(ptr-out)+1,"%d",q[i].m[1]), ptr += sprintf(ptr,"y%d",q[i].m[1]);
			else if ( q[i].m[1] == 1 ) ptr += sprintf(ptr,"y");
		}	
		for ( i = 0; out[i]; ++i )
			if ( !res[0][i] ) res[0][i] = ' ';
			else out[i] = ' ';
		puts(res[0]);
		puts(out);
	}
	return 0;
}
