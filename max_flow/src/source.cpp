#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <sstream>
#include <algorithm>
class Grapth;
#define MAX_INT  2147483647;



struct edge {
	char from, to;
	int inv_edge;
	int cost;
	int flow;
};

void print_edge_1(edge e)
{
	std::cout << " from : " << e.from << " to : " << e.to << " cost : " << e.cost << " flow : " << e.flow << std::endl;

}
void print_edge(edge e)
{
	std::cout << e.from << " " << e.to << " " << e.flow << std::endl;

}

void print_edges_1(std::vector<edge>& edges)
{
	for (auto i : edges)
	{
		print_edge_1(i);
	}
}
void print_edges(std::vector<edge>& edges)
{
	for (int i = 0 ; i <edges.size(); i++)
	{
		print_edge(edges[i]);
	}
}

void print_path(std::map<char, int> path, std::vector<edge>& edges)
{
	for (auto i : path)
	{
		//std::cout << "from : " << i.first << " to : " << i.second << std::endl;
		if(i.second >= 0)
			std::cout << "to : " << i.first << " from : " << edges[i.second].from << " flow : " << edges[i.second].flow << std::endl;
		else
			std::cout << "to : " << i.first << " from : " << i.second << std::endl;
	}
}


void print_augmenting_path(std::vector<int>& augmenting_path, std::vector<edge>& edges)
{
	for (auto i : augmenting_path) 
	{
		
		std::cout<< " from : "<< edges[i].from << " to : " << edges[i].to << " cost : " <<  edges[i].cost << " flow : " << edges[i].flow<< std::endl;
	}
}


struct cmp {
	bool operator()(char a, char b) const
	{
		return a > b;
	}
} ;



void print_a(std::map<char, std::vector< int > >& a, std::vector<edge>& edges)
{
	for (auto i : a) 
	{
		std::cout << std::endl;
		std::cout << "v : " << i.first << " vert : ";
		for(auto j : i.second)
			std::cout << edges[j].to << "";
	}
}


bool comp(char c1, char c2) {
	return c1 < c2;
}

void read_graph(char goal, std::map<char, std::vector< int > > &a, std::map<char, std::vector< int > >& ia, std::vector<edge>& edges, std::vector<int>& stock_edges, int m)
{
	char from;
	char to;
	int cap;

	for (int i = 0; i < m; i++) 
	{
		std::cin >> from >> to >> cap;

		if (a.count(from))
			a[from].push_back(i); // исходящие ребра
		else
			a.insert({ from, {i} });


		if (ia.count(to))
			ia[to].push_back(i + m); // входящие ребра
		else
			ia.insert({ to, {i + m} });



		// а в ребрах - вся информация
		// от 0 до m-1 - прямые ребра, от m до 2m-1 - обратные
		//if (from == goal)
			//cap = 0;
		edges[i].from = from;
		edges[i].to = to;
		edges[i].inv_edge = m + i;
		edges[i].cost = cap;
		edges[m + i].from = to;
		edges[m + i].to = from;
		edges[m + i].inv_edge = i;
		// запоминаем ребра, выходящие из стока
		if (from == goal) {
			stock_edges.push_back(i);
		}
	}


	for (auto &i : a) 
	{
		for (int j = 0; j < i.second.size(); j++)
			for (int k = 0; k < i.second.size(); k++)
			{
				if (edges[j].to > edges[k].to) 
				{
					//std::cout << "ffggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
					auto t = i.second[k];
					i.second[k] = i.second[j];
					i.second[j] = t;
				}
			}
		//std::sort(i.second.begin(), i.second.end(), comp);
	}



	for (auto& i : ia)
	{
		for (int j = 0; j < i.second.size(); j++)
			for (int k = 0; k < i.second.size(); k++)
			{
				if (edges[j].to > edges[k].to)
				{
					//std::cout << "ffggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
					auto t = i.second[k];
					i.second[k] = i.second[j];
					i.second[j] = t;
				}
			}
		//std::sort(i.second.begin(), i.second.end(), comp);
	}

}



