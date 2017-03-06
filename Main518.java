/*
 * 518. Time
 * TOPIC: built-in libraries, java.time, very neat, good interview question
 * status: Accepted
 */

/**
 * Created by sj on 21/01/17.
 */

import java.io.*;
import java.time.*;
import java.time.temporal.TemporalUnit;
import java.util.*;

import static java.time.temporal.ChronoUnit.*;

public class Main {

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    //BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/518/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/518/src/out02.txt")));
        new Main().go();
    }

    LocalDateTime readDate() {
        int year = scan.nextInt(), month = scan.nextInt(), day = scan.nextInt();
        int hour = scan.nextInt(), min = scan.nextInt(), sec = scan.nextInt();
        LocalDateTime t = LocalDateTime.of(year,month,day,hour,min,sec);
        return t;
    }

    LocalDateTime roundUpToMonth( LocalDateTime x ) {
        if ( x.getDayOfMonth() == 1 && x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.plusMonths(1).withDayOfMonth(1).withHour(0).withMinute(0).withSecond(0);
    }
    LocalDateTime roundDownToMonth( LocalDateTime x ) {
        if ( x.getDayOfMonth() == 1 && x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.withDayOfMonth(1).withHour(0).withMinute(0).withSecond(1);
    }
    LocalDateTime roundUpToMinute( LocalDateTime x ) {
        if ( x.getSecond() == 0 )
            return x;
        return x.plusMinutes(1).withSecond(0);
    }
    LocalDateTime roundDownToMinute( LocalDateTime x ) {
        if ( x.getSecond() == 0 )
            return x;
        return x.withSecond(1);
    }
    LocalDateTime roundUpToHour( LocalDateTime x ) {
        if ( x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.plusHours(1).withMinute(0).withSecond(0);
    }
    LocalDateTime roundDownToHour( LocalDateTime x ) {
        if ( x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.withMinute(0).withSecond(1);
    }
    LocalDateTime roundUpToDay( LocalDateTime x ) {
        if ( x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.plusDays(1).withHour(0).withMinute(0).withSecond(0);
    }
    LocalDateTime roundDownToDay( LocalDateTime x ) {
        if ( x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.withHour(0).withMinute(0).withSecond(1);
    }
    LocalDateTime roundUpToYear( LocalDateTime x ) {
        if ( x.getMonthValue() == 1 && x.getDayOfMonth() == 1 && x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.plusYears(1).withMonth(1).withDayOfMonth(1).withHour(0).withMinute(0).withSecond(0);
    }
    LocalDateTime roundDownToYear( LocalDateTime x ) {
        if ( x.getMonthValue() == 1 && x.getDayOfMonth() == 1 && x.getHour() == 0 && x.getMinute() == 0 && x.getSecond() == 0 )
            return x;
        return x.withMonth(1).withDayOfMonth(1).withHour(0).withMinute(0).withSecond(1);
    }

    void go() throws Exception {
        int i,j,k;
        String period;
        while ( scan.hasNext() ) {
            LocalDateTime a = readDate(), b = readDate();
            k = scan.nextInt();
            period = scan.next();
            if ( k == 0 ) {
                bw.write("0\n");
                continue ;
            }
            switch ( period ) {
                case "second": bw.write((a.until(b,SECONDS)/k)+"\n"); break ;
                case "minute": bw.write(roundUpToMinute(a).until(roundDownToMinute(b),MINUTES)/k+"\n"); break ;
                               //bw.write((a.until(b,SECONDS)/(k*60))+"\n"); break ;
                case "hour":   bw.write(roundUpToHour(a).until(roundDownToHour(b),HOURS)/k+"\n"); break ;
                               //bw.write(a.until(b,SECONDS)/(60*60*k)+"\n"); break ;
                case "day":    bw.write(roundUpToDay(a).until(roundDownToDay(b),DAYS)/k+"\n"); break ;
                               //bw.write(a.until(b,SECONDS)/(60*60*k*24)+"\n"); break ;
                case "month": a = roundUpToMonth(a);
                              b = roundDownToMonth(b);
                              bw.write((a.until(b,MONTHS))/k+"\n");
                              break ;
                case "year":  a = roundUpToYear(a);
                              b = roundDownToYear(b);
                              bw.write((a.until(b,YEARS))/k+"\n");
                              break ;
                default: assert false ;
            }
        }
        bw.flush();
    }
}

