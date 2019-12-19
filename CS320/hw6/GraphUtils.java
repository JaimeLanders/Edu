import java.io.*;
import java.util.*;

public abstract class GraphUtils {

  static <V> Graph<V> emptyGraph() {
    return new AdjSetGraph<V>();
  }

  static <V> Graph<V> emptyDirectedGraph() {
    // TODO: replace the following line with a call to the
    // constructor for the AdjSetDirectedGraphClass.
    // We are only using AdjSetGraph here to ensure that the initial
    // version of the code will compile.
    return new AdjSetDirectedGraph<V>();
//    return new AdjSetGraph<V>();
  }

  static <V> String dumpGraph(Graph<V> g) {
    String s = "Vertex count = " + g.vertexCount() + "\n";
    for (V v : g.vertices()) {
      s += v + ":";
      for (V w : g.neighbors(v)) {
        s += " " + w;
      }
      s += "\n";
    }
    return s;
  }

  public static <V> void toDot(Graph <V> g, String gname) throws Exception {
    toDot(g, gname, "graph", "--");
  }

  public static <V> void directedToDot(Graph <V> g, String gname) throws Exception {
    toDot(g, gname, "digraph", "->");
  }

  public static <V> void toDot(Graph <V> g, String gname, String type, String arrow) throws Exception {
    java.io.PrintStream out = new java.io.PrintStream(gname + ".dot");
    out.println(type + " {");
    for (V v : g.vertices()) {
      for (V w : g.neighbors(v)) {
        out.println("\"" + v + "\" " + arrow + " \"" + w + "\";");
      }
    }
    out.println("}");
    out.close();
  }

  public static <V> Graph<V> flip(Graph<V> g) {
//    System.out.println("\nflip()\n"); // DEBUG
    // Construct a flipped version of g as a directed graph, using
    // a Java translation of the algorithm from Week 5, Slide 70.
    Graph<V> flipped = emptyDirectedGraph();

    for (V v : g.vertices()) {
      flipped.addVertex(v);
    }

    for (V v : g.vertices()) {
//    System.out.println("\nv = " + v); // DEBUG
      for (V w : g.neighbors(v)) {
//         System.out.println("w = " + w); // DEBUG
        flipped.addEdge(w, v);
      }
    }

    return flipped;  // this is a stub, not the correct implementation!
  }

  public static <V> List<List<V>> scc(Graph<V> g) {
    // Calculate the list of strongly connected components in the given
    // graph, returning the result as a list of lists.  You should
    // Follow the algorithm that was presented using Python code on the
    // slides for Week 5, Slides 66-79, which was also presented at the
    // start of each of the Week 5 lab sessions.  It is not necessary
    // that you understand exactly how the algorithm works, just that
    // are able to determine how each part of the Python code can be
    // mapped into corresponding Java code that takes advantage of the
    // abstract datatypes for lists and sets in the Java Collections
    // Framework, as well as the abstract datatype for graphs that we
    // have been working with in the Week 8 labs and in the rest of
    // this assignment.

    // NOTE: It is expected that you will need to define multiple
    // auxiliary "private static" methods in this class to complete
    // your implementation.  (For example, you will need to implement
    // at least one "visit" method for each of the two depth first
    // searches that are required.)
    
//    System.out.println("\nscc()\n"); // DEBUG

    List<V> finished = new LinkedList<V>();
    Set<V> visited = new HashSet<V>();
    Graph<V> flipped = emptyDirectedGraph();

    finished = dfs(g);
//    System.out.println(finished);
    finished = reverse(finished);
//    System.out.println(finished);
    flipped = flip(g);
//    System.out.print(GraphUtils.dumpGraph(flipped));
    
    LinkedList<List<V>> sccs = new LinkedList<List<V>>();
    for(V v : finished){
      if(!visited.contains(v)){
//        System.out.println("\nv = " + v); // DEBUG
        List<V> scc = new LinkedList<V>();
        visit2(v, scc, visited, flipped);
//        System.out.println(scc);
        sccs.add(scc);
      }
    }

    return sccs ;
//    return new LinkedList<List<V>>();
    // This is a stub, not the correct implementation!  But it does
    // show how you can construct an empty list (in this case, an
    // empty list containing elements of type List<V>) using the
    // Java collections framework.
  }

  private static <V> List<V> dfs(Graph<V> g) {
//    System.out.println("dfs()\n"); // DEBUG

    Set<V> visited = new HashSet<V>();
    List<V> finished = new LinkedList<V>();

    for(V v : g.vertices()) { 
//      System.out.println("v = " + v + "\n"); // DEBUG
      finished = visit1(v, g, visited, finished);
    }

    return finished;
  }

  private static <V> List<V> visit1(V v, Graph<V> g, Set<V> visited, List<V> finished) {
//    System.out.println("visit1()\n"); // DEBUG
    if(!visited.contains(v)){
      visited.add(v);
//      for (V w : g.neighbors(v)) {
      for (V w : g.vertices()) {
//        System.out.println("w = " + w +"\n"); // DEBUG
        visit1(w, g, visited, finished);
      }
      finished.add(v);
    }
//    System.out.println("vistited = " + visited);
//    System.out.println("finished = " + finished);
    return finished;
  }

  private static <V> List<V> visit2(V v, List<V> scc, Set<V> visited, Graph<V> flipped) {
//    System.out.println("\nvisit2()\n"); // DEBUG
//    System.out.println("v = " + v + "\n"); // DEBUG
    visited.add(v);
    scc.add(v);
//    for(V w : visited) { 
//    for(V w : flipped.vertices()) { 
    for(V w : flipped.neighbors(v)) { 
//      System.out.println("w = " + w + "\n"); // DEBUG
      if(!visited.contains(w)){ 
        visit2(w, scc, visited, flipped);
      }
    }

    return scc;
//    return null;
  }

  private static <V> List<V> reverse(List<V> list) {

//    System.out.println("\nreverse()\n"); // DEBUG

    List<V> revList = new LinkedList<V>();

    for(int i = list.size(); i > 0; i--) {
//    System.out.println("i = " + i + "\n"); // DEBUG
//    System.out.println(list.get(i - 1)); // DEBUG
      revList.add(list.get(i - 1));
    }

    return revList;
  }
}