bool path_exists(char s, char t, std::map<char, std::vector< int > >& a, std::map<char, std::vector< int > >& ia, std::vector<edge>& edges, std::vector<int>& augmenting_path,int* cmin)
{
	//std::cout << "dd" << std::endl;
	std::set<char> used;
	// тут сохраняем номер ребра, по которому мы пришли в вершину
	std::map<char, int> path;

	std::list<char> q;
	q.push_back(s);

	used.insert(s);
	path.insert({s, -1}); // в первую не приходим ниоткуда

	bool found = false;
	char from;
	edge e;
	while (!q.empty() && !found) {

		from = q.back();
		q.pop_back();

		for (int j = 0; j < a[from].size() && !found; ++j) {

			e = edges[a[from][j]];
			if (!used.count(e.to) && (e.cost - e.flow) > 0) {
				q.push_back(e.to);

				used.insert(e.to);


				if(path.count(e.to))
					path[e.to] = a[from][j];
				else
					path.insert({ e.to , a[from][j] });

				// если достигли сток, то можно выходить
				found = e.to == t;
				//std::cout << "Findddd -> : " << e.to << std::endl;
			}
		}
		
		for (size_t j = 0; j < ia[from].size() && !found; ++j) {

			e = edges[ia[from][j]];

			if (!used.count(e.to) && (e.cost - e.flow) > 0) {
				q.push_back(e.to);
				used.insert(e.to);
				if (path.count(e.to))
					path[e.to] = ia[from][j];
				else
					path.insert({ e.to , ia[from][j] });
				// если достигли сток, то можно выходить
				found = e.to == t;
				//std::cout << "Findddd <- : " << e.to << std::endl;
			}
		}
	}

	if (!found) {
		return false;
	}
	//std::cout << "Findddd : " << e.to << std::endl;
	//std::cout << "path = " << path.size() << std::endl;
	//print_path(path, edges);
	augmenting_path.clear();
	// начинаем с конца
	*cmin = MAX_INT;
	//пока не достигли начала

	char cur = t;
	while (cur != s) 
	{
		int i = path[cur];
		augmenting_path.push_back(i); // заносим ребро, по которому пришли сюда
		e = edges[i];
		// минимальный добавляемый поток - самый слабый из потоков в пути
		if (*cmin > e.cost - e.flow) {
			*cmin = e.cost - e.flow;
		}
		cur = edges[i].from;
	}

	return true;


}

struct {
	bool operator()(edge a, edge b) const
	{
		if(a.from == b.from)
			return a.to < b.to;
		return a.from < b.from;
	}
} customLess;



int main()
{
	std::map<char, std::vector< int> > a;
	std::map<char, std::vector< int> > ia;
	std::vector<int> stock_edges;
	std::vector<edge> edges;

	std::vector<int> augmenting_path;


	int size;
	char start;
	char end;



	std::cin >> size;
	std::cin >> start >> end;
	std::cin.ignore();

	edges.resize(size*2);

	read_graph(end, a, ia, edges, stock_edges, size);
	
	int t = a.size() + ia.size();
	augmenting_path.reserve(t);




	//print_edges(edges);


	int flow = 0;
	int cmin;
	while (path_exists(start, end, a, ia, edges, augmenting_path, &cmin)) {
		flow += cmin;
		//print_augmenting_path(augmenting_path, edges);
		//std::cout << "cmin = " << cmin << std::endl;
		//std::cout << std::endl;
		// вдоль всего увеличивающего пути увеличиваем поток
		for (size_t i = 0; i < augmenting_path.size(); ++i) {
			int edge_num = augmenting_path[i];
			edges[edge_num].flow += cmin;
			edges[edges[edge_num].inv_edge].flow = -edges[edge_num].flow;
		}
		//print_edges_1(edges);
		//std::cout << "------------" << std::endl;
		cmin = 0;
	}

	for (size_t i = 0; i < stock_edges.size(); i++) {
		flow = flow + edges[stock_edges[i]].flow;
	}
	std::cout << flow << std::endl;

	//print_a(a, edges);
	std::vector<edge> new_edges(size);

	for (int i = 0; i < new_edges.size(); i++) 
	{
		new_edges[i] = edges[i];
	}

	std::sort(new_edges.begin(), new_edges.end(), customLess);
	

	print_edges(new_edges);

	return 0;
}
