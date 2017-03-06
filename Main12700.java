/*
 * 12700.
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    public static void main( String [] args ) throws Exception { new Main().go(); }
    void go() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),i,j,k,a,n,cs = 0,d;
        String s,res;
        for ( ;ts-- > 0; ) {
            n = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
            s = br.readLine();
            a = i = j = k = d = 0;
            for ( char c: s.toCharArray() ) {
                if ( c == 'A' ) continue ;
                ++k;
                if ( c == 'B' ) { ++i; continue ; }
                if ( c == 'W' ) { ++j; continue ; }
                ++d;
            }
            System.out.print("Case "+(++cs)+": ");
            if ( k == 0 )  {
                res = new String("ABANDONED");
                System.out.println(res);
                continue ;
            }
            else if ( i == j ) {
                res = new String("DRAW");
                System.out.println(res+" "+(i)+" "+d);
                continue ;
            }
            else if ( i == k ) {
                res = new String("BANGLAWASH");
                System.out.println(res);
                continue ;
            }
            else if ( j == k ) {
                res = new String("WHITEWASH");
                System.out.println(res);
                continue ;
            }
            else if ( i > j ) {
                res = new String("BANGLADESH");
                System.out.println(res+" "+i+" - "+j);
            }
            else {
                res = new String("WWW");
                System.out.println(res+" "+j+" - "+i);
            }
        }
    }
};

