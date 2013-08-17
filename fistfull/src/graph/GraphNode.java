package graph;

import java.util.ArrayList;

public class GraphNode {
	
	int value;
	ArrayList<GraphNode> neighbours;
	
	public GraphNode(int value, ArrayList<GraphNode> neighbours) {
		this.value = value;
		this.neighbours = neighbours;
	}
	
	@Override
	public String toString() {
		return Integer.toString(value);
	}
}
