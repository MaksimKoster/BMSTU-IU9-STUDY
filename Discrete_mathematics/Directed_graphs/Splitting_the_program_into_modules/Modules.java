import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Stack;


class tag{
    public static final String MINUS = "-";
    public static final String PLUS = "+";
    public static final String MULTI = "*";
    public static final String DIV = "/";
    public static final String EQUAL = "==";
    public static final String NOT_EQUAL = "!=";
    public static final String LESS_EQ = "<=";
    public static final String LESS = "<";
    public static final String MORE_EQ = ">=";
    public static final String MORE = ">";
    public static final String QUESTION = "?";
    public static final String LBRACKET = "(";
    public static final String RBRACKET = ")";
    public static final String SEMICOLON = ";";
    public static final String COLON = ":";
    public static final String COMMA = ",";
    public static final String ASSIGNMENT = ":=";
    public static final String IDENT = "IDENT";
    public static final String NUMBER = "NUMBER";
}

class Lexem {
    String line, func;
    ArrayList<String> tags;
    ArrayList<String> ident;
    ArrayList<String> vars;
    boolean assignment = false;
    int count = 0, count_args = 0, j = 0, n;


    Lexem(String line, int n) {
        this.line = line;
        tags = new ArrayList<>();
        ident = new ArrayList<>();
        vars = new ArrayList<>();
        this.n = n;
    }

    public boolean checkTags(String x){
        if (x.equals("parse_ident")) { return count < tags.size() && tags.get(count).equals(tag.COMMA);}
        if (x.equals("parse_expr")){ return count < tags.size() && tags.get(count).equals(tag.QUESTION);}
        if (x.equals("parse_comparison")) { return tags.get(count).equals(tag.EQUAL) || tags.get(count).equals(tag.NOT_EQUAL) || tags.get(count).equals(tag.LESS) || tags.get(count).equals(tag.MORE) || tags.get(count).equals(tag.MORE_EQ) || tags.get(count).equals(tag.LESS_EQ); }
        if (x.equals("parse_actual")){ return count < tags.size() && (tags.get(count).equals(tag.NUMBER) || tags.get(count).equals(tag.IDENT) || tags.get(count).equals(tag.LBRACKET) || tags.get(count).equals(tag.MINUS));}
        if (x.equals("parse_factor")) {return tags.get(count).equals(tag.NUMBER) || tags.get(count).equals(tag.IDENT) || tags.get(count).equals(tag.LBRACKET) || tags.get(count).equals(tag.MINUS);}
        return false;
    }
    public void findLexem(Modules X) {
        String s = line;
        for (int i = 0; i < s.length(); i++) {
            char token = (s.charAt(i));
            if (token == ' ') {
                continue;
            }

            if (token == '+') {
                tags.add(tag.PLUS);
                continue;
            }

            if (token == '-') {
                tags.add(tag.MINUS);
                continue;
            }

            if (token == '*') {
                tags.add(tag.MULTI);
                continue;
            }

            if (token == '/') {
                tags.add(tag.DIV);
                continue;
            }

            if (token == '=') {
                tags.add(tag.EQUAL);
                continue;
            }

            if (token == '<') {
                i++;
                char next_tok = s.charAt(i);

                if (next_tok == '>') {
                    tags.add(tag.NOT_EQUAL);
                    continue;
                }

                if (next_tok == '=') {
                    tags.add(tag.LESS_EQ);
                    continue;
                }

                i--;
                tags.add(tag.LESS);
                continue;
            }

            if (token == '>') {
                i++;
                char next_tok = s.charAt(i);
                if (next_tok == '=') {
                    tags.add(tag.MORE_EQ);
                    continue;
                }
                i--;
                tags.add(tag.MORE);
                continue;
            }

            if (token == '?') {
                tags.add(tag.QUESTION);
                continue;
            }

            if (token == ',') {
                tags.add(tag.COMMA);
                continue;
            }

            if (token == '(') {
                tags.add(tag.LBRACKET);
                count++;
                continue;
            }

            if (token == ')') {
                tags.add(tag.RBRACKET);
                if (count == 1) {
                    X.func_HM.put(func, count_args);
                    X.help.add(n, func);
                }
                count++;
                continue;
            }

            if (token == ';') {
                tags.add(tag.SEMICOLON);
                continue;
            }

            if (token == ':') {
                i++;
                if (s.charAt(i) == '=') {
                    tags.add(tag.ASSIGNMENT);
                    assignment = true;
                    continue;
                }
                i--;
                tags.add(tag.COLON);
                continue;
            }

            if (Character.isDigit((s.charAt(i)))) {
                tags.add(tag.NUMBER);
                while (i < s.length() && Character.isDigit(s.charAt(i))) {
                    i++;
                }
                i--;
                continue;
            }

            if (Character.isAlphabetic(s.charAt(i))) {
                tags.add(tag.IDENT);
                StringBuilder var = new StringBuilder(s.charAt(i) + "");
                i++;
                while (i < s.length() && (Character.isAlphabetic(s.charAt(i)) || Character.isDigit(s.charAt(i)))) {
                    var.append(s.charAt(i));
                    i++;
                }
                i--;
                if (count == 1) {
                    ident.add(var.toString());
                    count_args++;
                }
                if (count == 0)
                    func = var.toString();
                if (assignment)
                    vars.add(var.toString());
                continue;
            }
            new Exception();
        }
    }

