/*
 * status: Accepted
 * TOPIC: regex
 */
import java.io.*;
import java.util.*;
import java.text.*;
import java.util.regex.*;

class Main {
    public static void main ( String [] args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in,"UTF-8"));
        String s;
        StringTokenizer st;
        Pattern p1 = Pattern.compile("(\\d+)[^\\d]+(\\d+)");
        Pattern p2 = Pattern.compile("(\\d+)");
        int cs = 0, ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),a,b;
        while ( ts-- > 0 ) {
            s = br.readLine();
            Matcher m = p1.matcher(s);
            if ( m.find() ) {
                a = Integer.parseInt(m.group(1));
                b = Integer.parseInt(m.group(2));
            }
            else {
                m = p2.matcher(s);
                m.find();
                a = Integer.parseInt(m.group(1));
                b = 0;
            }
            System.out.print("Case "+(++cs)+": ");
            double r = a*0.5 + b*0.05 + 1e-9;
            System.out.println(new DecimalFormat().format(r));
        }
    }
};

