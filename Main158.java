/*
 * 158. Calendar
 * TOPIC: java.time., built-in-libraries, simulation, careful simulation, excellent interview question, technique
 * status: Accepted
 */

/**
 * Created by sj on 13/02/17.
 */

import java.io.*;
import java.time.temporal.ChronoUnit;
import java.time.temporal.TemporalUnit;
import java.util.*;
import java.time.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/158/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/158/src/out02.txt")));
        new Main().go();
    }

    static int nums = 0;

    class Anniversary {
        final LocalDate date;
        final String description;
        final int priority;
        private int serialNo;
        Anniversary( LocalDate date, String description, int priority ) {
            this.date = date;
            this.description = description;
            this.priority = priority;
            serialNo = nums++;
        }
        String stars( LocalDate d ) {
            if ( date.isBefore(d) ) return "";
            long p = ChronoUnit.DAYS.between(d,date);
            if ( p > priority ) return "";
            if ( p == 0 ) return "*TODAY*";
            StringBuilder sb = new StringBuilder();
            for ( long t = priority-(p-1); t-->0; sb.append("*") ) ;
            return sb.toString();
        }
        boolean qualifies( LocalDate d ) {
            if ( date.isBefore(d) ) return false ;
            long p = ChronoUnit.DAYS.between(d,date);
            return p <= priority;
        }
        String toStr( LocalDate d ) {
            StringBuilder sb = new StringBuilder(String.format("%3d%3d",date.getDayOfMonth(),date.getMonthValue()));
            sb.append(String.format(" %-7s %s",stars(d),description));
            return sb.toString();
        }
    }

    List<Anniversary> lst = new ArrayList<>();
    Set<Anniversary> set;

    void go() throws Exception {
        int i,j,k = 0,year = Integer.parseInt(br.readLine());
        String []c;
        for ( String s; (s = br.readLine()) != null && !s.equals("#"); ) {
            if ( s.charAt(0) == 'A' ) {
                c = s.split("\\s+",5);
                lst.add(new Anniversary(LocalDate.of(year,Integer.parseInt(c[2]),Integer.parseInt(c[1])),c[4],Integer.parseInt(c[3])));
                lst.add(new Anniversary(LocalDate.of(year+1,Integer.parseInt(c[2]),Integer.parseInt(c[1])),c[4],Integer.parseInt(c[3])));
                continue ;
            }
            if ( ++k > 1 ) bw.write("\n");
            c = s.split("\\s+");
            c = c;
            final LocalDate date = LocalDate.of(year,Integer.parseInt(c[2]),Integer.parseInt(c[1]));
            bw.write(String.format("Today is:%3s%3s\n",c[1],c[2]));
            set = new TreeSet<>(new Comparator<Anniversary>() {
                @Override
                public int compare(Anniversary o1, Anniversary o2) {
                    if ( o1.date.equals(o2.date) ) {
                        String o1s = o1.stars(date), o2s = o2.stars(date);
                        if ( o1s.equals(o2s) )
                            return o1.serialNo-o2.serialNo;
                        return o2s.length()-o1s.length();
                    }
                    if ( o1.date.isBefore(o2.date) )
                        return -1;
                    return 1;
                }
            });
            for ( Anniversary a: lst )
                if ( a.qualifies(date) )
                    set.add(a);
            for ( Anniversary a: set )
                bw.write(a.toStr(date)+"\n");
        }
        bw.flush();
    }
}