    public int findIdent( String var, int n, Modules X){
        j++;
        int lBracket = 1;
        int comma = 0;
        int i;
        n += 2;
        for (i = n; lBracket != 0; i++) {
            if (tags.get(i).equals(tag.COMMA)) {
                comma++;
                continue;
            }
            if (tags.get(i).equals(tag.LBRACKET)) {
                lBracket++;
                continue;
            }
            if (tags.get(i).equals(tag.IDENT)) {
                if (X.func_HM.containsKey(vars.get(j))) {
                    i = findIdent(vars.get(j), i, X);
                    i--;
                    continue;
                }
                j++;
            }
            if (tags.get(i).equals(tag.RBRACKET)) {
                if (tags.get(i - 1).equals(tag.LBRACKET))
                    comma--;
                lBracket--;
            }
        }
        if (tags.get(i).equals(tag.LBRACKET)) comma--;
        else comma++;

        if (X.func_HM.get(var) != comma) { System.out.println("error"); System.exit(0); }
        boolean add = true;

        for(Graph x: X.graph.get(this.n).link)
            if (x.n == X.help.indexOf(var))
                add = false;
        if (add)
            X.graph.get(this.n).link.add(X.graph.get(X.help.indexOf(var)));
        return i;
    }

    public void findError(Modules X)  {
        assignment = false;
        for(int i = 0; i < tags.size(); i++) {
            if (tags.get(i).equals(tag.ASSIGNMENT))
                assignment = true;
            if (assignment && tags.get(i).equals(tag.IDENT)) {
                if (!X.func_HM.containsKey(vars.get(j))) {
                    if (!ident.contains(vars.get(j)))
                    {
                        System.out.println("error");
                        System.exit(0);
                    }
                }
                else {
                    i = findIdent(vars.get(j), i, X);
                    j--;
                }
                j++;
            }
        }
    }

    public void parse() throws Exception {
        count = 0;
        if(!parse_func()){throw new Exception();}
        if (count < tags.size())
        {
            System.out.println("error");
            System.exit(0);
        }
    }

    boolean parse_func() {
        if (count < tags.size() && tags.get(count).equals(tag.IDENT)) { count++; }
        else return true;

        if (tags.get(count).equals(tag.LBRACKET)) { count++;
            if (tags.get(count).equals(tag.IDENT)) { parse_ident(); }
        }
        else return false;

        if (tags.get(count).equals(tag.RBRACKET)) { count++; }
        else return false;

        if (tags.get(count).equals(tag.ASSIGNMENT)) { count++; parse_expr(); }
        else return false;

        if (tags.get(count).equals(tag.SEMICOLON)) { count++; return true;}
        else return false;
    }


    public void parse_ident() {
        count++;
        if (checkTags("parse_ident")) {
            count++;
            parse_ident();
        }
    }

