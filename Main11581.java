/*
 * 11581. Grid Successors
 * status: Accepted
 * TOPIC: cycles, dp
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    public boolean []seen = new boolean[512];
    int []m = new int[512];
    int []len = new int[512];
    int []visited = new int[512];
    int yes = 0;
    int []dp = new int[512];
    public static void main( String [] args ) throws Exception { new Main().go(); }
    boolean []is_in_cycle = new boolean[512];
    int nx( int u ) {
        int [][]g = new int[5][5];
        int [][]t = new int[5][5];
        int i,j,k = 0,di,dj,ni,nj,v = 0;
        for ( i = 1; i <= 3; ++i )
            for ( j = 1; j <= 3; ++j ) {
                g[i][j] = ((u>>k)&1);
                ++k;
            }
        for ( i = 1; i <= 3; ++i ) 
            for ( j = 1; j <= 3; ++j )
                t[i][j] = ((g[i-1][j]+g[i][j-1]+g[i+1][j]+g[i][j+1])&1);
        k = 0;
        for ( i = 1; i <= 3; ++i )
            for ( j = 1; j <= 3; ++j ) {
                v |= (t[i][j]<<k);
                ++k;
            }
        return v;
    }
    boolean in_cycle( int src, int x, int dist ) {
        if ( dist > 0 && x == src )
            return true;
        if ( visited[x] == yes ) return false;
        visited[x] = yes;
        return in_cycle(src,m[x],dist+1);
    }
    int calc_dp( int x ) {
        if ( dp[x] > 0 )
            return dp[x];
        if ( is_in_cycle[x] )
            return dp[x] = 0;
        return dp[x] = 1+calc_dp(m[x]);
    }
    void go() throws Exception {
        int i,j,k,ts,di,dj,ni,nj,u;
        String s;
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        for ( k = 0; k < 512; ++k ) m[k] = nx(k);
        for ( k = 0; k < 512; ++k ) {
            ++yes;
            if ( !(is_in_cycle[k] = in_cycle(k,k,0)) ) {
                calc_dp(k);
            }
        }

        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());

        while ( ts-- > 0 ) {
            br.readLine();
            k = 0; u = 0;
            for ( i = 0; i < 3; ++i ) {
                s = br.readLine();
                for ( j = 0; j < 3; ++j ) {
                    if ( s.charAt(j) == '1' )
                        u|=(1<<k);
                    ++k;
                }
            }
            if ( is_in_cycle[u] ) {
                System.out.println("-1");
                continue ;
            }
            System.out.println(dp[u]-1);
        }
    }
};

