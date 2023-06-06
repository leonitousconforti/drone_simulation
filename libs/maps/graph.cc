#include "graph.h"

#include <algorithm>
#include <limits>

namespace drone_simulation::maps {

IGraph::IGraph() {}
IGraph::~IGraph() {}

void IGraph::addNode(const int64_t id, const geometry::Point3f pos) {
  this->nodes.push_back(std::make_shared<IGraphNode>(id, pos));
};

const std::vector<std::shared_ptr<IGraphNode>>& IGraph::getNodes() const {
  return this->nodes;
}

void IGraph::addEdge(const int64_t id1, const int64_t id2) {
  auto findById = [](const int64_t id) {
    return [=](const std::shared_ptr<IGraphNode> node) {
      return node->getId() == id;
    };
  };

  auto node1 = std::find_if(nodes.begin(), nodes.end(), findById(id1));
  auto node2 = std::find_if(nodes.begin(), nodes.end(), findById(id2));
  if (node1 == nodes.end() || node2 == nodes.end()) return;

  node1->get()->addNeighbor(*node2);
  node2->get()->addNeighbor(*node1);
};

void IGraph::prune() {
  auto noNeighbors = [](const std::shared_ptr<IGraphNode> node) {
    return node->getNeighbors().size() == 0;
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
