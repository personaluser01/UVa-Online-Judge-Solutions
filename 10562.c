    /*
     * 10562. Undraw the Trees
     * status: Accepted
     * TOPIC: recursion, dfs, brackets
     */
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #define N (1 << 16)
    #define FG (ptr = fgets(buff,sizeof buff,stdin))

    int seen[0x400][0x400],yes,id[0x400][0x400],n,adj[N][0x200],deg[N],m,used[N],indeed;
    char g[0x400][0x400],buff[0x400],*ptr,label[N];

    int valid( char ch ) { return ch != ' ' && ch != '\0' && ch != '\n' && ch != '-' && ch != '|' && ch != '#' && ch >= 32 && ch <= 126; }

    void recover( int line, int i, int j, int *v, int *len ) {
        int k,l,t,left,right,x,y,u[0x200],L;
        if ( line >= m ) { *len = 0; return ; }
        for ( *len = 0, k = i; k <= j; ++k )
            if ( valid(g[line][k]) ) {
                if ( seen[line][k] == yes ) { v[(*len)++] = id[line][k]; continue ; }
                seen[line][k] = yes, label[id[line][k] = x = n++] = g[line][k], deg[v[(*len)++] = x] = 0;
                if ( line+2 < m && g[line+1][k] == '|' ) {
                    assert( line+2 < m && g[line+2][k] == '-' );
                    left = right = k;
                    for (;left >= 0 && g[line+2][left] == '-'; --left );
                    for (;g[line+2][right] == '-'; ++right );
                    assert( line+3 < m );
                    recover(line+3,++left,--right,u,&L);
                    for ( l = 0; l < L; adj[x][deg[x]++] = u[l++] );
                }
            }
    }

    void dump( int x )
    { int i; if ( 0 && used[x] == indeed ) return ; used[x] = indeed; for ( putchar(label[x]), putchar('('), i = 0; i < deg[x]; dump(adj[x][i++]) ); putchar(')'); }

    int empty( char *p ) {
       while ( *ptr && *ptr != '\n' && isspace(*ptr) ) ++ptr;
       return !*ptr || *ptr == '\n';
    }

    int main() {
        int i,j,k,ts,v[0x200],L;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif
        for ( sscanf(FG,"%d",&ts); ts-- && ++yes; ) {
            for ( i = 0; i <= 200; ++i ) {
                for ( j = 0; j <= 200; ++j )
                    g[i][j] = '#';
                g[i][201] = '\0';
            }
            for ( m = 0; fgets(g[m],sizeof g[m],stdin); ++m ) {
                assert( !empty(g[m]) );
                for ( k = strlen(g[m])-1; k >= 0 && !(g[m][k] != '\n' && g[m][k] != '\0' && g[m][k] != ' '); --k );
                g[m][k+1] = '\0';
                if ( 0 == strcmp(g[m],"#") ) break ;
            }
            ++indeed;
            k = strlen(g[0]), recover(0,0,k-1,v,&L);
          if ( n == 0 ) { puts("()"); continue ; }
          putchar('(');
           for ( i = 0; i < L; dump(v[i++]) );
           puts(")");
        }
        return 0;
    }

