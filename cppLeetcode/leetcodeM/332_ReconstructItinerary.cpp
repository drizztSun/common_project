/*
 
 332. Reconstruct Itinerary
 
 
 Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

 Note:

 If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 All airports are represented by three capital letters (IATA code).
 You may assume all tickets form at least one valid itinerary.
 One must use all the tickets once and only once.
 Example 1:

 Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
 Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
 Example 2:

 Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
 Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
              But it is larger in lexical order.
 
 
 
 
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <deque>

using std::unordered_map;
using std::vector;
using std::string;
using std::deque;


class ReconstructItinerary {

public:
    
    vector<string> doit_greedy(vector<vector<string>>& tickets) {
        
        unordered_map<string, deque<string>> graph;
        vector<string> trip;
        
        for (auto& c : tickets) {
            graph[c[0]].push_back(c[1]);
        }
        
        for (auto& c : graph) {
            auto& dests = c.second;
            std::sort(begin(dests), end(dests));
        }
        
        const string start = "JFK";
        
        std::function<void(const string& )> visit = [&](const string& city) {
            
            auto& next_cities = graph[city];
            
            while (!next_cities.empty()) {
                
                const string dest = next_cities.front();
                next_cities.pop_front();
                
                visit(dest);
            }
            
            trip.push_back(city);
        };
        
        
        visit("JFK");
        
        return vector<string>(trip.rbegin(), trip.rend());
    }
};
