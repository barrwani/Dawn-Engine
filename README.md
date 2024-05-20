# Dawn Engine

Dawn Engine is a work-in-progress 2D OOP-based Game Engine, utilising C++ and SDL2. Dawn Engine is inspired by Godot.
Since this is a solo project intended for personal use, branching and versioning is not utilised. 

## Key features
Complete:
- Node-based tree for hierarchy organisation and inheritance
- Quadtree data structure for collision detection
- Nodes all in a vector of `std::unique_ptr` owned by their parent for consistent memory management
- Node groups

WIP:
- Impulse-based collision resolution 
- Sprite animation system 
- Collision layers 
- Basic camera system 

Planning:
- Asset management system 
- Singleton 
- Tilemap System 
- Node re-parenting
- `queue_free()` for abstracted node deletion



## Base structure
The nodes are layed out in a hierarchical scene graph - essentially a linked tree.
- Each node holds a pointer to its parent (`Node* parent`) and a vector of unique pointers of it's children (`std::vector<std::unique_ptr<Node>>`)
- Nodes have `update(delta)` and `draw(delta)` methods which are called recursively on all children every delta
- Node initialization and child node instancing (that is needed when the node is first instanced) is described in the constructor
- Nodes who's parents are the scene root have `nullptr` set as their parent, and are added to the root's children vector. 
  - This ensures that when the root is destroyed the children are properly managed, although this approach may be tweaked based on game state.
- Quadtree that stores all collidable objects and checks for collisions every delta
- Dynamic allocation occurs at the beginning of a scene instance

### Nodes

Nodes are, much like in Godot, inherited from a base Node class and further derived into `Node2D -> {CollisionObject2D,Sprite2D}` and `CollisionObject2D -> {Area2D, CharacterBody2D, StaticBody2D}`. 

Nodes are basically objects, and can be seen as subtrees, inheriting as many children as they want. When a node is deleted, all of it's child nodes recurisvely destroy themselves (smart pointers). Nodes can be deleted by deallocating from the parent's `children` vector (same in root). 

## Collision

Collision detection is done by a Quadtree data structure which recursively checks for collisions between objects in the same or neighbouring space quadrants. 

Once collision is detected, both colliding objects are made aware of the collision as well as what they are colliding with. From there, each object can handle collision in it's own way. 

Currently, displacement collision resolution is being used to resolve collision between objects, though a move to impulse-based collision resolution is currently being worked on.
