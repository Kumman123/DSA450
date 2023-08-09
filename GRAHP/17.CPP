// A C++ program to order of characters in an alien language
#include<bits/stdc++.h>
using namespace std;

// Class to represent a graph
class Graph
{
    int V;    // No. of vertices'

    // Pointer to an array containing adjacency listsList
    list<int> *adj;

    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
    Graph(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);

    // prints a Topological Sort of the complete graph
    void topologicalSort();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

// The function to do Topological Sort. It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological Sort
    // starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    while (Stack.empty() == false)
    {
        cout << (char) ('a' + Stack.top()) << " ";
        Stack.pop();
    }
}

int min(int x, int y)
{
    return (x < y)? x : y;
}

// This function finds and prints order of character from a sorted
// array of words. n is size of words[].  alpha is set of possible
// alphabets.
// For simplicity, this function is written in a way that only
// first 'alpha' characters can be there in words array.  For
// example if alpha is 7, then words[] should have only 'a', 'b',
// 'c' 'd', 'e', 'f', 'g'
void printOrder(string words[], int n, int alpha)
{
    // Create a graph with 'alpha' edges
    Graph g(alpha);

    // Process all adjacent pairs of words and create a graph
    for (int i = 0; i < n-1; i++)
    {
        // Take the current two words and find the first mismatching
        // character
        string word1 = words[i], word2 = words[i+1];
        for (int j = 0; j < min(word1.length(), word2.length()); j++)
        {
            // If we find a mismatching character, then add an edge
            // from character of word1 to that of word2
            if (word1[j] != word2[j])
            {
                g.addEdge(word1[j]-'a', word2[j]-'a');
                break;
            }
        }
    }

    // Print topological sort of the above created graph
    g.topologicalSort();
}

// Driver program to test above functions
int main()
{
    string words[] = {"caa", "aaa", "aab"};
    printOrder(words, 3, 3);
    return 0;
}



























/*

	Time complexity: O(N + W) 
	Space complexity: O(N)
	
	where 'N' is the number of words in the array, and 'W' is the size of words.

*/

#include<algorithm>
#include<unordered_map>
#include<queue>
#include<set>
#include<string>


// function to create graph
unordered_map<char, set<char> > constructGraph(vector<string>& words) 
{

    // initialise a map to store the graph
    unordered_map<char, set<char> > graph;
    
    // create nodes
    for(int i = 0; i < words.size(); i++) 
    {
        for (int j = 0; j < words[i].size(); j++) 
        {

            // store word in a variable
            char c = words[i][j];

            // if word does not exist in the graph
            if (graph.find(c) == graph.end()) 
            {

                // create a temporary set
                set<char> temp;

                // add the node
                graph[c] = temp;
            }
        }
    }
    for (int i = 0; i < words.size() - 1; i++) 
    {

        // initialise a variable to follow index
        int index = 0;

        // traverse until you reach end of one of the words
        while (index < words[i].size() && index < words[i + 1].size()) 
        {

            // if you find the mismatched character
            if (words[i][index] != words[i + 1][index]) 
            {

                // add node into the graph
                graph[words[i][index]].insert(words[i + 1][index]);
                break;
            }

            // increment index
            index++;
        }

        // check if index is equal to smaller length from the two words
        if (index == min(words[i].size(), words[i + 1].size())) 
        {
            if (words[i].size() > words[i + 1].size()) 
            {

                // return an empty map
                return unordered_map<char, set<char> >();
            }
        }
    }

    // return graph
    return graph;
}


