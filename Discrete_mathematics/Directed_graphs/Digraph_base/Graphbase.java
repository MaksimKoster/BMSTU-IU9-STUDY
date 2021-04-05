import java.util.*;

class OrGraph {
    ArrayList<Integer> link = new ArrayList<>();
    int T1;
    int comp = 0;
    int low = 0;
}

class Condensation {
    int min = Integer.MAX_VALUE;
    boolean out  = true;
}

public class Graphbase {

    public static int time = 1;
    public static int count = 1;

    public static void Tarjan(OrGraph[] graph) {

        Stack<Integer> s = new Stack<>();

        for (int i = 0; i < graph.length; i++) {
            if (graph[i].T1 == 0) {
                VisitVertex_Tarjan(graph, i, s);
            }
        }

    }

    public static void VisitVertex_Tarjan(OrGraph[] graph, int i, Stack<Integer> s) {
        int v;
        graph[i].T1 = graph[i].low = time++;
        s.push(i);

        for (int j = 0; j < graph[i].link.size(); j++) {
            v = graph[i].link.get(j);

            if (graph[v].T1 == 0) {
                VisitVertex_Tarjan(graph, v, s);
            }

            if (graph[v].comp == 0 && graph[i].low > graph[v].low) {
                graph[i].low = graph[v].low;
            }

        }

        if (graph[i].T1 == graph[i].low) {
            do {
                v = s.pop();
                graph[v].comp = count;
            }
            while (i != v);
            count++;
        }
    }

    public static void makebase(Condensation[] base, OrGraph[] graph) {

        for (int i = 0; i < graph.length; i++) {
            int j = graph[i].comp - 1;
            base[j].min = Math.min(base[j].min, i);

            for (int u = 0; u < graph[i].link.size(); u++) {
                int v = graph[i].link.get(u);

                if (graph[v].comp != graph[i].comp) {
                    base[graph[v].comp - 1].out = false;
                }
            }
        }
    }

    public static void printAnswer(Condensation[] base){
        for (int j = 0; j < count - 1; j++) {
            if (base[j].out) {
                System.out.print(base[j].min +" ");
            }
        }
    }


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        OrGraph[] graph = new OrGraph[n];

        for (int i = 0; i < n; i++) {
            graph[i] = new OrGraph();
        }

        for (int j = 0; j < m; j++) {
            int v1 = in.nextInt();
            int v2 = in.nextInt();
            graph[v1].link.add(v2);
        }

        Tarjan(graph);

        Condensation[] base = new Condensation[count];
        for (int i = 0; i < base.length; i++){
            base[i] = new Condensation();
        }

        makebase(base, graph);
        printAnswer(base);
    }
}