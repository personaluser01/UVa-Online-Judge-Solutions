/*
 * 349. Transferable voting
 * TOPIC: simulation, hard interview question
 * status: Accepted
 */

/**
 * Created by sj on 02/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 0x80;
    int m,n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/349/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/349/src/out02.txt")));
        new Main().go();
    }

    Map<Integer,Queue<Integer>> q = new TreeMap<>();

    void go() throws Exception {
        int i,j,k,invalid,cs = 0,ma,mi,realCnt;
        boolean ok,flag;
        Scanner scan;
        Set<Integer> ans;
        for ( String s; (s = br.readLine()) != null; ) {
            scan = new Scanner(s);
            n = scan.nextInt();
            m = scan.nextInt();
            if ( m == 0 && n == 0 ) break ;
            for ( invalid = 0, q.clear(), i = 0; i < m; ++i ) {
                scan = new Scanner(s = br.readLine());
                q.put(i,new LinkedList<>());
                Set<Integer> ss = new HashSet<>();
                for ( ok = true, j = 0; j < n && ok; ++j )
                    if ( (k = scan.nextInt()-1) < 0 || k >= n || ss.contains(k) ) {
                        ++invalid;
                        ok = false ;
                    }
                    else {
                        ss.add(k);
                        q.get(i).add(k);
                    }
                if ( !ok ) q.remove(i);
            }
            bw.write("Election #"+(++cs)+"\n");
            if ( invalid > 0 )
                bw.write("   "+invalid+" bad ballot(s)\n");
            realCnt = m-invalid;
            ans = null;
            do {
                flag = false ;
                Map<Integer,Integer> cnt = new TreeMap<>();
                for ( Map.Entry<Integer,Queue<Integer>> entry: q.entrySet() ) {
                    Queue<Integer> lst = entry.getValue();
                    if ( lst.isEmpty() ) continue ;
                    j = lst.peek();
                    if ( !cnt.containsKey(j) )
                        cnt.put(j,1);
                    else cnt.put(j,cnt.get(j)+1);
                }
                Set<Integer> winners = new TreeSet<>(), losers = new TreeSet<>(), advancers = new TreeSet<>();
                ma = -1; mi = (1<<29);
                for ( Map.Entry<Integer,Integer> entry: cnt.entrySet() )
                    if ( ma < entry.getValue() )
                        ma = entry.getValue();
                    else if ( mi > entry.getValue() )
                        mi = entry.getValue();
                for ( Map.Entry<Integer,Integer> entry: cnt.entrySet() )
                    if ( losers.isEmpty() && entry.getValue() == mi && mi != ma )
                        losers.add(entry.getKey());
                    else {
                        if ( entry.getValue() == ma ) winners.add(entry.getKey());
                        advancers.add(entry.getKey());
                    }
                for (Integer x : losers)
                    for (Map.Entry<Integer, Queue<Integer>> entry : q.entrySet())
                        if (entry.getValue().contains(x)) {
                            entry.getValue().remove(x);
                            flag = true;
                        }
                if ( !flag ) ans = winners;
            } while ( flag );
            if ( ans.size() >= 2 ) {
                bw.write("   The following candidates are tied:");
                for ( Integer x: ans )
                    bw.write(" "+(x+1));
                bw.write("\n");
            }
            else {
                Iterator<Integer> it = ans.iterator();
                bw.write("   Candidate "+(it.next()+1)+" is elected.\n");
            }
        }
        bw.flush();
    }
}
