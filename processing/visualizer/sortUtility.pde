import java.util.*;

public class NodeComparatorByNodeid implements Comparator<Node> { 
  @Override public int compare(Node p1, Node p2) { 
    return p1.nodeid < p2.nodeid ? -1 : 1;
  }
} 

void changeSortType() {
  //for sort
  switch(sortType) {
  default: //nodeid
    //destructive sort
    Collections.sort(nodes, new NodeComparatorByNodeid()); 
    break;
  }
}

void displaySortType(float x, float y) {
  fill(255);
  textAlign(LEFT);
  textSize(height / 20);
  String temp_str = "Sorted by:\n";
  switch(sortType) {
  default:
    temp_str += "Node ID";
    break;
  }
  text(temp_str, x, y);
}