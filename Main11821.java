/*
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main ( String [] args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        int i,j,k,ts;
        StringTokenizer st;
        String s;
        BigDecimal x,sum;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
        while ( ts-- > 0 ) {
            sum = new BigDecimal("0");
            do {
                x = new BigDecimal(new StringTokenizer(br.readLine()).nextToken());
                sum = sum.add(x);
            } while ( !x.equals(BigDecimal.ZERO) );
            BigInteger ss = sum.toBigInteger();
            if ( 0 != sum.compareTo(new BigDecimal(ss)) ) {
                System.out.println(sum.stripTrailingZeros());
            }
            else 
                System.out.println(ss);
        }
    }
};

