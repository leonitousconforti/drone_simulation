#include "graph_node.h"

namespace drone_simulation::maps {

IGraphNode::IGraphNode(const int64_t id, const geometry::Point3f position)
    : id(id), position(position){};

IGraphNode::~IGraphNode(){};

const int64_t IGraphNode::getId() const { return this->id; };

const std::vector<std::shared_ptr<IGraphNode>>& IGraphNode::getNeighbors()
    const {
  return this->neighbors;
};

const geometry::Point3f IGraphNode::getPosition() const {
  return this->position;
}

void IGraphNode::addNeighbor(std::shared_ptr<IGraphNode> neighbor) {
  this->neighbors.push_back(neighbor);
};

std::ostream& operator<<(std::ostream& os, const IGraphNode& node) {
  os << "node " << node.id << "@" << node.position << " has "
     << node.neighbors.size() << " neighbor(s)";
  return os;
}

}  // namespace drone_simulation::maps
