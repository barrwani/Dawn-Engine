#ifndef NODE_H
#define NODE_H
#include <SDL.h>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class root;


const int MAXGROUPS = 30;

//TODO: Implement scene tree methods
class Node {
public:
    std::size_t node_id;

    //Return a raw pointer to a child node
    // Useful for modifying other nodes children w/o ownership
    Node* get_child(int child_id);
    Node* get_parent(){return parent;}
    //Returns a vector of raw pointers to all children of a node
    std::unordered_set<Node*> get_children();

    virtual void update() = 0;
    virtual void draw() = 0;
    //Checks if node is in a group
    bool is_in_group(char* groupname);

    //Adds node to group
    void add_to_group(char* groupname);

    //Removes node from group
    bool remove_from_group(char* groupname);

protected:
    //unique ptr so parent owns all children, makes memory management easy
    std::unordered_set<std::unique_ptr<Node>> children;
    //if parent==nullptr add node to root child array
    Node* parent;
    char* name;
    std::unordered_set<char*> groups;
    bool collision = false;
};


#endif //NODE_H
