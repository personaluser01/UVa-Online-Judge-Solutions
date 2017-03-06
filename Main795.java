/*
 * 795. Sandorf's Cipher
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    static String ReadLn( int len ) {
        byte []c = new byte[len];
        int i,j,k = 0,ch = -1;
        try {
            while ( k < len ) {
                ch = System.in.read();
                if ( ch < 0 || ch == '\n' ) break ;
                c[k++] = (byte)ch;
            }
            while ( (k%36) != 0 )
                c[k++] = ' ';
        }
        catch ( IOException e ) {
            return null;
        }
		if ( ch < 0 ) return null;
        return new String(c,0,k);
    }
    public static void main( String[] args ) {
        Main w = new Main();
        w.doIt();
    }
    void doIt() {
        String s;
        StringTokenizer idata;
		int [][]sandorf = new int[6][6];
	    int	[][][]a = new int[4][6][6];
		int i,j,k,t,l,ii,jj;
		for ( i = 0; i < 6; ++i )
			for ( j = 0; j < 6; ++j )
				sandorf[i][j] = 0;
		sandorf[0][1] = 1;
		sandorf[0][3] = 1;
		sandorf[0][5] = 1;
		sandorf[1][4] = 1;
		sandorf[2][2] = 1;
		sandorf[3][1] = 1;
		sandorf[3][4] = 1;
		sandorf[4][5] = 1;
		sandorf[5][3] = 1;
		for ( i = 0; i < 6; ++i )
			for ( j = 0; j < 6; ++j )
				a[0][i][j] = sandorf[i][j];
		for ( t = 1; t < 4; ++t ) {
			i = 0; 
			for ( jj = 0; jj < 6; ++jj ) {
				j = 0;
				for ( ii = 5; ii >= 0; --ii )
					a[t][i][j++] = a[t-1][ii][jj];
				i = i+1;
			}
		}
        while ( (s = Main.ReadLn(0x400)) != null ) {
            if ( s.length() == 0 ) {
                System.out.println("");
                continue ;
            }
			/*
            String r = new StringBuilder(s).reverse().toString();
            System.out.println(r);
			*/
			char [][]c = new char[6][6];
			char []e = new char[s.length()+1];
			String r = new String();
			l = 0;
			for ( k = 0; k < s.length();) {
				for ( i = 0; i < 6; ++i )
					for ( j = 0; j < 6; ++j ) 
						c[i][j] = s.charAt(k++);
				ii = l;
				for ( t = 0; t < 4; ++t ) 
					for ( i = 0; i < 6; ++i )
						for ( j = 0; j < 6; ++j )
							if ( a[t][i][j] == 1 ) 
								e[l++] = c[i][j];
				String o = new String(e,ii,l-ii);
				r = r+o;
			}
			String rr = new StringBuilder(r).reverse().toString();
			for ( i = rr.length()-1; i >= 0 && rr.charAt(i) == '#'; --i );
			System.out.println(rr.substring(0,i+1));
			assert( l == s.length() );
			// System.out.println(r);
        }
    }
};

