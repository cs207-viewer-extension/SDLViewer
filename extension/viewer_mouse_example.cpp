/**
 * @file viewer.cpp
 * Test script for the SDLViewer and Graph
 *
 * @brief Reads in two files specified on the command line.
 * First file: 3D Points (one per line) defined by three doubles
 * Second file: Tetrahedra (one per line) defined by 4 indices into the point list
 *
 * Prints
 * A B
 * where A = number of nodes
 *       B = number of edges
 * and launches an SDLViewer to visualize the system
 */

#include <fstream>

#include "CS207/SDLViewer.hpp"
#include "CS207/Util.hpp"
#include "CS207/Color.hpp"

#include "Graph.hpp"
#include "Point.hpp"

#include <memory>

typedef typename CS207::SDLViewer Viewer;
typedef Graph<bool, int> GraphType;



struct EventListener: public Viewer::Listener {
  GraphType& g;
  Viewer& v;

  void handle_mouse_left_click_event() {
    std::cout << "Left Mouse Click! " << std::endl;

    for (auto it = g.node_begin(); it != g.node_end(); ++it) {
      auto n = *it;
      if(n.value())
        n.position().y -= 0.05;
    }

    update_viewer();
  }

  void handle_mouse_right_click_event() {
    std::cout << "Right Mouse Click! " << std::endl;

    for (auto it = g.node_begin(); it != g.node_end(); ++it) {
      auto n = *it;
      if(n.value())
        n.position().y += 0.05;
    }

    update_viewer();
  }

  /** Helper function that updates the viewer */
  void update_viewer() {
    v.clear();
    auto node_map = v.empty_node_map(g); 
    v.add_nodes(g.node_begin(), g.node_end(), node_map);
    v.add_edges(g.edge_begin(), g.edge_end(), node_map);
  }

  void handle_node_selection_event(int i) {(void) i; }
  void handle_mouse_move_event() {}
  void handle(SDL_Event e){ (void) e; }
  void handle_keyboard_event(char c) { (void) c; }

  EventListener(GraphType& g, Viewer& v) : g(g), v(v) {
  };
};


int main(int argc, char** argv)
{
  // Check arguments
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " NODES_FILE TETS_FILE\n";
    exit(1);
  }

  // Construct a Graph
  GraphType graph;
  std::vector<typename GraphType::node_type> nodes;
  std::vector<typename GraphType::node_type> nodes2;

  // Create a nodes_file from the first input argument
  std::ifstream nodes_file(argv[1]);
  // Interpret each line of the nodes_file as a 3D Point and add to the Graph
  Point p;
  while (CS207::getline_parsed(nodes_file, p)){
    nodes.push_back(graph.add_node(p, false));
    nodes2.push_back(graph.add_node(Point(p.x, p.y, p.z+0.25), true));

  }

  // Create a tets_file from the second input argument
  std::ifstream tets_file(argv[2]);
  // Interpret each line of the tets_file as four ints which refer to nodes
  std::array<int,4> t;
  while (CS207::getline_parsed(tets_file, t))
    for (unsigned i = 1; i < t.size(); ++i)
      for (unsigned j = 0; j < i; ++j){
        graph.add_edge(nodes[t[i]], nodes[t[j]]);
        graph.add_edge(nodes2[t[i]], nodes2[t[j]]);
      }

  // Print number of nodes and edges
  std::cout << graph.num_nodes() << " " << graph.num_edges() << std::endl;


  // Launch a viewer
  CS207::SDLViewer viewer;
  viewer.launch();
  
  // Create listern and wrap it within a Smart Pointer
  std::unique_ptr<EventListener> el(new EventListener(graph, viewer));

  //Add listener to the SDLViewer: 
  viewer.add_listener(std::move(el));
  
  // Set the viewer
  auto node_map = viewer.empty_node_map(graph); 
  viewer.add_nodes(graph.node_begin(),graph.node_end(),node_map);
  viewer.add_edges(graph.edge_begin(), graph.edge_end(),node_map);
  viewer.center_view();

  return 0;
}
