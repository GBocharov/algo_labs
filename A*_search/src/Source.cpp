#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <sstream>
class Grapth;
#define MAX_INT  2147483647;

class Vertex
{
public:
	char name;
	float cost;
	bool operator < (Vertex const& other) const
	{
		if (cost == other.cost)
			return name < other.name;
		return cost > other.cost;
	}

};


class Link
{
public:
	char name_2;
	float length;

	Link(char n_2, float l) : name_2(n_2), length(l) {};

	bool operator < (Link const& other) const
	{
		if (length == other.length)
			return name_2 < other.name_2;
		return length > other.length;
	}
};



void print_set(std::set<Link> const& l)
{
	for (auto i : l)
	{
		std::cout << "\t" << " name = " << i.name_2 << " length = " << i.length << std::endl;
	}
}


void print_graph(std::map<char, std::set<Link>> const& graph)
{

	for (auto i : graph)
	{
		std::cout << "Vertex " << i.first << " :" << std::endl;

		print_set(i.second);
	}
}

void print_graph(std::map<char, float>& graph_state)
{

	for (auto i : graph_state)
	{
		std::cout << "Vertex " << i.first << " :" << std::endl;

		std::cout << i.second << std::endl;
	}
}


float h(char x, char finish)
{
	return abs(x - finish);
}

float h_1(char x, char finish_1, char finish_2)
{
	return std::min(abs(x - finish_1), abs(x - finish_2));
}



void print_Path(char begin, char goal, std::map<char, char>& Path)
{
	if (!Path.count(goal)) {
		std::cout << "No path" << std::endl;
		return;
	}
	std::string s = "";
	s += goal;
	char current = Path[goal];
	s = current + s;
	while (current != begin)
	{
		current = Path[current];
		s = current + s;
	}
	std::cout << s << std::endl;
}


void read_graph(std::map<char, std::set<Link>>& graph)
{
	char n1;
	char n2;
	float cost;
	std::string s;
	while (getline(std::cin, s) && !s.empty())
	{

		//std::cout<<s<<std::endl;

		(std::stringstream)s >> n1 >> n2 >> cost;



		if (graph.count(n1))
		{
			graph[n1].insert(Link(n2, cost));
		}
		else
		{
			graph.insert({ n1, { Link(n2, cost) } });
		}

	}
}



std::map<char, char> DXTR(char start, char goal_1, char goal_2, std::map<char, std::set<Link>>& graph, int& res)
{

	std::priority_queue<Vertex> queue;
	queue.push({ start, 0 });

	std::map<char, float> cost_visited;
	cost_visited.insert({ start, 0 });


	std::map<char, char> visited;
	cost_visited.insert({ start, '0' });

	while (!queue.empty())
	{
		float cur_cost = queue.top().cost;
		char cur_node = queue.top().name;
		queue.pop();

		if (cost_visited.count(goal_1) && cost_visited[goal_1] <= cur_cost) {
			res = 1;
			break;
		}
		if (cost_visited.count(goal_2) && cost_visited[goal_2] <= cur_cost) 
		{
			res = 2;
			break;
		}



		auto next_noodes = graph[cur_node];  // Links

		for (auto i : next_noodes)
		{

			float neigh_cost = i.length;
			char neigh_node = i.name_2;
			float new_cost = cost_visited[cur_node] + neigh_cost;


			if (!cost_visited.count(neigh_node) || new_cost <= cost_visited[neigh_node])  // vertex not in visited or new cost < curent cost
			{
				float priority = new_cost + h_1(neigh_node, goal_1, goal_2);
				queue.push({ neigh_node, priority });
				//queue.push({neigh_node, new_cost}); // D


				if (!cost_visited.count(neigh_node))
				{
					cost_visited.insert({ neigh_node, new_cost });
				}
				else
				{
					cost_visited.erase(neigh_node);
					cost_visited.insert({ neigh_node, new_cost });
				}
				//cost_visited.insert_or_assign(neigh_node, new_cost);
				if (!visited.count(neigh_node))
				{
					visited.insert({ neigh_node, cur_node });
				}
				else
				{

					visited.erase(neigh_node);
					visited.insert({ neigh_node, cur_node });
				}
				//visited.insert_or_assign(neigh_node, cur_node);
			}

		}
	}
	return visited;
}


int main()
{
	std::map<char, std::set<Link>> graph;

	char start;
	char end_1;
	char end_2 = 0;
	int result = 0;

	std::cin >> start >> end_1 >> end_2;
	std::cin.ignore();
	read_graph(graph);
	//std::cout << "dd";

	//print_graph(graph);

	auto t = DXTR(start, end_1, end_2, graph, result);

	if(result == 1)
		print_Path(start, end_1, t);
	else
		print_Path(start, end_2, t);





	return 0;
}