    public void parse_expr() {
        parse_comparison();
        if (checkTags("parse_expr")) {
            count++;
            parse_comparison();
            if (tags.get(count).equals(tag.COLON)) {
                count++;
                parse_expr();
            }
            else
            {
                System.out.println("error");
                System.exit(0);
            }
        }
    }

    public void parse_comparison() {
        parse_arith();
        if (checkTags("parse_comparison")) {
            count++;
            parse_arith();
        }
    }

    private void parse_arith() {
        parse_term();
        parse_arith_2();
    }

    private void parse_arith_2() {
        if (tags.get(count).equals(tag.PLUS) || tags.get(count).equals(tag.MINUS)) {
            count++;
            parse_term();
            parse_arith_2();
        }
    }

    private void parse_term() {
        parse_factor();
        parse_term_2();
    }

    private void parse_term_2() {
        if (tags.get(count).equals(tag.MULTI) || tags.get(count).equals(tag.DIV)) {
            count++;
            parse_factor();
            parse_term_2();
        }
    }

    private void parse_factor() {
        if (checkTags("parse_factor")) {
            count++;
            if (count < tags.size() && tags.get(count - 1).equals(tag.IDENT) && tags.get(count).equals(tag.LBRACKET)) {
                count++;
                parse_actual();
                if (tags.get(count).equals(tag.RBRACKET))
                    count++;
                else
                {
                    System.out.println("error");
                    System.exit(0);
                }
            }
            if (tags.get(count - 1).equals(tag.LBRACKET)) {
                parse_expr();
                if (tags.get(count).equals(tag.RBRACKET))
                    count++;
                else{
                    System.out.println("error");
                    System.exit(0);
                }
            }
            if (tags.get(count - 1).equals(tag.MINUS))
                parse_factor();
        }
        else{
            System.out.println("error");
            System.exit(0);
        }
    }

    private void parse_actual(){
        if (checkTags("parse_actual")) {
            parse_expr();
            if (count < tags.size() && tags.get(count).equals(tag.COMMA)) {
                count++;
                parse_actual();
            }
        }
    }
}

class Graph {
    ArrayList<Graph> link;
    int comp = 0, low = 0, T1 = 0, n;

    public Graph(int n) {
        this.link = new ArrayList<>();
        this.n = n;
    }
}

public class Modules {
    static int count = 1;
    static int time = 1;
    HashMap<String, Integer> func_HM;
    ArrayList<Lexem> str;
    ArrayList<Graph> graph;
    ArrayList<String> help;
    Stack<Graph> stack;

    public Modules(){
        func_HM = new HashMap<>();
        str = new ArrayList<>();
        graph = new ArrayList<>();
        help = new ArrayList<>();
        stack = new Stack<>();
    }

    public void checkerrors()  {
        for (Lexem lexem : str) lexem.findError(this);
    }

    public void add(int i , String x) {
        graph.add(new Graph(i));
        str.add(new Lexem(x, i));
    }

    public void analysis(int i) throws Exception{
        str.get(i).findLexem(this);
        str.get(i).parse();
    }

    public void Tarjan() {
        for (Graph x : graph)
            if (x.T1 == 0) {
                VisitVertex_Tarjan(x);
            }
    }

    public void VisitVertex_Tarjan(Graph v) {
        v.T1 = v.low = time++;
        stack.push(v);
        for(Graph x : v.link) {
            if (x.T1 == 0) {
                VisitVertex_Tarjan(x);
            }
            if (x.comp == 0 && v.low > x.low)
                v.low = x.low;
        }
        if (v.T1 == v.low) {
            Graph u;
            do {
                u = stack.pop();
                u.comp = count;
            } while (u != v);
            count++;
        }
    }

    public String toString(){
        int answer = count - 1;
        return "" + answer;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Modules X = new Modules();
        try {
            for (int i = 0; in.hasNextLine(); i++) {
                String s = in.nextLine();
                if (s.isEmpty())
                    continue;
                X.add(i, s);
                X.analysis(i);
            }
        }
        catch (Exception e){
            System.out.println("error");
            return;
        }
        X.checkerrors();
        X.Tarjan();
        System.out.print(X);
    }
}