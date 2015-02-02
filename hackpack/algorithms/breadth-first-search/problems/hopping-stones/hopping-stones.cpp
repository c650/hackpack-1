#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<unsigned int, unsigned int> Puiui;

struct Node
{
	unsigned int id;
	bool visited;
	unsigned int dist;
	vector<Node*> neighbors;

	Node() : id(0), visited(false), dist(0) {}
	Node(const unsigned int id) : id(id), visited(false), dist(0) {}
	~Node() {};
};

int main()
{
	Node* nodes = nullptr;
	vector<Puiui> edges;

	// Read in all edges.
	unsigned int a, b;
	unsigned int max_node_id = 0;
	while(cin >> a)
	{
		cin >> b;
		if(a > max_node_id) max_node_id = a;
		if(b > max_node_id) max_node_id = b;
		edges.push_back(make_pair(a, b));
	}

	// Make nodes.
	nodes = new Node[max_node_id + 1];
	for(unsigned int i = 0; i <= max_node_id; i++)
	{
		nodes[i].id = i;
	}

	// Connect nodes by the specified edges.
	for(unsigned int i = 0; i < edges.size(); i++)
	{
		nodes[edges[i].first].neighbors.push_back(&nodes[edges[i].second]);
		nodes[edges[i].second].neighbors.push_back(&nodes[edges[i].first]);
	}

	// Breadth-first search from start to target.
	const unsigned int Start = 0;
	const unsigned int Target = 20;

	queue<Node*> q;
	q.push(&nodes[Start]);
	while(!q.empty())
	{
		// Get current node.
		Node* current = q.front();
		q.pop();
		current->visited = true;

		// See if this is the target node.
		if(current->id == Target)
		{
			cout << "It will take " << current->dist <<
				" hops to get to stone #" << Target << endl;
			break;
		}
		else
		{
			// Update neighbors' distances.
			for(unsigned int i = 0; i < current->neighbors.size(); i++)
			{
				Node* const neighbor = current->neighbors[i];
				if(!neighbor->visited)
				{
					q.push(neighbor);
					neighbor->dist = current->dist + 1;
				}
			}
		}
	}

	delete[] nodes;

	return 0;
}
