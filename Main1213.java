/*
 * TOPIC: primes, sieves, dp, lazy dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    int N = 0x400+0x80, K = 0x100;
    int oo = (int)((1L<<31)-1L);
    boolean []isprime = new boolean[N];
    int []p = new int[N];
    int m = 0;
    int [][][]z = new int[N][K][K];

    public static void main( String [] args ) throws Exception{
        new Main().go();
    }
    int calcZ( int n, int k, int t ) {
        if ( 0 == n ) {
            if ( k == 0 )
                return 1;
            return 0;
        }
        assert n > 0 ;
        if ( t < 0 || k > n || k <= 0 ) return 0;
        if ( z[n][k][t] < +oo )
            return z[n][k][t];
        z[n][k][t] = 0;
        int low,high,mid;
        if ( p[t] <= n ) low = t;
        else {
            assert p[t] > n;
            if ( p[0] > n ) low = -1;
            else {
                assert p[0] <= n;
                low = 0; high = t;
                while ( low+1 < high ) {
                    mid = (low+high)/2;
                    if ( p[mid] <= n ) low = mid;
                    else high = mid;
                }
            }
        }
        for ( int i = low; i >= 0; --i )
            if ( p[i] <= n )
                z[n][k][t] = z[n][k][t] + calcZ(n-p[i],k-1,i-1);
        return z[n][k][t];
    }
    void go() throws Exception {
        int i,j,k,l,t,ts,n;
        Scanner scan = new Scanner(System.in);
        for ( i = 3; i < N; i += 2 )
            isprime[i] = true;
        isprime[2]=true;
        for ( i = 0; i < N; ++i )
            if ( isprime[i] )
                for ( j = i+i; j < N; j += i )
                    isprime[j]=false;
        m = 0;
        for ( i = 1; i < N; ++i )
            if ( isprime[i] )
                p[m++] = i;
        for ( i = 0; i < N; ++i )
            for ( j = 0; j <= 14; ++j )
                for ( t = 0; t < m; ++t )
                    z[i][j][t]=+oo;
        while ( (n = scan.nextInt()) != 0 ) {
            k = scan.nextInt();
            System.out.println(calcZ(n,k,m-1));
        }
    }
};

