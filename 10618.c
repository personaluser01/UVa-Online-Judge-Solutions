/*
 * 10618. Tango Tango Insurrection
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
#define N (1 << 7)
#define Q (1 << (7+2+2+2))
#define oo 0xfffful
enum { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };
enum { NONE = 0, L = 1, R = 2 };
#define M(k) ((1ULL<<(k))-1ULL)

unsigned int 
enc( unsigned int k, unsigned int i, unsigned int j, unsigned int l ) 
{ return (k)|(i<<7)|(j<<9)|(l<<11); }

unsigned short z[N][4][4][3];
unsigned int p[N][4][4][3];
char s[N];

unsigned int calc_z(int,int,int,int);

void update( int k, int i, int j, int last, int pk, int pi, int pj, int pl, int dw ) {
	unsigned int w;
	if ( pj == LEFT ) {
		if ( (pi == UP||pi == DOWN) && last == L && i != pi )
			return ;
	}
	if ( pi == RIGHT ) {
		if ( (pj == UP||pj == DOWN) && last == R && j != pj )
			return ;
	}
	if ( calc_z(pk,pi,pj,pl) < +oo )
		if ( (w = calc_z(pk,pi,pj,pl)+dw) < z[k][i][j][last] ) {
			z[k][i][j][last]=w;
			p[k][i][j][last]=enc(pk,pi,pj,pl);
		}
}

void dump( int k, int i, int j, int l ) {
	int pk,pi,pj,pl;
	unsigned int u;
	if ( !k ) return ;
	u = p[k][i][j][l];
	pk = (u&M(7));
	pi = (u>>7)&3;
	pj = (u>>9)&3;
	pl = (u>>11);
	dump(pk,pi,pj,pl);
	if ( l == NONE ) {
		putchar('.');
		return ;
	}
	putchar(l==L?'L':'R');
}

unsigned int 
calc_z( int k, int i, int j, int last ) {
	unsigned short*r = z[k][i][j]+last;
	int pl;

	if ( *r < +oo )
		return *r;
	if ( (i==j) )
		return +oo;
	if ( !k ) 
		return +oo;
	assert( k >= 1 );
	if ( s[k] != '.' && last == NONE )
		return +oo;

	/*
	 * Case 1:
	 */
	if ( s[k] == '.' ) {
		if ( last == NONE ) {
			for ( pl = NONE; pl <= R; ++pl )
				update(k,i,j,last,k-1,i,j,pl,0);
			return *r;
		}
		if ( last == L ) {
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,(i+3)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+1)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+2)&3,j,pl,(pl==L?7:1));
			}
			return *r;
		}
		if ( last == R ) {
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,(j+3)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+1)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+2)&3,pl,(pl==R?7:1));
			}
			return *r;
		}
	}

	/*
	 * Case 2:
	 */
	if ( s[k] == 'U' ) {
		assert( last != NONE );
		if ( last == L ) {
			if ( i != UP )
				return +oo;
			assert( i == UP );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==L?3:1));
				update(k,i,j,last,k-1,(i+3)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+1)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+2)&3,j,pl,(pl==L?7:1));
			}
			return *r;
		}
		if ( last == R ) {
			if ( j != UP )
				return +oo;
			assert( j == UP );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==R?3:1));
				update(k,i,j,last,k-1,i,(j+3)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+1)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+2)&3,pl,(pl==R?7:1));
			}
			return *r;
		}
	}

	/*
	 * Case 3:
	 */
	if ( s[k] == 'D' ) {
		assert( last != NONE );
		if ( last == L ) {
			if ( i != DOWN )
				return +oo;
			assert( i == DOWN );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==L?3:1));
				update(k,i,j,last,k-1,(i+3)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+1)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+2)&3,j,pl,(pl==L?7:1));
			}
			return *r;
		}
		if ( last == R ) {
			if ( j != DOWN )
				return +oo;
			assert( j == DOWN );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==R?3:1));
				update(k,i,j,last,k-1,i,(j+3)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+1)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+2)&3,pl,(pl==R?7:1));
			}
			return *r;
		}
	}

	/*
	 * Case 4:
	 */
	if ( s[k] == 'L' ) {
		assert( last != NONE );
		if ( last == L ) {
			if ( i != LEFT )
				return +oo;
			assert( i == LEFT );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==L?3:1));
				update(k,i,j,last,k-1,(i+3)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+1)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+2)&3,j,pl,(pl==L?7:1));
			}
			return *r;
		}
		if ( last == R ) {
			if ( j != LEFT )
				return +oo;
			assert( j == LEFT );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==R?3:1));
				update(k,i,j,last,k-1,i,(j+3)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+1)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+2)&3,pl,(pl==R?7:1));
			}
			return *r;
		}
	}

	/*
	 * Case 5:
	 */
	if ( s[k] == 'R' ) {
		assert( last != NONE );
		if ( last == L ) {
			if ( i != RIGHT )
				return +oo;
			assert( i == RIGHT );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==L?3:1));
				update(k,i,j,last,k-1,(i+3)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+1)&3,j,pl,(pl==L?5:1));
				update(k,i,j,last,k-1,(i+2)&3,j,pl,(pl==L?7:1));
			}
			return *r;
		}
		if ( last == R ) {
			if ( j != RIGHT )
				return +oo;
			assert( j == RIGHT );
			for ( pl = NONE; pl <= R; ++pl ) {
				update(k,i,j,last,k-1,i,j,pl,(pl==R?3:1));
				update(k,i,j,last,k-1,i,(j+3)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+1)&3,pl,(pl==R?5:1));
				update(k,i,j,last,k-1,i,(j+2)&3,pl,(pl==R?7:1));
			}
			return *r;
		}
	}
	assert( 0 );
}


int main() {
	int i,j,k,l,t,n;
	unsigned int best,w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( fgets(s+1,sizeof(s),stdin) && 1[s] != '#' ) {
		for ( n = 1; s[n] && s[n] != '\n'; ++n );
		s[n--] = '\0';
		memset(z,0xffull,sizeof(z));
		z[0][LEFT][RIGHT][NONE] = 0;
		for (w=+oo,i=UP;i<=RIGHT;++i)
			for (j=UP;j<=RIGHT;++j)
				for ( l = NONE; l <= R; ++l )
					if (calc_z(n,i,j,l)<w)
						w = calc_z(n,i,j,l), best = enc(n,i,j,l);
		dump(best&127,(best>>7)&3,(best>>9)&3,best>>11);
		putchar('\n');
	}
	return 0;
}

