/*
 * 174. Strategy
 * TOPIC: simulation, technique, excellent, parsing, javascript, built-in functionality
 * status: Accepted
 */

/**
 * Created by sj on 19/02/17.
 */

import javax.script.*;
import java.io.*;
import java.util.*;

public class Main {
    private static final int MAXP = 20;
    private static int id;
    int L;
    ScriptEngineManager manager = new ScriptEngineManager();
    ScriptEngine engine = manager.getEngineByName("js");

    enum Token {
        IF("IF"),THEN("THEN"),ELSE("ELSE"),AND("AND"),OR("OR"),MY("MY"),YOUR("YOUR"),NULL("NULL"),TRADE("TRADE"),CHEAT("CHEAT"),ONE("1"),TWO("2"),EQUAL("="),NEQ("#"),LAST("LAST");
        String str;
        private Token( String str ) {
            this.str = str;
        }
        public String toString() {
            return str;
        }
    };
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringBuilder sb = new StringBuilder();
    String buff;
    int m;

    private char peek() {
        for (;m < L && (buff.charAt(m)==' '||buff.charAt(m)=='.'||buff.charAt(m)=='\n'||buff.charAt(m)=='\t'); ++m );
        return m<L?buff.charAt(m):'$';
    }

    Token nextToken() {
        assert m < buff.length();
        if ( peek() == '$' ) return null;
        for ( Token token: Token.values() )
            if ( buff.indexOf(token.str,m) == m ) {
                m += token.str.length();
                return token;
            }
        return null;
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/174/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/174/src/out02.txt")));
        new Main().go();
    }

    class Condition {
        List<Cond> c = new ArrayList<>();
        List<Token> op = new ArrayList<>();
        Condition() {
            for ( c.add(new Cond()); (peek()=='A'||peek()=='O'); op.add(nextToken()),c.add(new Cond()) );
        }
        public boolean eval( Program x,Program y ) {
            StringBuilder sb = new StringBuilder();
            for ( int i = 0; i < c.size(); ++i ) {
                if ( i >= 1 ) {
                    assert i-1 < op.size();
                    sb.append(op.get(i - 1) == Token.AND ? "&&" : "||");
                }
                sb.append(c.get(i).eval(x,y)==true?"true":"false");
            }
            try {
                Boolean b = (Boolean) engine.eval(sb.toString());
                //System.out.println("EVAL("+sb.toString()+") = "+b);
                return b;
            } catch ( Exception e ) {
                System.out.println("JS Exception: "+e.getMessage());
                e.printStackTrace();
                return false ;
            }
        }
        public String toString() {
            StringBuilder sb = new StringBuilder();
            for ( int i = 0; i < c.size(); ++i ) {
                if ( i >= 1 )
                    sb.append(" "+op.get(i-1).str+" ");
                sb.append(c.get(i).toString());
            }
            return sb.toString();
        }
    }

    class Cond {
        final Memory mem;
        final Token relation,command;
        public String toString() {
            return mem.toString()+" "+relation.toString()+" "+command.toString();
        }
        Cond() {
            mem = new Memory();
            relation = nextToken();
            command = nextToken();
        }
        public boolean eval( Program x, Program y ) {
            if ( mem.whose == Token.MY ) {
                switch ( mem.which ) {
                    case ONE: return relation==Token.EQUAL?(x.last.get(y.id)==command):(x.last.get(y.id)!=command);
                    default:  return relation==Token.EQUAL?(x.preLast.get(y.id)==command):(x.preLast.get(y.id)!=command);
                }
            }
            else {
                assert mem.whose == Token.YOUR;
                switch ( mem.which ) {
                    case ONE: return relation==Token.EQUAL?(y.last.get(x.id)==command):(y.last.get(x.id)!=command);
                    default:  return relation==Token.EQUAL?(y.preLast.get(x.id)==command):(y.preLast.get(x.id)!=command);
                }
            }
        }
    }