// function to get indegree of element
unordered_map<char, int> getIndegree(unordered_map<char, set<char> >& graph) 
{

    // initialise a map to store indegree
    unordered_map<char, int> indegree;

    // initialise an iterator from start of graph
    unordered_map<char, set<char> >::iterator iter;
    iter = graph.begin();

    // traverse until iterator reaches end of graph
    while (iter != graph.end()) 
    {

        // update value
        indegree[iter->first] = 0;

        // increment iterator
        iter++;
    }

    // start again from start of graph    
    iter = graph.begin();

    // traverse until iterator reaches end of graph
    while (iter != graph.end()) 
    {

        // initialise another iterator
        set<char>::iterator _iter = (iter->second).begin();

        // while second iterator reaches end
        while (_iter != (iter->second).end()) 
        {

            // update
            indegree[*_iter] = indegree[*_iter] + 1;
            
            // increment second iterator
            _iter++;
        }

        // increment first iterator
        iter++;
    }

    //return the indegree map
    return indegree;
}


//function to find topological ordering    
string topologicalSorting(unordered_map<char, set<char> > graph) 
{

    // initialise another map to store degree
    unordered_map<char, int> indegree = getIndegree(graph);

    // initialise priority queue instead of simple queue in order to create lexicographical order
    priority_queue<char, vector<char>, greater<char> > que;

    // initialise an iterator to traverse through map
    unordered_map<char, int>::iterator iter;

    // start iterator from begin
    iter = indegree.begin();

    // while iterator reaches end do 
    while (iter != indegree.end()) 
    {

        // if degree = 0
        if (indegree[iter->first] == 0) 
        {

            // push value into the queue
            que.push(iter->first);
        }

        //increment iterator
        iter++;
    }

    // initialise a string to store the order
    string result = "";

    // while queue is not empty
    while (que.size()) 
    {

        // store top element of queue 
        char head = que.top();

        // pop the top element
        que.pop();

        // append head of queue into the result
        result += head;

        // initialise an iterator of set
        set<char>::iterator iter;

        // start iterator from head of graph's begin
        iter = graph[head].begin();

        // while iterator reaches end
        while (iter != graph[head].end()) 
        {

            // store iterator pointer as neighbor
            char neighbor = *iter;

            // update indegree of neighbor
            indegree[neighbor] -= 1;

            // if now, the indegree of neighbor is zero
            if (indegree[neighbor] == 0) 
            {

                // push neighbor into the queue
                que.push(neighbor);
            }

            // increment iterator
            iter++;
        }
    }

    // check if length of string is not equal to size of indegree     
    if (result.size() != indegree.size()) 
    {

        // return an empty string
        return "";
    }

    // else return the order 
    return result;
}

string alienOrder(vector<string> &words, int n)
{

    // initialise unordered_map to store the graph
    unordered_map<char, set<char> > graph = constructGraph(words);
    
    // If graph is empty return an empty string
    if (!graph.size()) 
    {
        return "";
    }

    // return the topological order of the graph
    return topologicalSorting(graph);
}

    












class Solution{
    private:
    vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    // code here
	    vector<int>indegree(V, 0);
	    for(int i=0; i<V; i++){
	        for(auto it:adj[i]){
	            indegree[it]++;
	        }
	    }
	    
	    queue<int>q;
	    for(int i=0; i<V; i++){
	        if(indegree[i]==0) q.push(i);
	    }
	    
	    vector<int>topo;
	    while(!q.empty()){
	        int node=q.front();
	        q.pop();
	        topo.push_back(node);
	        
	        for(auto it:adj[node]){
	            indegree[it]--;
	            if(indegree[it]==0) q.push(it);
	        }
	    }
	    return topo;
	}
    
    public:
    string findOrder(string dict[], int N, int K) {
        //code here
        vector<int>adj[K];
        for(int i=0; i<N-1; i++){
            string s1=dict[i];
            string s2=dict[i+1];
            int len=min(s1.size(), s2.size());
            for(int ptr=0; ptr<len; ptr++){
                if(s1[ptr]!=s2[ptr]){
                    adj[s1[ptr]-'a'].push_back(s2[ptr]-'a');
                    break;
                }
            }
        }
        vector<int>topo=topoSort(K, adj);
        string ans="";
        for(auto it:topo){
            ans+=char(it+'a');
        }
        return ans;
    }