/*
 * 10264. Most Potent Corner
 * status: Accepted
 * TOPIC: bitmasks, n-dimensional cube, xor
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {

    public int []c = new int[1 << 15];
    public int []p = new int[1 << 15];

    public static void main( String [] args ) throws Exception { new Main().go(); }
    void go() throws Exception {
        int i,j,k,l,t,n,m,w;
        String s;
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while ( (s=br.readLine())!=null ) {
            st = new StringTokenizer(s);
            n = Integer.parseInt(st.nextToken());
            for ( i = 0; i < (1<<n); ++i ) {
                c[i] = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
                p[i] = 0;
            }
            for ( i = 0; i < (1<<n); ++i ) 
                for ( j = 0; j < n; ++j )
                    p[i] += c[i^(1<<j)];
            w = -(1<<29);
            for ( i = 0; i < (1<<n); ++i ) 
                for ( j = 0; j < n; ++j )
                    if ( w < p[i]+p[i^(1<<j)] )
                        w = p[i]+p[i^(1<<j)];
            System.out.println(w);
        }
    }
};

