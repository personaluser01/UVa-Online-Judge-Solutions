/*
 * 12097. Pie
 * status: Accepted
 * TOPIC: binary search
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
    double []r = new double[1 << 16];
    double []v = new double[1 << 16];
    int m,n;
    public static void main ( String [] args ) throws Exception { new Main().go(); }
    int f( double x ) {
        int i,j,k = 0;
        for ( i = 0; i < n; ++i ) 
            k += (int)Math.floor(v[i]/x);
        return k;
    }
    void go() throws Exception {
        int i,j,k,ts;
        double R,good,bad,mid;
        Scanner scan = new Scanner(System.in);
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            n = scan.nextInt(); m = scan.nextInt();
            R = 0;
            for ( i = 0; i < n; ++i ) {
                r[i] = scan.nextDouble();
                v[i] = r[i]*r[i]*Math.PI;
                if ( R < v[i] ) R = v[i];
            }
            if ( f(R) >= m+1 ) {
                System.out.println(String.format("%.4f",R));
                continue ;
            }
            bad = R; good = 0;
            while ( Math.abs(bad-good) > 1e-7 ) {
                mid = (good+bad)/2;
                if ( f(mid)<m+1 )
                    bad = mid;
                else good = mid;
            }
            System.out.println(String.format("%.4f",good));
        }
    }
};

