/*
 * 10320. Cow Trouble!
 * TOPIC: geometry, trigonometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	double l,w,R,ans;
	double S( double x ) { return x*x; }
	Scanner scan = new Scanner(System.in);
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		double phi,a,b,d;
		while ( scan.hasNext() ) {
			l = scan.nextDouble();
			w = scan.nextDouble();
			R = scan.nextDouble();
			if ( l < w ) { ans = l; l = w; w = ans; }
			if ( R <= w ) 
				ans = Math.PI*S(R)*3.0/4;
			else if ( R <= l ) {
				ans = Math.PI*S(R)*3.0/4 + Math.PI*S(R-w)/4;
			}
			else if ( R <= l+w ) {
				ans = Math.PI*S(R)*3.0/4 + Math.PI*S(R-w)/4 + Math.PI*S(R-l)/4;
			}
			else {
				phi = Math.atan(l/w);
				d = Math.sqrt(l*l+w*w);
				a = Math.acos((S(d)+S(R-l)-S(R-w))/(2*(R-l)*d))-phi;
				b = phi-Math.asin((S(d)+S(R-w)-S(R-l))/(2*(R-w)*d));
				ans = Math.PI*S(R)*3.0/4.0+S(R-l)*(Math.PI/2-a)/2+S(R-w)*(Math.PI/2-b)/2+w*(R-l)*Math.sin(a)/2+l*(R-w)*Math.sin(b)/2;
			}
			System.out.printf("%.10f\n",ans);
		}
	}
};

