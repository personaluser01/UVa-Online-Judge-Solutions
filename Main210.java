/*
 * 210. Concurrency Simulator
 * TOPIC: ad hoc
 * status: Accepted
 * NOTES: beware of things like "printz"!
 */

/**
 * Created by sj on 19/01/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    enum Command { ASS, PRINT, LOCK, UNLOCK, END };
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        //System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/210/src/input.txt")));
        //System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/210/src/out02.txt")));
        new Main().go();
    }

    Map<Command,Integer> times = new TreeMap<>();
    int n,quantum;
    int []v = new int[26];
    boolean locked;

    static int getArgs( String s ) {
        Pattern p = Pattern.compile("([a-z])\\s*=\\s*(\\d+)");
        Matcher m = p.matcher(s);
        m.find();
        int ch = m.group(1).charAt(0)-'a';
        int val = Integer.parseInt(m.group(2));
        return ch|(val<<5);
    }

    static boolean isAssignment( String s ) {
        Pattern p = Pattern.compile("([a-z])\\s*=\\s*(\\d+)");
        Matcher m = p.matcher(s);
        boolean res = m.find();
        return res;
    }

    class Program {
        final int id;
        List<Command> lst;
        Map<Integer,String> m;
        Scanner scan;
        int currentLineOfExecution = 0;
        Program( int id ) throws Exception {
            this.id = id;
            lst = new ArrayList<>();
            m = new TreeMap<>();
            for ( String s, tok; (s = br.readLine()) != null && !(tok = (scan = new Scanner(s)).next()).equals("end"); )
                switch ( tok ) {
                    case "print": lst.add(Command.PRINT); m.put(lst.size()-1,scan.next()); break ;
                    case "lock": lst.add(Command.LOCK); break ;
                    case "unlock": lst.add(Command.UNLOCK); break ;
                    default: if ( isAssignment(s) ) { lst.add(Command.ASS); m.put(lst.size()-1,s); }
                             else if ( s.substring(0,5).equals("print") ) {
                                lst.add(Command.PRINT);
                                m.put(lst.size()-1,s.substring(5,6));
                             }
                             break ;
                }
        }
        public void executeNextChunk() throws Exception {
            Command c = null;
            for ( int k = quantum; k > 0 && currentLineOfExecution < lst.size(); ++currentLineOfExecution, k-=times.get(c) ) {
                c = lst.get(currentLineOfExecution);
                switch ( c ) {
                    case ASS: int u = getArgs(m.get(currentLineOfExecution));
                                v[u&31] = u>>5;
                                break ;
                    case PRINT: bw.write((id+1)+": "+v[m.get(currentLineOfExecution).charAt(0)-'a']+"\n");
                                break ;
                    case LOCK: if ( locked ) {
                                    blockedQueue.addLast(this);
                                    return ;
                                }
                                locked = true ;
                                break ;
                    case UNLOCK: assert locked;
                                locked = false ;
                                if ( !blockedQueue.isEmpty() )
                                    readyQueue.addFirst(blockedQueue.pollFirst());
                                break ;
                    default: assert false ;
                }
            }
            if ( currentLineOfExecution < lst.size() )
                readyQueue.addLast(this);
        }
    }

    Program []p = new Program[0x80];
    Deque<Program> readyQueue = new LinkedList<>(), blockedQueue = new LinkedList<>();

    void runSimulation() throws Exception {
        Program running = null;
        int i,j,k;
        for ( i = 0; i < 26; v[i++] = 0 );
        readyQueue.clear(); blockedQueue.clear(); locked = false ;
        for ( i = 0; i < n; readyQueue.addLast(p[i++]) );
        for ( ;!readyQueue.isEmpty(); readyQueue.pollFirst().executeNextChunk() ) ;
    }

    void go() throws Exception {
        int i,j,k,ts,cs = 0;
        String s;
        for ( ts = Integer.parseInt(br.readLine()), br.readLine(); ts-->0; br.readLine() ) {
            if ( ++cs > 1 ) bw.write("\n");
            Scanner scan = new Scanner(br.readLine());
            times.clear();
            n = scan.nextInt();
            for ( Command x: Command.values() )
                times.put(x,scan.nextInt());
            quantum = scan.nextInt();
            for ( i = 0; i < n; ++i )
                p[i] = new Program(i);
            runSimulation();
        }
        bw.flush();
    }
}
