
#include "../../include/Nodes/Node.h"



std::unordered_set<Node*> Node::get_children()
{
    std::unordered_set<Node*> rawchildren;
    for(auto& child : children)
    {
        rawchildren.insert(child.get());
    }
    return rawchildren;
}

void Node::update(float delta)
{
    for(auto& child : children)
    {
        child->update(delta);
    }
}


void Node::draw()
{
    for(auto& child : children)
    {
        child->draw();
    }
}



bool Node::is_in_group(std::string groupname)
{
    return groups.find(groupname) != groups.end();
}

void Node::add_to_group(std::string groupname)
{
    if(groups.size() < MAXGROUPS)
        groups.insert(groupname);
    else
        std::cerr << name << " is in too many groups" << std::endl;
}

bool Node::remove_from_group(std::string groupname)
{
    return groups.erase(groupname);
}