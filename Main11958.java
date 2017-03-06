/*
 * 11958. Coming Home
 * status: Accepted
 * TOPIC: regex, simulation, easy
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    static String ReadLn( int len ) {
        byte []b = new byte[len+1];
        int ch = -1,i = 0;
        try {
            while ( i < len ) {
                ch = System.in.read();
                if ( ch < 0 || ch == '\n' ) break ;
                b[i++] = (byte)ch;
            }
        }
        catch ( IOException e ) {
            System.out.println(e.toString());
            return null;
        }
        return new String(b,0,i);
    }
    public static void main( String [] args ) {
        Main m = new Main();
        m.myWork();
    }
    void myWork() {
        String s,curTime;
        Pattern pattern = Pattern.compile("(\\d+)\\s*:\\s*(\\d+)\\s+(\\d+)"),
                p = Pattern.compile("(\\d+)\\s*:\\s*(\\d+)");
        StringTokenizer st;
        int ts,i,j,k,n,cs = 0,H0,M0,H1 = 0,M1 = 0,wait,minwait = (1<<29),
            noonH = 0, noonM = 0, timeTillNoon;

        s = Main.ReadLn(0x400);
        st = new StringTokenizer(s);
        ts = Integer.parseInt(st.nextToken());
        while ( ts-- > 0 ) {
            s = Main.ReadLn(0x400);
            st = new StringTokenizer(s);
            n = Integer.parseInt(st.nextToken());
            curTime = st.nextToken();
            Matcher mm = p.matcher(curTime);
			mm.find();
            H0 = Integer.parseInt(mm.group(1));
            M0 = Integer.parseInt(mm.group(2));
            if ( H0 == 0 )
                timeTillNoon = 24*60-M0;
            else 
                timeTillNoon = (24-H0)*60-M0;
            minwait = (1<<29);
            for ( i = 0; i < n; ++i ) {
                s = Main.ReadLn(0x400);
                st = new StringTokenizer(s);
                String t = st.nextToken()+" "+st.nextToken();
                Matcher matcher = pattern.matcher(t);
				if ( matcher.find() ) {
                	H1 = Integer.parseInt(matcher.group(1));
                	M1 = Integer.parseInt(matcher.group(2));
                	if ( H1 < H0 || H1 == H0 && M1 < M0 ) 
                    	wait = timeTillNoon+H1*60+M1+Integer.parseInt(matcher.group(3));
                	else
                    	wait = (H1-H0)*60+(M1-M0)+Integer.parseInt(matcher.group(3));
                	if ( wait < minwait ) minwait = wait;
				}
                if ( false && matcher.matches() ) {
                    System.out.println("Grou 1"+matcher.group(1));
                    System.out.println("Grou 2"+matcher.group(2));
                    System.out.println("Grou 3"+matcher.group(3));
                }
            }
            System.out.printf("Case %d: %d\n",++cs,minwait);
        }
    }
};

