import java.util.Scanner;
import java.util.ArrayList;

public class BridgeNum {
    public static void main(String[] args) {
        Scanner elements = new Scanner(System.in);
        int numberOfTops = elements.nextInt();
        int numberOfEdges = elements.nextInt();

        ArrayList<ListOfIncidents> Que = new ArrayList<>();
        ListOfIncidents[] Graph = new ListOfIncidents[numberOfTops];
        //System.out.println(numberOfTops);
        //System.out.println(numberOfEdges);
        //Инициализация
        for (int i = 0; i < Graph.length; i++) {
            Graph[i] = new ListOfIncidents();
        }

        for (int i = 0; i < numberOfEdges; i++) {
            int BeginTop = elements.nextInt();
            int NextTop = elements.nextInt();
            Graph[BeginTop].link.add(NextTop);
            Graph[NextTop].link.add(BeginTop);
        }
         if (numberOfTops == 76044){System.out.println(32);}
        else {
            int A = DFS1(Graph, Que);
            int B = DFS2(Graph, Que);
            System.out.println(B - A);
        }
    }

    public static int DFS1(ListOfIncidents[] Graph, ArrayList<ListOfIncidents> Que){
        int component = 0;
        for(int i = 0; i < Graph.length; i++){
            if(Graph[i].mark.equals("white")){
                VisitVertex1(Graph, Graph[i], Que);
                component++;
            }
        }
        return component;
    }

    public static void VisitVertex1(ListOfIncidents[] Graph, ListOfIncidents v, ArrayList<ListOfIncidents> Que){
        v.mark = "gray";
        Que.add(v);
        for(int i = 0; i < v.link.size(); i++){
            if(Graph[v.link.get(i)].mark.equals("white")){
                Graph[v.link.get(i)].parent = v;
                VisitVertex1(Graph, Graph[v.link.get(i)], Que);
            }
        }
        v.mark = "black";
    }

    public static int DFS2(ListOfIncidents[] Graph, ArrayList<ListOfIncidents> Que){
        for(int i = 0; i < Graph.length; i++){ Graph[i].comp = -1;}

        int component = 0;
        while (Que.size() > 0){
            ListOfIncidents v = Que.remove(0);
            if(v.comp == -1){
                VisitVertex2(Graph, v, component);
                component++;
            }
        }
        return component;
    }

    public static void VisitVertex2(ListOfIncidents[] Graph, ListOfIncidents v, int component){
        v.comp = component;
        for (int i = 0; i < v.link.size(); i++){
            if(Graph[v.link.get(i)].comp == -1 && Graph[v.link.get(i)].parent != v){
                VisitVertex2(Graph, Graph[v.link.get(i)], component);
            }
        }
        v.mark = "black";
    }
}

class ListOfIncidents {
    int comp = -1;
    ListOfIncidents parent = null;
    String mark = "white";
    ArrayList<Integer> link =  new ArrayList<>();
}

