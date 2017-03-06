/*
 * 1047. Zones
 * TOPIC: bitmasks, inclusion-exclusion
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef long long i64;


int bts[1 << 21];
i64 e[1 << 21];

    void go() {
		int n,m,i,j,k,l,common,cs = 0;
        i64 max_weight,ax;
        unsigned int u,v,mask;
		while ( 1 ) {
            scanf("%d %d",&n,&m);
			if ( n == 0 && m == 0 ) break ;
            for ( u = 0; u < (1<<n); ++u ) e[u] = 0;
			for ( i = 0; i < n; ++i ) 
                scanf("%lld",&e[1<<i]);
            scanf("%d",&common);
			for ( i = 0; i < common; ++i ) {
				for ( u = 0, scanf("%d",&l); l--; ) {
                    scanf("%d",&j);
					u |= (1<<(j-1));
				}
                scanf("%lld",e+u);
			}
            max_weight = 0; mask = 0;
            for(v=0;v<(1<<n);++v) {
                if ( bts[v] != m ) continue ;
                for ( ax=0,u=v; u; u = ((u-1)&v) ) {
                    if ( (bts[u]&1)==1 )
                        ax += e[u];
                    else ax -= e[u];
                }
                if ( ax > max_weight ) { 
                    max_weight=ax; 
                    mask=v;
                }
            }
			printf("Case Number %d \n",++cs);
            printf("Number of Customers: %lld\nLocations recommended:",max_weight);
            for(i=0;i<n;++i)
                if ( (mask>>i)&1 )
                    printf(" %d",i+1);
			puts(" \n ");
		}
	}

int main() {
    unsigned int k;
        for ( k = 0; k < (1 << 21); ++k ) bts[k] = bts[k>>1]+(k&1);
        go();
        return 0;
}

