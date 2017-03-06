/*
 * 11236. Grocery Store
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		long i,j,k,t,sum;
		int l = 0;
		double s,p,tol = 1e-10;
		for ( i = 1; i <= 2000; ++i )
			for ( j = i; (i+j) <= 2000; ++j )
				for ( k = j; (i+j+k) <= 2000; ++k )
					for ( t = k; (sum = i+j+k+t) <= 2000; ++t ) {
						s = sum/100.00;
						p = (i*j*k*t)/100000000.00;
						if ( Math.abs(s-p) < tol )
							System.out.printf("a[%d] = \"%.2f %.2f %.2f %.2f\";\n",++l,i/100.00+tol,j/100.00+tol,k/100.00+tol,t/100.00+tol);
					}
	}
};

