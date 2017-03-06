/*
 * 586. Instant Complexity
 * TOPIC: parsing
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {

    int DEG = 12;

    String BEGIN = new String("BEGIN");
    String END = new String("END");
    Scanner scan = new Scanner(System.in);

    public static void main ( String [] args ) throws Exception { new Main().go(); }

    class polyCoeffs {
        int []c = new int[DEG];
        void add( polyCoeffs other ) {
            for ( int i = 0; i < DEG; ++i )
                this.c[i] += other.c[i];
        }
        void sub( polyCoeffs other ) {
            for ( int i = 0; i < DEG; ++i )
                this.c[i] -= other.c[i];
        }
        polyCoeffs () {
            for ( int i = 0; i < DEG; ++i )
                this.c[i] = 0;
        }
        polyCoeffs ( int[] g ) {
            for ( int i = 0; i < DEG; ++i )
                this.c[i] = g[i];
        }
        int getC( int i ) {
            return this.c[i];
        }
        polyCoeffs mult( polyCoeffs a, polyCoeffs b ) {
            int []g = new int[DEG];
            for ( int i = 0; i < DEG; ++i )
                for ( int j = 0; i+j < DEG; ++j )
                    g[i+j] += a.getC(i)*b.getC(j);
            return new polyCoeffs(g);
        }
        void shiftUp() {
            int []g = new int[DEG];
            for ( int i = 0; i < DEG-1; ++i )
                g[i+1] = this.c[i];
            for ( int i = 0; i < DEG; ++i )
                this.c[i] = g[i];
        }
        void multEach( int k ) {
            for ( int i = 0; i < DEG; ++i )
                this.c[i] *= k;
        }
        void addTo( int idx, int d ) {
            this.c[idx] += d;
        }
        public void display() {
            int i,j = 0;
            for ( i = DEG-1; i >= 0 && this.c[i] == 0; --i );
            if ( i < 0 ) {
                System.out.println("0");
                return ;
            }
            for (;i >= 0; --i ) {
                if ( this.c[i] == 0 ) continue ;
                if ( (++j) >= 2 ) System.out.print("+");
                if ( i == 0 ) {
                    System.out.print(this.c[i]);
                    continue ;
                }
                if ( this.c[i] != 1 )
                    System.out.print(this.c[i]+"*n");
                else 
                    System.out.print("n");
                if ( i >= 2 )
                    System.out.print("^"+i);
            }
            System.out.println("");
        }
    }
    polyCoeffs oneStatement() throws Exception {
        polyCoeffs res = null,dr;
        String s = scan.next(),t,r,q;
        if ( s.equals(END) )
            return res;
        if ( s.equals("LOOP") ) {
            t = scan.next();
            res = new polyCoeffs();
            dr = readSTL();
            if ( t.equals("n") ) {
                dr.shiftUp();
            }
            else {
                dr.multEach(Integer.parseInt(t));
            }
            res.add(dr);
        }
        else if ( s.equals("OP") ) {
            res = new polyCoeffs();
            t = scan.next();
            res.addTo(0,Integer.parseInt(t));
        }
        return res;
    }
    polyCoeffs readSTL() throws Exception {
        polyCoeffs res = new polyCoeffs(),p;
        for (;(p = oneStatement()) != null; res.add(p) );
        return res;
    }
    polyCoeffs progAnalyzer() throws Exception {
        String s = scan.next();
        polyCoeffs res;
        // assert s.equals(BEGIN);
        res = readSTL();
        return res;
    }
    void go() throws Exception {
        int i,j,k,l,t,ts,cs = 0;
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            System.out.println("Program #"+(++cs));
            System.out.print("Runtime = ");
            polyCoeffs p = progAnalyzer();
            p.display();
            System.out.println("");
        }
    }
};


