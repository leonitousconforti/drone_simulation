#include "graph.h"

#include <limits>
#include <stdexcept>

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

IGraph::IGraph() {}

IGraph::~IGraph() {
  for (auto node : this->nodes) {
    delete node;
  }
}

void IGraph::addNode(IGraphNode* node) {
  std::string name = node->getName();
  if (this->contains(name)) {
    throw std::invalid_argument(name);
  }
  this->lookup.insert({name, node});
  this->nodes.push_back(node);
};

bool IGraph::contains(std::string& name) const {
  return !(this->lookup.find(name) == this->lookup.end());
};

IGraphNode* IGraph::nodeNamed(std::string& name) const {
  auto result = this->lookup.find(name);
  if (result == this->lookup.end()) {
    throw std::invalid_argument(name);
  }
  return result->second;
};

const std::vector<IGraphNode*>& IGraph::getNodes() const { return this->nodes; }

void IGraph::addEdge(std::string& name1, std::string& name2) {
  IGraphNode* node1 = nodeNamed(name1);
  IGraphNode* node2 = nodeNamed(name2);
  node1->addNeighbor(node2);
};

const geometry::BoundingBox IGraph::getBoundingBox() const {
  geometry::BoundingBox bb;
  const std::vector<IGraphNode*>& nodes = this->getNodes();

  for (size_t i = 0; i < nodes.size(); i++) {
    std::vector<float> pos = nodes[i]->getPosition().toVec();
    if (i == 0) {
      bb.min = pos;
      bb.max = pos;
    } else {
      for (size_t j = 0; j < pos.size(); j++) {
        if (bb.min[j] > pos[j]) {
          bb.min[j] = pos[j];
        }
        if (bb.max[j] < pos[j]) {
          bb.max[j] = pos[j];
        }
      }
    }
  }

  return bb;
}

const IGraphNode* IGraph::nearestNode(
    geometry::Point3f point, const geometry::DistanceFunction& distance) const {
  const std::vector<IGraphNode*> nodes = this->getNodes();
  float minDistance = std::numeric_limits<float>::infinity();
  std::vector<float> point_v = point.toVec();
  const IGraphNode* closestNode = NULL;

  for (auto* node : nodes) {
    auto temp_3d = node->getPosition().toVec();
    float d = distance(temp_3d, point_v);
    if (d < minDistance) {
      closestNode = node;
      minDistance = d;
    }
  }

  return closestNode;
}

};  // namespace drone_simulation::maps
