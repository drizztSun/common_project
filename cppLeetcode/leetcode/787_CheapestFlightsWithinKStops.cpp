#include <vector>
#include <queue>
#include <unordered_map>
using std::unordered_map;
using std::vector;

struct Edge {
	int from;
	int to;
	int price;
};

struct Node {
	int name;
	int cost;
	int stops;
};

class FindCheapestPrice {

public:	
	int doit(int n, vector<vector<int>>&& flights, int src, int dst, int K) {


		vector<vector<Edge>> flight_prices(n, vector<Edge>());

		for (auto& c : flights) {
			flight_prices[c[0]].push_back(Edge{ c[0], c[1], c[2] });
		}

		vector<bool> visited(n, false);

		auto compare = [](Node l, Node r) -> bool {
			return l.cost > r.cost;
		};

		std::priority_queue<Node, vector<Node>, decltype(compare)> pq(compare);
		pq.push(Node{src, 0, -1});

		while (!pq.empty()) {

			Node n = pq.top();
			pq.pop();
			if (n.name == dst) {
				return n.cost;
			}

			for (auto&c : flight_prices[n.name]) {
				if (!visited[c.to] && n.stops < K) {
					pq.push(Node{ c.to, n.cost + c.price, n.stops + 1 });
				}
			}
			visited[n.name] = true;
		}

		return -1;
	}
};


void Test_787_CheapestFlights() {


	int res = 0;
	
	res = FindCheapestPrice().doit(3, vector<vector<int>>{ {0, 1, 100}, { 1, 2, 100 }, { 0, 2, 500 }}, 0, 2, 1);

	res = FindCheapestPrice().doit(3, vector<vector<int>>{ {0, 1, 100}, { 1, 2, 100 }, { 0, 2, 500 }}, 0, 2, 0);

	res = 0;
}
