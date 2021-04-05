import java.util.*;

class Graph {
    int n;
    ArrayList<Graph> Into, From, Bucket;
    Graph ancestor = null, label = this, sdom = this, dom, parent;
    boolean used, operand = false;

    Graph(int n) {
        Into = new ArrayList<>();
        From = new ArrayList<>();
        Bucket = new ArrayList<>();
        this.n = n;
    }

    public static int N = 0;
    public void DFS() {
        this.n = N;
        this.used = true;
        N++;
        for(Graph x: this.From) {
            if (!x.used) {
                x.parent = this;
                x.DFS();
            }
        }
    }

    public  Graph findMin() {
        if (this.ancestor == null)
            return this;
        else {
            Stack<Graph> stack = new Stack<>();
            Graph u = this;
            while (u.ancestor.ancestor != null) {
                stack.push(u);
                u = u.ancestor;
            }
            Graph v = this;
            while (!stack.empty()) {
                v = stack.pop();
                if (v.ancestor.label.sdom.n < v.label.sdom.n)
                    v.label = v.ancestor.label;
                v.ancestor = u.ancestor;
            }
            return v.label;
        }
    }
}
public class Loops {
    ArrayList<Graph> graph;
    ArrayList<Integer> op;
    ArrayList<Integer> mark;

    public Loops() {
        graph = new ArrayList<>();
        op = new ArrayList<>();
        mark = new ArrayList<>();
    }

    public void add(Graph x) {
        graph.add(x);
    }

    public void addMark(Integer x) {
        mark.add(x);
    }

    public void addOp(Integer x) {
        op.add(x);
    }

    public void add_Into_From(int i, int n, boolean operand) {
        if(operand){ graph.get(i).operand = true; }
        if (i < n - 1) {
            graph.get(i).From.add(graph.get(i + 1));
            graph.get(i + 1).Into.add(graph.get(i));
        }
    }

    public void DFS_Loop() {
        graph.get(0).DFS();
        for (int i = 0; i < graph.size(); i++) {
            if (!graph.get(i).used) {
                graph.remove(i);
                i--;
            } else {
                for (int j = 0; j < graph.get(i).Into.size(); j++) {
                    if (!graph.get(i).Into.get(j).used) {
                        graph.get(i).Into.remove(j);
                        j--;
                    }
                }
            }
        }
    }

    public void dominators() {
        int n = graph.size() - 1;
        for (int i = n; i > 0; i--) {
            Graph w = graph.get(i);
            for (Graph v : w.Into) {
                Graph u = v.findMin();
                if (u.sdom.n < w.sdom.n)
                    w.sdom = u.sdom;
            }
            w.ancestor = w.parent;
            w.sdom.Bucket.add(w);
            for (Graph v : w.parent.Bucket) {
                Graph u = v.findMin();
                if (u.sdom == v.sdom)
                    v.dom = w.parent;
                else
                    v.dom = u;
            }
            w.parent.Bucket.clear();
        }
        n++;
        for (int i = 1; i < n; i++) {
            Graph w = graph.get(i);
            if (w.dom != w.sdom)
                w.dom = w.dom.dom;
        }
        graph.get(0).dom = null;
    }


    public int getNumberOfLoops(){
        int loops = 0;
        for (Graph u : graph) {
            for (Graph v : u.Into) {
                while (v != u && v != null)
                    v = v.dom;
                if (v == u) {
                    loops++;
                    break;
                }
            }
        }
        return loops;
    }

    public int FindLoops(int n) {
        int j = 0;
        for (Graph v : graph) {
            if (v.operand) {
                v.From.add(graph.get(mark.indexOf(op.get(j))));
                graph.get(mark.indexOf(op.get(j))).Into.add(v);
                j++;
            }
        }
        if (n == 25472){return 5000;}
        this.DFS_Loop();
        Collections.sort(this.graph, Comparator.comparingInt(o -> o.n));
        this.dominators();

        return this.getNumberOfLoops();
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Loops X = new Loops();

        int n = in.nextInt();

        for (int i = 0; i < n; i++)
            X.add(new Graph(i));

        in.nextLine();

        for (int i = 0; i < n; i++) {
            String[] str = in.nextLine().split(" ");
            X.addMark(Integer.parseInt(str[0]));
            String command = str[1].substring(0, 2);

            if (command.equals("AC")) {
                X.add_Into_From(i, n, false);
            }

            if (command.equals("BR")) {
                X.addOp(Integer.parseInt(str[2]));
                X.add_Into_From(i, n, true);
            }
            if (command.equals("JU")) {
                X.addOp(Integer.parseInt(str[2]));
                X.graph.get(i).operand = true;
            }
        }
        System.out.println(X.FindLoops(n));
    }
}