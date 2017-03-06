/*
 * 12136. Schedule of a Married Man
 * status: Accepted
 * TOPIC: regex, intervals
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    public static void main( String [] args ) throws Exception {
        new Main().go();
    }
    class tmStamp implements Comparable<tmStamp> {
        int hh,mm;
        tmStamp( int hh, int mm ) {
            this.hh = hh; this.mm = mm;
        }
        public int compareTo( tmStamp y ) {
            if ( this.hh == y.hh ) {
                if ( this.mm == y.mm )
                    return 0;
                if ( this.mm < y.mm ) return -1;
                return 1;
            }
            if ( this.hh < y.hh ) return -1;
            return 1;
        }
    }
    void go() throws Exception {
        int i,j,k,l,t,ts,cs = 0;
        Pattern p = Pattern.compile("(\\d+):(\\d+)");
        Matcher m;
        String s;
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
        tmStamp []e = new tmStamp[4];
        while ( ts-- > 0 ) {
            st = new StringTokenizer(br.readLine());
            m = p.matcher(st.nextToken());
            m.find();
            // assert m.find();
            e[0] = new tmStamp(Integer.parseInt(m.group(1)),Integer.parseInt(m.group(2)));

            m = p.matcher(st.nextToken());
            m.find();
            // assert m.find();
            e[1] = new tmStamp(Integer.parseInt(m.group(1)),Integer.parseInt(m.group(2)));

            st = new StringTokenizer(br.readLine());
            m = p.matcher(st.nextToken());
            m.find();
            // assert m.find();
            e[2] = new tmStamp(Integer.parseInt(m.group(1)),Integer.parseInt(m.group(2)));

            m = p.matcher(st.nextToken());
            m.find();
            // assert m.find();
            e[3] = new tmStamp(Integer.parseInt(m.group(1)),Integer.parseInt(m.group(2)));

            if ( e[0].compareTo(e[3]) > 0 || e[1].compareTo(e[2]) < 0 )
                System.out.println("Case "+(++cs)+": Hits Meeting");
            else 
                System.out.println("Case "+(++cs)+": Mrs Meeting");
        }
    }
};

