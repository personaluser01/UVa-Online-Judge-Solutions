/*
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.lang.Math.*;

class Main {
    public static void main( String[]args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        int i,j,k = 0,ts;
        double w,l,d,weight;
        String s;
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
        while ( ts-- > 0 ) {
            st = new StringTokenizer(br.readLine());
            l = Double.parseDouble(st.nextToken());
            w = Double.parseDouble(st.nextToken());
            d = Double.parseDouble(st.nextToken());
            weight = Double.parseDouble(st.nextToken());
            if ( !((l <= 56 && w <= 45 && d <= 25 || w+l+d <= 125) && weight <= 7) ) {
                System.out.println(0);
                continue ;
            }
            System.out.println(1); ++k;
        }
        System.out.println(k);
    }
};

