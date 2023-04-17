#include "graph.h"

#include <functional>
#include <limits>
#include <stdexcept>
#include <unordered_set>

namespace drone_simulation::maps {

IGraph::IGraph() {}

IGraph::~IGraph() {
  for (auto node : this->nodes) {
    delete node;
  }
}

void IGraph::addNode(IGraphNode* node) {
  int64_t id = node->getId();
  if (this->contains(id)) {
    throw std::invalid_argument("graph already contains that node");
  }
  this->lookup.insert({id, node});
  this->nodes.push_back(node);
};

bool IGraph::contains(int64_t id) const {
  return !(this->lookup.find(id) == this->lookup.end());
};

IGraphNode* IGraph::getNodeById(int64_t id) const {
  auto result = this->lookup.find(id);
  if (result == this->lookup.end()) {
    throw std::invalid_argument("graph does not contain that node");
  }
  return result->second;
};

const std::vector<IGraphNode*>& IGraph::getNodes() const { return this->nodes; }

void IGraph::addEdge(int64_t id1, int64_t id2) {
  IGraphNode* node1 = getNodeById(id1);
  IGraphNode* node2 = getNodeById(id2);
  node1->addNeighbor(node2);
  node2->addNeighbor(node1);
};

void IGraph::prune() {
  auto noNeighbors = [](IGraphNode* node) {
    if (node->getNeighbors().size() == 0) {
      delete node;
      return true;
    }
    return false;
  };
  auto _ = std::remove_if(this->nodes.begin(), this->nodes.end(), noNeighbors);
  this->nodes.erase(_, this->nodes.end());
}

const geometry::BoundingBox IGraph::getBoundingBox() const {
  geometry::BoundingBox bb;
  const std::vector<IGraphNode*>& nodes = this->getNodes();

  geometry::Point3f initial = nodes[0]->getPosition();
  bb.min.x = initial.x;
  bb.min.y = initial.y;
  bb.max.x = initial.x;
  bb.max.y = initial.y;
  bb.min.z = 0;
  bb.max.z = 0;

  for (IGraphNode* node : nodes) {
    geometry::Point3f pos = node->getPosition();
    if (bb.min.x > pos.x) bb.min.x = pos.x;
    if (bb.min.y > pos.y) bb.min.y = pos.y;
    if (bb.max.x < pos.x) bb.max.x = pos.x;
    if (bb.max.y < pos.y) bb.max.y = pos.y;
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
