#ifndef NODE_H
#define NODE_H
#include <SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
//TODO: Implement memory management and child tree
//TODO: Implement scene tree methods
class Node {
public:
    std::unique_ptr<Node> get_child(int node_id, int child_id);
    std::vector<std::unique_ptr<Node>> get_children(int node_id);
    bool is_in_group(char* groupname);
    void add_to_group(char* groupname);
    bool remove_from_group(char* groupname);
private:
    void queue_free();
    std::vector<std::unique_ptr<Node>> children;
    Node* parent;
    std::size_t node_id;
    std::vector<char*> groups;

};


#endif //NODE_H
