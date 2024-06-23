#pragma once

#include <climits>
#include <vector>
#include <queue>

namespace graph {

typedef typename std::pair<int, int> WeightedEdge;

// https://oi-wiki.org/graph/shortest-path/#dijkstra-%E7%AE%97%E6%B3%95
int Dijkstra(const std::vector<std::vector<int>>& links, const int N) {
	// links[i] = [u_i, v_i, time_i], u_i to v_i with cost time_i
	// node index is [0, 1, ... N]
	std::vector<std::vector<WeightedEdge>> link_map(N);
	for (const auto& link : links) {
		link_map[link[0]].emplace_back(link[2], link[1]);
		link_map[link[1]].emplace_back(link[2], link[0]);
	}

	std::vector<int> dist(N, INT_MAX);
	std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, std::greater<WeightedEdge>> pq;

	pq.emplace(0, 0); // (dist, node)
	dist[0] = 0;

	while (!pq.empty()) {
		const auto [cost, node] = pq.top();
		pq.pop();

		for (const auto& [child_cost, child_node] : link_map[node]) {
			const int cost_sum = cost + child_cost;
			if (cost_sum < dist[child_node]) {
				dist[child_node] = cost_sum;
				pq.emplace(cost_sum, child_node);
			}
		}
	}
	return dist[N - 1];
}

}  // namespace graph
