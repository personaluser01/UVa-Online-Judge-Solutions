/*
 * 995. Super Divisible Numbers
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 51
#define oo 0xfffffffful
typedef long long i64;

i64 B,d[0x400];
char str[0x400],s[L][0x400],*qtr,move[L][L];
int is[0x400],yes,m,max_k,cur;
unsigned int z[L][L];

void recover( int k, int r ) {
	if ( k == 1 ) {
		*qtr++ = d[z[k][r]]+'0';
		return ;
	}
	recover(k-1,move[k][r]);
	*qtr++ = d[z[k][r]]+'0';
}

int main() {
	int i,j,k,r,nr;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %s",&B,str) ) {
		for ( ++yes, i = 0; str[i]; is[str[i++]-'0'] = yes );
		for ( m = 0, i = 0; i < B; ++i )
			if ( is[i] == yes )
				d[m++] = i;
		memset(z,0xff,sizeof(z));
		for ( i = m-1; i >= 0; --i )
			if ( d[i] ) 
				if ( z[1][(B*d[i]) % 2] == +oo ) 
					z[1][(B*d[i]) % 2] = i;
		max_k = 1;
		for ( k = 2; k < L; ++k ) 
			for ( r = 0; r < k; ++r )
				if ( z[k-1][r] < +oo )
					for ( i = m-1; i >= 0; --i )
						if ( !((r+d[i]) % k) )
							if ( z[k][nr = ((r+d[i])*B)%(k+1)] == +oo )
								z[k][nr] = i, move[k][nr] = r, max_k = k, printf("max_k = %d, r = %d\n",max_k,r);;
		for ( cur = -1, r = 0; r <= max_k; ++r )
			if ( z[max_k][r] < +oo )
				++cur, qtr = s[cur], recover(max_k-1,move[max_k][r]), *qtr = '\0';
		for ( j = 1; j; )
			for ( j = 0, i = 0; i < cur; ++i )
				if ( strcmp(s[i],s[i+1]) > 0 && ++j )
					strcpy(tmp,s[i]), strcpy(s[i],s[i+1]), strcpy(s[i+1],tmp);
		printf("%s\n",s[cur]);
	}
	return 0;
}
