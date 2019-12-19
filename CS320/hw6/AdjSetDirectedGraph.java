import java.util.*;

class  AdjSetDirectedGraph<V> extends AdjSetGraph<V> {
  // Add an edge between two vertices.
  // Raises IllegalArgumentException if either vertex is not in graph
  // No-op if edge already exists
  public void addEdge(V v1, V v2) {
    Set<V> adjs1 = adjacents(v1);   // Check that v1 is in the graph
    Set<V> adjs2 = adjacents(v2);   // Check that v2 is in the graph
    adjs1.add(v2);                  // Add an edge from v1 to v2
  }
}
