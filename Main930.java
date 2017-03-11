/*
 * 930. Polynomial Roots
 * TOPIC: polynomials, Ruffini method
 * status: Accepted
 */

/**
 * Created by sj on 10/03/17.
 */

import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    private final static double tol = 1e-12, INF = (1L<<50)+0.00;
    private final static int oo = (1<<29);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/930/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/930/src/out02.txt")));
        new Main().go();
    }

    class Polynomial {
        int n;
        double []c;
        Polynomial( double []c ) {
            for ( this.c = c, n = c.length; n >= 1 && abs(c[n-1]) < tol; --n ) ;
            if ( n == 0 ) n = 1;
        }
        int getDeg() {
            if ( n == 1 && abs(c[0]) < tol )
                return -oo;
            return n-1;
        }
        boolean isZero() {
            return getDeg() == +oo;
        }
        boolean isConstant() {
            return getDeg() == 0;
        }
        Polynomial derivative() {
            if ( isZero() || isConstant() )
                return new Polynomial(new double[1]);
            assert n >= 2;
            double []s = new double[n-1];
            for ( int i = n-1; i >= 1; --i )
                s[i-1] = i*c[i];
            return new Polynomial(s);
        }

        double eval( double t ) {
            double s = 0;
            for ( int i = n-1; i >= 0; s = t*s+c[i--] );
            return s;
        }

        double f( double a, double b ) {
            double low = a+tol,high = b-tol,mid;
            if ( abs(eval(low)) < tol ) return low;
            if ( eval(low) > 0 && eval(high) <= 0 ) {
                for ( ;abs(high-low) > tol; ) {
                    mid = (low+high)/2;
                    if ( eval(mid) <= 0 )
                        high = mid;
                    else low = mid;
                }
                return (low+high)/2;
            }
            else if ( eval(low) < 0 && eval(high) >= 0 ) {
                for ( ;abs(high-low) > tol; ) {
                    mid = (low+high)/2;
                    if ( eval(mid) < 0 )
                        low = mid;
                    else high = mid;
                }
                return (low+high)/2;
            }
            else return INF;
        }

        Polynomial divide( double t ) {
            double []d = new double[n-1];
            d[n-2] = c[n-1];
            for ( int i = n-3; i >= 0; --i )
                d[i] = c[i+1]+t*d[i+1];
            return new Polynomial(d);
        }

        double findRoot() {
            double []x = new double[2];
            int t;
            Polynomial q = derivative();
            for ( t = 0, x[t] = -(1<<20), x[t^1] = (1<<20); abs(x[0]-x[1]) >= 1e-5; t ^= 1 )
                x[t] = x[t^1] - eval(x[t^1])/q.eval(x[t^1]);
            return x[t];
        }
    }

    void go() throws Exception {
        int i,j,k,ts = scan.nextInt(),n;
        double []c;
        double t;
        for (;ts-->0;) {
            c = new double[(n = scan.nextInt())+1];
            for ( i = n; i >= 0; c[i--] = scan.nextDouble() );
            Polynomial p = new Polynomial(c);
            for ( i = 0; i < n-2; ++i )
                p = p.divide(scan.nextDouble());
            double D = -4*p.c[0]*p.c[2]+p.c[1]*p.c[1];
            List<Double> roots = new ArrayList<>();
            roots.add((-p.c[1]-sqrt(D))/2/p.c[2]);
            roots.add((-p.c[1]+sqrt(D))/2/p.c[2]);
            bw.write(String.format("%.1f\n",roots.get(1)));
            bw.write(String.format("%.1f\n",roots.get(0)));
        }
        bw.flush();
    }
}

