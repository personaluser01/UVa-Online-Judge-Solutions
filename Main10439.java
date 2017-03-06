/*
 * 10439. Temple of Dune
 * TOPIC: complex numbers, vectors, rotations
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final double tol = 1e-9, oo = (1<<29);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	double S( double x ) { return x*x; }
	class Foo implements Comparable<Foo> {
		double x,y;
		Foo ( double x, double y ) { this.x = x; this.y = y; }
		public int compareTo( Foo other ) {
			if ( Math.abs(this.x -other.x) < tol ) {
				if ( Math.abs(this.y-other.y) < tol ) 
					return 0;
				return this.y<other.y?-1:1;
			}
			return this.x<other.x?-1:1;
		}
		public double distTo( Foo other ) {
			return Math.sqrt(S(this.x-other.x)+S(this.y-other.y));
		}
	}
	double ang( Foo a ) {
		double len = Math.sqrt(a.x*a.x + a.y*a.y), si = a.y/len, co = a.x/len;
		if ( Math.abs(co-1.00) < tol )
			return 0;
		if ( Math.abs(co+1.00) < tol )
			return -Math.PI;
		if ( co >= 0 && si >= 0 )
			return Math.acos(co);
		if ( co >= 0 && si <= 0 )
			return Math.asin(si);
		if ( co <= 0 && si >= 0 )
			return Math.acos(co);
		return -Math.PI+Math.acos(-co);
	}
	Foo []c = new Foo[3];
	boolean isAMultipleOf( double x, double y ) {
		double l = x/y;
		return Math.abs(l-(int)(l+0.5)) < 1e-3;
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),ans,n;
		double []len = new double[3],an = new double[3];
		double area,R,u,v,low,high,mid;
		int Low,High,Mid;
		Foo O;
		for(;ts-->0;) {
			for ( i = 0; i < 3; c[i++] = new Foo(scan.nextDouble(),scan.nextDouble()) );
			Arrays.sort(c);
			for ( area = 0, i = 0; i < 3; ++i ) {
				j = (i+1)%3;
				len[i] = c[i].distTo(c[j]);
				area += (c[i].x-c[j].x)*(c[i].y+c[j].y);
			}
			area = Math.abs(area);
			R = len[0]*len[1]*len[2]/2/area;
			double x0 = (c[0].x+c[1].x)/2, y0 = (c[0].y+c[1].y)/2;
			u = (c[1].y-c[0].y); v = -(c[1].x-c[0].x);
			for ( low=0, high=+oo; Math.abs(high-low)>1e-11; ) {
				mid = (low+high)/2;
				O = new Foo(x0+mid*u,y0+mid*v);
				if ( O.distTo(c[0]) <= R ) 
					low = mid;
				else high = mid;
			}
			low = (low+high)/2;
			O = new Foo(x0+low*u,y0+low*v);
			//System.out.println(O.distTo(c[0])+" "+O.distTo(c[1])+" "+O.distTo(c[2])+" "+ R);
			if ( Math.abs(O.distTo(c[2])-R) > 1e-8 )
				O = new Foo(2*x0-O.x,2*y0-O.y);
			//System.out.println(O.distTo(c[0])+" "+O.distTo(c[1])+" "+O.distTo(c[2])+" "+ R);
			for ( i = 0; i < 3; ++i )
				c[i] = new Foo(c[i].x-O.x,c[i].y-O.y);
			Arrays.sort(c);
			for ( i = 0; i < 3; ++i ) 
				an[i] = ang(c[i]);
			for ( j = 0, i = 1; i < 3; ++i )
				if ( an[i] < an[j] )
					j = i;
			for ( i = 0; i < 3; ++i ) {
				Foo t = new Foo(c[i].x*Math.cos(-an[j])-c[i].y*Math.sin(-an[j]), c[i].x*Math.sin(-an[j])+c[i].y*Math.cos(-an[j]));
				c[i] = t;
			}
			for ( i = 0; i < 3; ++i ) {
				an[i] = ang(c[i]);
				if ( an[i] < 0 ) an[i] += 2*Math.PI;
				assert 0 <= an[i] && an[i] < 2*Math.PI;
			}
			/*
			for ( i = 0; i < 3; ++i )
				System.out.println(an[i]/Math.PI*180.00);
			*/
			double w,minw = +oo;
			/*
			for ( ans = -1, n = 3; n <= 200; ++n ) {
				double phi = 2*Math.PI/n;
				boolean ok = true;
				w = 0;
				for ( i = 0; i < 3; ++i ) {
					if ( Math.abs(an[i]-0) < tol ) continue ;
					for ( Low = 0, High = n-1; Low+1<High; ) {
						Mid = (Low+High)/2;
						if ( an[i] >= phi*Mid+tol ) Low = Mid;
						else High = Mid;
					}
					w += Math.abs(phi*High-an[i]);
					if ( Math.abs(phi*High-an[i]) >= 1e-3 ) { 
						ok = false ;
					}
				}
				if ( w < minw ) { minw = w; ans = n; }
			}
			*/
			for ( ans = -1, n = 3; n <= 200; ++n )
				if ( isAMultipleOf(an[0],2*Math.PI/n) && isAMultipleOf(an[1],2*Math.PI/n) && isAMultipleOf(an[2],2*Math.PI/n) )
				{ ans = n; break; }
			System.out.println(ans);
		}
	}
};


