#include <bits/stdc++.h>

using namespace std;


struct Edge
{
    int destination;
    int weight;
};


pair<vector<int>, int> findShortestPath(const vector<vector<Edge>> &graph, int source, int destination)
{
    int numVertices = graph.size();

   
    vector<int> distances(numVertices, INT_MAX);
    distances[source] = 0;

  
    vector<int> previous(numVertices, -1);

   
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty())
    {
        int currentVertex = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

   
        if (currentDistance > distances[currentVertex])
        {
            continue;
        }

        for (const Edge &edge : graph[currentVertex])
        {
            int nextVertex = edge.destination;
            int weight = edge.weight;

           
            int distance = currentDistance + weight;

            if (distance < distances[nextVertex])
            {
                distances[nextVertex] = distance;
                previous[nextVertex] = currentVertex;
                pq.push(make_pair(distance, nextVertex));
            }
        }
    }

   
    vector<int> shortestPath;
    int currentVertex = destination;
    while (currentVertex != -1)
    {
        shortestPath.push_back(currentVertex);
        currentVertex = previous[currentVertex];
    }

    reverse(shortestPath.begin(), shortestPath.end());

    return make_pair(shortestPath, distances[destination]);
}

int main()
{
    int numVertices, numEdges;
    cout << "Enter the number of vertices and edges: ";
    cin >> numVertices >> numEdges;

    vector<vector<Edge>> graph(numVertices);

    cout << "Enter the edges in the format 'source destination weight':" << endl;
    for (int i = 0; i < numEdges; i++)
    {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph[source].push_back({destination, weight});
       
    }

    int source, destination;
    cout << "Enter the source and destination vertices: ";
    cin >> source >> destination;

    pair<vector<int>, int> result = findShortestPath(graph, source, destination);
    vector<int> shortestPath = result.first;
    int overallWeight = result.second;

    cout << "Shortest Path: ";
    for (int i = 0; i < shortestPath.size(); i++)
    {
        cout << shortestPath[i];
        if (i != shortestPath.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "Overall Distance: " << overallWeight << endl;

    return 0;
}
