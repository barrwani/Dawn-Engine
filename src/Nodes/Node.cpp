
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

bool Node::is_in_group(char* groupname)
{
    return groups.find(groupname) != groups.end();
}

void Node::add_to_group(char *groupname)
{
    if(groups.size() < MAXGROUPS)
        groups.insert(groupname);
    else
        std::cerr << name << " is in too many groups" << std::endl;
}

bool Node::remove_from_group(char* groupname)
{
    return groups.erase(groupname);
}