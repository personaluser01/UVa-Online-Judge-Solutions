/*
 * 10022. Delta-wave
 * TOPIC: simulation, grids
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	long m,n;
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	class Coord {
		long x,y;
		Coord( long n ) {
			long m = (long)Math.sqrt(n), mid;
			if ( m*m < n ) ++m;
			mid = (m*m+(m-1)*(m-1)+1)/2;
			this.y = m;
			this.x = n-mid;
		}
        void setX( long x ) { this.x = x; }
        void setY( long y ) { this.y = y; }

        long g( long a, long b ) {
            long diff = Math.abs(a-b);
            return (diff<<1)-(diff&1);
        }

        boolean hasStickAbove( long x, long y ) {
            return (x&1) != (y&1);
        }
        boolean hasStickBelow( long x, long y ) {
            return (x&1) == (y&1);
        }


        long f( long x0, long y0, long x1, long y1 ) {
            long d = 0,h = 1+Math.abs(x1);
            if ( y0 > y1 )
                return f(x1,y1,x0,y0);
            // assert y0 <= y1;
            if ( x0 == x1 && y0 == y1 )
                return 0;
            while ( true ) {
                if ( x0 == x1 && y0 == y1 )
                    return d;
                assert y0 <= y1;
                if ( !hasStickBelow(x1,y1) ) {
                    if ( x0 < x1 ) --x1;
                    else ++x1;
                    assert 1-y1 <= x1 && x1 <= y1-1;
                    assert hasStickBelow(x1,y1); 
                    ++d;
                }
                if ( !hasStickAbove(x0,y0) ) {
                    if ( x0 < x1 ) ++x0;
                    else --x0;
                    assert 1-y0 <= x0 && x0 <= y0-1;
                    assert hasStickAbove(x0,y0); 
                    ++d;
                }
                if ( x0 == x1 )
                    return d+g(y0,y1);
                if ( y0 == y1 )
                    return d+Math.abs(x0-x1);
                ++d; ++y0;
            }
        }

		long distTo( Coord other ) {
            return f(this.x,this.y,other.x,other.y);
		}
		long getX() { return this.x; }
		long getY() { return this.y; }
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int i,j,k,ts = scan.nextInt();
		for ( ;ts-- > 0; ) {
			m = scan.nextLong();
			n = scan.nextLong();
			Coord a = new Coord(m);
			Coord b = new Coord(n);
			// System.out.println(a.getX()+" "+a.getY());
			// System.out.println(b.getX()+" "+b.getY());
			System.out.println(a.distTo(b));
			if ( ts > 0 ) System.out.println("");
		}
	}
};

