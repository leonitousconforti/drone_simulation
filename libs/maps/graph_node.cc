#include "graph_node.h"

namespace drone_simulation::maps {

IGraphNode::IGraphNode(geometry::Point3f position, const std::string& name)
    : name(name), position(position){};

IGraphNode::~IGraphNode(){};

const std::string& IGraphNode::getName() const { return this->name; };

const std::vector<IGraphNode*>& IGraphNode::getNeighbors() const {
  return this->neighbors;
};

const geometry::Point3f IGraphNode::getPosition() const {
  return this->position;
}

void IGraphNode::addNeighbor(IGraphNode* neighbor) {
  this->neighbors.push_back(neighbor);
};

std::ostream& operator<<(std::ostream& os, const IGraphNode& node) {
  os << node.name << "@" << node.position << " has " << node.neighbors.size()
     << " neighbors";
  return os;
}

}  // namespace drone_simulation::maps
