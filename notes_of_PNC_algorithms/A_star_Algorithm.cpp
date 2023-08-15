#include"A_star_Algorithm.h"

GridWithWeights make_diagram4() {
    GridWithWeights grid(10, 10);
    add_rect(grid, 1, 7, 4, 9);
    typedef GridLocation L;
    grid.forests = std::unordered_set<GridLocation>{
      L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
      L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
      L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
      L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
      L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
      L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
      L{7, 3}, L{7, 4}, L{7, 5}
    };
    return grid;
}

std::vector<GridLocation> SquareGrid::neighbors(GridLocation id)const {
	std::vector<GridLocation> res;
	for (GridLocation dir : DIRS) {
		GridLocation next{ id.x + dir.x, id.y + dir.y };
		if (in_bounds(next) && passable(next)) {
			res.push_back(next);
		}
	}

	if ((id.x + id.y) % 2 == 0) {
		//-------------------------------------------------------
		std::reverse(res.begin(), res.end());//为什么需要反转数组?
		//-------------------------------------------------------		
	}

	return res;
}

SquareGrid make_diagram1() {
	SquareGrid grid(30, 15);
	add_rect(grid, 3, 3, 5, 12);
	add_rect(grid, 13, 4, 15, 15);
	add_rect(grid, 21, 0, 23, 7);
	add_rect(grid, 23, 5, 26, 7);
	return grid;
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
	for (int x = x1; x < x2; ++x) {
		for (int y = y1; y < y2; ++y) {
			grid.walls.insert(GridLocation{ x, y });
		}
	}
}

template<class Graph>
void draw_grid(const Graph& graph,
    std::unordered_map<GridLocation, double>* distances = nullptr,
    std::unordered_map<GridLocation, GridLocation>* point_to = nullptr,
    std::vector<GridLocation>* path = nullptr,
    GridLocation* start = nullptr,
    GridLocation* goal = nullptr) {
    const int field_width = 3;
    std::cout << std::string(field_width * graph.width, '_') << '\n';
    for (int y = 0; y != graph.height; ++y) {
        for (int x = 0; x != graph.width; ++x) {
            GridLocation id{ x, y };
            if (graph.walls.find(id) != graph.walls.end()) {
                std::cout << std::string(field_width, '#');
            }
            else if (start && id == *start) {
                std::cout << " A ";
            }
            else if (goal && id == *goal) {
                std::cout << " Z ";
            }
            else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
                std::cout << " @ ";
            }
            else if (point_to != nullptr && point_to->count(id)) {
                GridLocation next = (*point_to)[id];
                if (next.x == x + 1) { std::cout << " > "; }
                else if (next.x == x - 1) { std::cout << " < "; }
                else if (next.y == y + 1) { std::cout << " v "; }
                else if (next.y == y - 1) { std::cout << " ^ "; }
                else { std::cout << " * "; }
            }
            else if (distances != nullptr && distances->count(id)) {
                std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
            }
            else {
                std::cout << " . ";
            }
        }
        std::cout << '\n';
    }
    std::cout << std::string(field_width * graph.width, '~') << '\n';
}

template<typename Location, typename Graph>
std::unordered_map<Location, Location> bfs(Graph graph, Location start, Location goal) {
    std::queue<Location> frontier;
    frontier.push(start);

    std::unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        Location cur = frontier.front();
        frontier.pop();

        if (cur == goal) break;

        for (Location next : graph.neighbors(cur)) {
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = cur;
            }
        }
    }
    return came_from;
}

template<typename Location, typename Graph>
void dijkstra_search(
    Graph graph,
    Location start,
    Location goal,
    std::unordered_map<Location, Location>& came_from,
    std::unordered_map<Location, double>& cost_so_far
) {
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Location cur = frontier.get();

        if (cur == goal) break;

        for (Location next : graph.neighbors(cur)) {
            double new_cost = cost_so_far[cur] + graph.cost(cur, next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                came_from[next] = cur;
                frontier.put(next, new_cost);
            }
        }
    }
}

template<typename Location>
std::vector<Location> reconstruct_path(
    Location start, Location goal,
    std::unordered_map<Location, Location> came_from
) {
    std::vector<Location> path;
    Location cur = goal;
    if (came_from.find(goal) == came_from.end()) return path;
    while (cur != start) {
        path.push_back(cur);
        cur = came_from[cur];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

template<typename Location, typename Graph>
void a_star_search(
    Graph graph,
    Location start,
    Location goal,
    std::unordered_map<Location, Location>& came_from,
    std::unordered_map<Location, double>& cost_so_far
) {
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);
    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Location cur = frontier.get();
        if (cur == goal) break;

        for (Location next : graph.neighbors(cur)) {
            double new_cost = cost_so_far[cur] + graph.cost(cur, next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = cur;
            }
        }
    }
}

int main() {
    GridWithWeights grid = make_diagram4();
    GridLocation start{ 1,4 }, goal{ 8,3 };
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;
    dijkstra_search(grid, start, goal, came_from, cost_so_far);
    draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
    
    std::cout << "\n";
    
    std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, nullptr, nullptr, &path, &start, &goal);

    std::cout << std::endl;
    draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);

    return 0;
}