#include "graph.h"

#include <functional>
#include <limits>
#include <stdexcept>
#include <unordered_set>

namespace drone_simulation::maps {

IGraph::IGraph() {}
IGraph::~IGraph() {}

void IGraph::addNode(std::shared_ptr<IGraphNode> node) {
  int64_t id = node.get()->getId();
  if (this->contains(id)) {
    throw std::invalid_argument("graph already contains that node");
  }
  this->lookup.insert({id, node});
  this->nodes.push_back(node);
};

const bool IGraph::contains(const int64_t id) const {
  return !(this->lookup.find(id) == this->lookup.end());
};

const std::shared_ptr<IGraphNode> IGraph::getNodeById(const int64_t id) const {
  auto result = this->lookup.find(id);
  if (result == this->lookup.end()) {
    throw std::invalid_argument("graph does not contain that node");
  }
  return result->second;
};

const std::vector<std::shared_ptr<IGraphNode>>& IGraph::getNodes() const {
  return this->nodes;
}

void IGraph::addEdge(const int64_t id1, const int64_t id2) {
  std::shared_ptr<IGraphNode> node1 = getNodeById(id1);
  std::shared_ptr<IGraphNode> node2 = getNodeById(id2);
  node1->addNeighbor(node2);
  node2->addNeighbor(node1);
};

void IGraph::prune() {
  auto noNeighbors = [](std::shared_ptr<IGraphNode> node) {
    return node.get()->getNeighbors().size() == 0;
  };
  auto _ = std::remove_if(this->nodes.begin(), this->nodes.end(), noNeighbors);
  this->nodes.erase(_, this->nodes.end());
}

const geometry::BoundingBox IGraph::getBoundingBox() const {
  geometry::BoundingBox bb;
  const std::vector<std::shared_ptr<IGraphNode>>& nodes = this->getNodes();

  geometry::Point3f initial = nodes[0]->getPosition();
  bb.min.x = initial.x;
  bb.min.y = initial.y;
  bb.max.x = initial.x;
  bb.max.y = initial.y;
  bb.min.z = 0;
  bb.max.z = 0;

  for (std::shared_ptr<IGraphNode> node : nodes) {
    geometry::Point3f pos = node->getPosition();
    if (bb.min.x > pos.x) bb.min.x = pos.x;
    if (bb.min.y > pos.y) bb.min.y = pos.y;
    if (bb.max.x < pos.x) bb.max.x = pos.x;
    if (bb.max.y < pos.y) bb.max.y = pos.y;
  }

  return bb;
}

const std::shared_ptr<IGraphNode> IGraph::nearestNode(
    const geometry::Point3f point,
    const geometry::DistanceFunction& distance) const {
  std::vector<float> point_v = point.toVec();
  float minDistance = std::numeric_limits<float>::infinity();
  std::shared_ptr<IGraphNode> closestNode = NULL;

  for (auto node : this->getNodes()) {
    auto temp_3d = node->getPosition().toVec();
    float d = distance(temp_3d, point_v);
    if (d < minDistance) {
      minDistance = d;
      closestNode = node;
    }
  }

  return closestNode;
}

};  // namespace drone_simulation::maps
