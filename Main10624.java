import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
    int m,n;
    public static void main( String [] args ) throws Exception {
        new Main().go();
    }
    String f( String s, int i ) {
        String t = null,r;
        if ( i == n ) 
            return s;
        BigInteger vs = new BigInteger(s);
        vs = vs.multiply(new BigInteger("10"));
        vs = vs.mod(new BigInteger(r = Integer.toString(i+1)));
        for ( int d = 0; d <= 9; ++d ) {
            if ( i >= m-1 && !vs.add(new BigInteger(Integer.toString(d))).mod(new BigInteger(r)).equals(BigInteger.ZERO) )
                continue ;
            if ( (t = f(s+Character.toString((char)(d+'0')),i+1)) != null )
                return t;
        }
        return t;
    }
    String F() {
        String t = null;
        for ( int d = 1; d <= 9; ++d ) 
            if ( (t = f(Integer.toString(d),1)) != null )
                return t;
        return t;
    }
    void go() throws Exception {
        int i,j,k,ts,cs = 0;
        Scanner scan = new Scanner(System.in);
        String s;
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            m = scan.nextInt(); n = scan.nextInt();
            if ( (s=F()) != null ) {
                System.out.println(String.format("a[%d][%d] = ",m,n)+"string(\""+s+"\");");
                // System.out.println("Case "+(++cs)+": "+s);
            }
            else System.out.println(String.format("a[%d][%d] = ",m,n)+"string(\"-1\");");
                //System.out.println("Case "+(++cs)+": "+"-1");
        }
    }
};

