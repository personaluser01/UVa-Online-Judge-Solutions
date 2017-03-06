/*
 * 12503. Robot Instructions
 * status: Accepted
 * TOPIC: medium, simulation, recursion
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	String []ins;
	int []arg;
	String find( int x )  {
		assert x >= 1;
		if ( arg[x] == 0 )
			return ins[x];
		assert arg[x] >= 1;
		return ins[x] = find(arg[x]);
	}
	void go() throws Exception {
		int i,j,k,l,ts,n,e;
		Pattern p1 = Pattern.compile("(\\w+)");
		Pattern p2 = Pattern.compile("([A-Z\\s]+)([\\d]+)");
		Matcher m;
		String s,t;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			n = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			ins = new String[n+2];
			arg = new int[n+2];
			for ( i = 0; i <= n; ++i )
				arg[i] = 0;
			j = 0;
			for ( i = 1; i <= n; ++i ) {
				s = br.readLine();
				m = p2.matcher(s);
				if ( m.find() ) {
					t = m.group(1);
					if ( t.contains("SAME AS") ) {
						arg[i] = Integer.parseInt(m.group(2));
						// assert( arg[i] >= 1 );
						ins[i] = find(arg[i]);
						if ( ins[i].contains("LEFT") ) {
							--j; 
							continue ;
						}
						else {
							// assert ins[i].contains("RIGHT");
							++j; continue ;
						}
					}
				}
				else {
					m = p1.matcher(s);
					// assert m.find();
					m.find();
					t = m.group(1);
					if ( t.contains("LEFT") ) {
						ins[i] = t; --j;

					}
					else {
						// assert t.contains("RIGHT");
						ins[i] = t; ++j;
					}
				}
			}
			System.out.println(j);
		}
	}
};

