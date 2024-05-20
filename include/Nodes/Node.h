#ifndef NODE_H
#define NODE_H
#include <SDL.h>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <SDL_image.h>
#include "../base/Vector2.h"

class root;


const int MAXGROUPS = 30;

class Node {
public:
    std::size_t node_id;
    virtual ~Node()=default;


    void set_parent(Node* newparent){parent = newparent;}
    Node* get_parent(){return parent;}

    //Returns a vector of raw pointers to all children of a node
    std::unordered_set<Node*> get_children();

    virtual void update(float delta) = 0;
    virtual void draw() = 0;
    void setName(std::string newname){name = newname;}


    virtual Vector2 getPosition()=0;
    virtual Vector2 getDirection()=0;
    virtual Vector2 getDimension()=0;

    virtual void setPosition(Vector2 newpos)=0;
    virtual void setDirection(Vector2 newdir)=0;
    virtual void setDimension(Vector2 newdim)=0;

    std::string getName(){return name;}
    void addChild(std::unique_ptr<Node> child)
    {
        children.push_back(std::move(child));
    }
    //Checks if node is in a group
    bool is_in_group(std::string groupname);

    //Adds node to group
    void add_to_group(std::string groupname);

    //Removes node from group
    bool remove_from_group(std::string groupname);



//unique ptr so parent owns all children, makes memory management easy
std::vector<std::unique_ptr<Node>> children;
protected:
    //if parent==nullptr add node to root child array
    Node* parent;
    std::string name;
    std::unordered_set<std::string> groups;
    bool collision = false;
    Vector2 position,direction, dim;

};


#endif //NODE_H
