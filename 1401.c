/*
 * 1401. Remember the Word
 * TOPIC: trie, dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN (1<<21)
#define A 26
#define FG(buff) (ptr = fgets(buff,sizeof buff,stdin))
typedef long long i64;
#define Q (1<<21)
#define MOD 20071027LL

typedef struct cell {
	struct cell *son[A];
	char is_term;
} cell ;

cell *init() {
	cell *x = (cell *)malloc(sizeof *x);
	int i;
	for ( x->is_term=0, i = 0; i < A; x->son[i++] = NULL );
	return x;
}

void push( cell *root, char *s ) {
	cell *x;
	for ( x = root; x && *s; x = x->son[*s++-'a'] ) 
		if ( !x->son[*s-'a'] ) x->son[*s-'a'] = init();
	x->is_term = 1;
}

char buff[LEN],*ptr,s[LEN];
int m,n;
cell *root;
i64 z[Q];

int main() {
	int i,j,k,cs=0;
	cell *x;
#ifndef ONLINE_JUDGE
	freopen("b.txt","r",stdin);
#endif
	for (;FG(buff+1)&&printf("Case %d: ",++cs);) {
		for ( root=init(), sscanf(FG(s),"%d",&n), i = 0; i < n; ++i, s[j] = '\0', push(root,s) ) 
			for ( FG(s), j = 0; s[j] && s[j]!='\n'; ++j );
		for ( m=1; buff[m] && buff[m]!='\n'; ++m );
		for ( buff[m--]='\0', i = 0; i <= m; z[i++] = 0 );
		for ( z[0]=1, i = 0; i < m; ++i ) 
			for ( x=root->son[buff[i+1]-'a'], j = i+1; j <= m && x; ++j ) {
				if ( x->is_term && (z[j] += z[i]) >= MOD )
					z[j] -= MOD;
				if ( buff[j+1] ) x = x->son[buff[j+1]-'a'];
			}
		printf("%lld\n",z[m]);
	}
	return 0;
}

