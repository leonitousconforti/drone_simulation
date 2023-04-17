#include "graph_node.h"

namespace drone_simulation::maps {

IGraphNode::IGraphNode(geometry::Point3f position, const int64_t id)
    : id(id), position(position){};

IGraphNode::~IGraphNode(){};

const int64_t IGraphNode::getId() const { return this->id; };

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
  os << "node " << node.id << "@" << node.position << " has "
     << node.neighbors.size() << " neighbor(s)";
  return os;
}

}  // namespace drone_simulation::maps
