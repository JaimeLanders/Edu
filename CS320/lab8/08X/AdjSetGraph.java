import java.util.*;

class  AdjSetGraph<V> implements Graph<V> {
  private Map<V,Set<V>> vertices;

    // complete the implementation by adding all the methods
    // defined in the Graph interface

    // (you may also wish to add private helper methods to perform
    //  tasks that are common to several public methods)

  public void addVertex(V v) {
    Set<V> edges = new Set<V>;

    vetices.put(v, edges);
  }

  public Iterable<V> vertices() {
    return null;
  }

  public int vertexCount() {
//    return 0;
    return vertices.size();
  }

  public boolean hasVertex(V v) {
    return false;
  }

  public void addEdge(V v1, V v2) {
  }

  public Iterable<V> neighbors(V v) {
    return null;
  }

  public int degree(V v) {
    return vertices.get(v).size();
  }

  // useful for debugging, once methods are implemented
  public String toString() {
    return GraphUtils.dumpGraph(this);
  }
}
