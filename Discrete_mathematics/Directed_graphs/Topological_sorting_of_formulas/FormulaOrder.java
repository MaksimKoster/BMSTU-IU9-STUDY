import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class tag{
    public static final String MINUS = "-";
    public static final String PLUS = "+";
    public static final String MULTI = "*";
    public static final String DIV = "/";
    public static final String LEFTPAREN = "(";
    public static final String RIGHTPAREN = ")";
    public static final String EQUAL = "=";
    public static final String COMMA = "COMMA";
    public static final String NUMBER = "NUMBER";
    public static final String VAR = "VAR";
}

class Lexem {
    boolean equal;
    String line, var_new;
    ArrayList<String> tags;
    int count = 0, count_comma = 0, count_equal = 0, count_var = 0;

    Lexem(String line) {
        equal = false;
        this.line = line;
        this.tags = new ArrayList<>();
    }

    void findLexem(int n, FormulaOrder X){
        HashMap<String, Integer> a = X.a;
        String s = line;
        for (int i = 0; i < s.length(); i++) {
            char token = s.charAt(i);

            if (token == ' '){ continue; }
            if (token == '-') {
                tags.add(tag.MINUS);
                continue;
            }
            if (token =='+') {
                if (count_equal == 0) {
                    System.out.println("syntax error");
                    System.exit(0);
                }
                tags.add(tag.PLUS);
                continue;
            }
            if (token == '*') {
                tags.add(tag.MULTI);
                continue;
            }
            if (token ==  '/') {
                tags.add(tag.DIV);
                continue;
            }
            if (token == '(') {
                tags.add(tag.LEFTPAREN);
                continue;
            }
            if (token == ')') {
                tags.add(tag.RIGHTPAREN);
                continue;
            }
            if (token =='=') {
                equal = true;
                count_equal++;
                if (count_equal > 1) {
                    System.out.println("syntax error");
                    System.exit(0);
                }
                tags.add(tag.EQUAL);
                continue;
            }
            if (token ==',') {
                tags.add(tag.COMMA);
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
                tags.add(tag.VAR);
                count_var++;
                var_new = s.charAt(i) + "";
                i++;
                while (i < s.length() && (Character.isAlphabetic(s.charAt(i)) || Character.isDigit(s.charAt(i)))) {
                    var_new += s.charAt(i);
                    i++;
                }
                i--;
                if (!equal) {
                    if (a.containsKey(var_new)) {
                        System.out.println("syntax error");
                        System.exit(0);
                    }
                    a.put(var_new, n);
                }
                continue;
            }
            System.out.println("syntax error");
            System.exit(0);
        }
    }

    void for_HM (int n, FormulaOrder y) {
        equal = false;
        String s = line;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '=')
                equal = true;
            if (equal) {
                if (Character.isAlphabetic(s.charAt(i))) {
                    StringBuilder var = new StringBuilder(s.charAt(i) + "");
                    i++;
                    while (i < s.length() && (Character.isAlphabetic(s.charAt(i)) || Character.isDigit(s.charAt(i)))) {
                        var.append(s.charAt(i));
                        i++;
                    }
                    i--;
                    if (!y.a.containsKey(var.toString())){
                        System.out.println("syntax error");
                        System.exit(0);
                    }
                    int x = y.a.get(var.toString());
                    y.graph.get(n).link.add(y.graph.get(x));
                }
            }
        }
    }

    void parse_left () throws Exception {
        if (tags.get(count).equals(tag.VAR)) {
            count++;
            if (tags.get(count).equals(tag.COMMA)) {
                count++;
                count_comma++;
                parse_left();
            }
            if (count < tags.size() && tags.get(count).equals(tag.EQUAL)) {
                count++;
                if (count_comma == 0)
                    parse_right();
                else {
                    parse_right_comma();
                    if (count_comma != 0)
                        throw new Exception();
                }
            }
        }
        else
            throw new Exception();
    }

    void parse_right_comma() {
        if (tags.get(count).equals(tag.VAR) || tags.get(count).equals(tag.NUMBER)) {
            count++;
            if (count < tags.size() && tags.get(count).equals(tag.COMMA)) {
                count++;
                count_comma--;
                parse_right_comma();
            }
        }
    }

    void parse_right() {
        parse_t();
        parse_e2();
    }

    void parse_t() {
        parse_f();
        parse_t2();
    }

    void parse_e2() {
        if (count < tags.size() && (tags.get(count).equals(tag.MINUS) || tags.get(count).equals(tag.PLUS))) {
            count++;
            parse_t();
            parse_e2();
        }
        if (count == tags.size()-1 && (tags.get(count).equals(tag.NUMBER) || tags.get(count).equals(tag.COMMA))) {
            System.out.println("syntax error");
            System.exit(0);
        }
    }

    void parse_t2(){
        if (count < tags.size() && (tags.get(count).equals(tag.MULTI) || tags.get(count).equals(tag.DIV))) {
            count++;
            parse_f();
            parse_t2();
        }
    }

    void parse_f() {
        if (tags.get(count).equals(tag.MINUS) || tags.get(count).equals(tag.LEFTPAREN) || tags.get(count).equals(tag.NUMBER) || tags.get(count).equals(tag.VAR)) {
            count++;
            if (tags.get(count - 1).equals(tag.MINUS))
                parse_f();
            if (tags.get(count - 1).equals(tag.LEFTPAREN)) {
                parse_right();
                if (tags.get(count).equals(tag.RIGHTPAREN))
                    count++;
                else{System.out.println("syntax error");
                    System.exit(0);}
            }
        }
        else{System.out.println("syntax error");
            System.exit(0);}
    }
}

class Graph {
    ArrayList<Graph> link;
    int count;
    String color = "white";

    Graph(int count) {
        link = new ArrayList<>();
        this.count = count;
    }

    public void dfs(ArrayList<Graph> s)  {
        this.color = "grey";
        for(Graph v: this.link)
            if (v.color.equals("white")) { v.dfs(s); }
            else if (v.color.equals("grey")){
                System.out.println("cycle");
                System.exit(0);
            }
        this.color = "black";
        s.add(this);
    }
}

public class FormulaOrder {

    HashMap<String, Integer> a;
    ArrayList<Lexem> str ;
    ArrayList<Graph> graph;
    ArrayList<Graph> answer;

    FormulaOrder(){
        a = new HashMap<>();
        str = new ArrayList<>();
        graph = new ArrayList<>();
        answer = new ArrayList<>();
    }

    public void printResult(){
        this.dfs_formula();
        for(Graph x : answer)
            System.out.println(str.get(x.count).line);
    }

    public void addLine(int i, String x){
        this.str.add(new Lexem(x));
        this.graph.add(new Graph(i));
    }

    public void dfs_formula()  {
        for(Graph x : graph)
            if (x.color.equals("white"))
                x.dfs(answer);
    }

    public void parse(int i) throws Exception {
        str.get(i).findLexem(i, this);
        str.get(i).parse_left();
    }

    public void analysis() {
        int i = 0;
        for (Lexem line: str) {
            line.for_HM(i, this);
            i++;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        FormulaOrder X = new FormulaOrder();
        try {
            for (int i = 0; in.hasNextLine(); i++) {
                X.addLine(i, in.nextLine());
                X.parse(i);
            }
        }
        catch(Exception e){
            System.out.println("syntax error");
            return;
        }
        X.analysis();
        X.printResult();
    }
}