    class Memory {
        final Token whose, which;
        Memory() {
            whose = nextToken();
            Token last = nextToken();
            assert last == Token.LAST;
            which = nextToken();
        }
        public String toString() {
            return whose+" "+which;
        }
    }

    class IfStatement {
        final Condition c;
        final Statement a,b;
        IfStatement() {
            Token iff = nextToken();
            assert iff == Token.IF;
            c = new Condition();
            Token thenn = nextToken();
            assert thenn == Token.THEN;
            a = new Statement();
            Token elsee = nextToken();
            assert elsee == Token.ELSE;
            b = new Statement();
        }
        Token eval( Program x, Program y ) {
            if ( c.eval(x,y) )
                return a.eval(x,y);
            else return b.eval(x,y);
        }
        public String toString() {
            return "IF "+c.toString()+" THEN "+a.toString()+" ELSE "+b.toString();
        }
    }

    class Statement {
        Token command = null;
        IfStatement ifStatement = null;
        Statement() {
            if ( peek() == 'T' || peek() == 'C' )
                command = nextToken();
            else
                ifStatement = new IfStatement();
        }
        public Token eval(Program x, Program y) {
            if ( command != null )
                return command;
            assert ifStatement != null;
            return ifStatement.eval(x,y);
        }
        public String toString() {
            if ( command != null )
                return command.toString();
            else return ifStatement.toString();
        }
    }

    class Program {
        final Statement statement;
        private final int id;
        int score = 0;
        public boolean canPlayWith( Program other ) {
            return id < other.id;
        }
        public String toString() { return statement.toString(); }
        Map<Integer,Token> last = new TreeMap<>(), preLast = new TreeMap<>();
        void add( int pt ) {
            score += pt;
        }
        Program() {
            this.id = Main.id++;
            statement = new Statement();
            for ( int i = 0; i < MAXP; ++i ) {
                if ( i == id ) continue ;
                last.put(i,Token.NULL);
                preLast.put(i,Token.NULL);
            }
        }
        void playWith( Program other ) {
            if ( !canPlayWith(other) ) return ;
            Token myMove = this.statement.eval(this,other), herMove = other.statement.eval(other,this);
            if ( myMove == Token.TRADE && herMove == Token.CHEAT ) {
                this.add(-2);
                other.add(2);
            }
            else if ( myMove == Token.TRADE && herMove == Token.TRADE ) {
                this.add(1);
                other.add(1);
            }
            else if ( myMove == Token.CHEAT && herMove == Token.TRADE ) {
                this.add(2);
                other.add(-2);
            }
            else {
                this.add(-1);
                other.add(-1);
            }
            // System.out.println(String.format("%d against %d, moves = %s and %s",id,other.id,myMove.toString(),herMove.toString()));
            this.register(other,myMove);
            other.register(this,herMove);
        }

        private void register(Program other, Token myMove) {
            this.preLast.put(other.id,this.last.get(other.id));
            assert myMove != Token.NULL;
            this.last.put(other.id,myMove);
        }

        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof Program) )
                return false ;
            Program x = (Program)obj;
            return x.id == this.id;
        }
        @Override
        public int hashCode() {
            return id;
        }
    }

    void go() throws Exception {
        String s;
        List<Program> p = new ArrayList<>();
        for ( m = 0; (s = br.readLine()) != null; sb.append(s) );
        buff = sb.toString();
        assert buff.charAt(buff.length()-1) == '#';
        L = buff.length()-1;
        for (;peek() != '$'; p.add(new Program()) );
        for ( Program x: p )
            for ( Program y: p )
                if ( x.canPlayWith(y) )
                    for ( int i = 0; i < 10; ++i )
                        x.playWith(y);
        for ( Program x: p )
            bw.write(String.format("%3d",x.score)+"\n");
        /*
        for ( int i = 0; i < p.size(); ++i )
            bw.write(p.get(i).toString()+"\n");
           */
        bw.flush();
    }
}

