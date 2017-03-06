/*
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    public static void main( String [] args ) throws Exception { new Main().go(); }
    String enc( String From, int k ) {
        int i,j,n = From.length();
        byte []c = new byte[n+1];
        for ( i = 0; i < n; ++i )
            c[i] = (byte)From.charAt(i);
        for ( i = 0; i < n; ++i )
            c[i] = (byte)((((c[i]-'a')+k)%26)+'a');
        return new String(c,0,n);
    }
    boolean fits( List<String> a, String d, int k ) {
        for ( int i = 0; i < (int)a.size(); ++i )
            if ( enc(d,k).equals((String)a.get(i)) )
                return true;
        return false;
    }
    void go() throws Exception {
        int i,j,k,m,ts;
        byte []c;
        String e,d;
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
        while ( ts-- > 0 ) {
            st = new StringTokenizer(e = br.readLine());
            List<String> L = new ArrayList<String>();
            while ( st.hasMoreTokens() ) 
                L.add(st.nextToken());
            d = br.readLine();
            List<Integer> a = new ArrayList<Integer>();
            m = 0; c = new byte[27];
            for ( k = 0; k <= 25; ++k ) 
                if ( fits(L,d,k) )
					c[m++] = (byte)(k+'a');
            System.out.println(new String(c,0,m));
        }
    }
};

