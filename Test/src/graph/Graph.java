package graph;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

public class Graph {

	int noNodes;
	int noEdges;
	ArrayList<GraphNode> nodes;
	
	private enum State {
		Unvisited, Visiting, Visited
	}
	
	public Graph(String filename) {
		
		try {
			BufferedReader reader = new BufferedReader(new FileReader(filename));
			String line = reader.readLine();
			noNodes = Integer.parseInt(line);
			line = reader.readLine();
			noEdges = Integer.parseInt(line);
			
			nodes = new ArrayList<GraphNode>(noNodes);
			for(int i = 0; i < noNodes; i++)
				nodes.add(new GraphNode(i, new ArrayList<GraphNode>()));
			
			for(int i = 0; i < noEdges; i++) {
				line = reader.readLine();
				int from = Integer.parseInt(line.substring(0, line.indexOf(' ')));
				int to   = Integer.parseInt(line.substring(line.indexOf(' ') + 1));
				GraphNode current = nodes.get(from);
				GraphNode destination = nodes.get(to);
				current.neighbours.add(destination);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// 4.2
	public boolean isRouteBetween(GraphNode src, GraphNode dst) {
		Queue<GraphNode> q = new LinkedList<GraphNode>();
		Map<GraphNode, State> visit = new HashMap<GraphNode, State>();
		
		q.add(src);
		visit.put(src,  State.Visiting);
		
		while( !q.isEmpty() ) {
			
			GraphNode current = q.poll();
			for(GraphNode node : current.neighbours) {
				if(node == dst)
					return true;
				if(visit.get(node) == null) {
					visit.put(node, State.Visiting);
					q.add(node);
				}
			}
			visit.put(current, State.Visited);
		}
		
		return false;
	}
	
	public static void main(String[] args) {
		
		Graph g = new Graph("intrare.txt");
		for(GraphNode node : g.nodes)
			System.out.println(node.neighbours);
		
		System.out.println(g.isRouteBetween(g.nodes.get(5), g.nodes.get(0)));
	}
}
