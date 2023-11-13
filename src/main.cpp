//
// Created by weed1 on 11/13/2023.
//

#include "main.h"

// Libraries needed for the project
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <iomanip>

// Directives needed for the project
using namespace std;

// Class definitions
class webpage {
    // Object that will represent each vertex in the graph
private:
    // Member variable declaration
    int id, webOutEdge;
    double webRank;
    string webUrl;

public:
    // Main constructor
    explicit webpage(string url, int numId) : id(numId), webRank(0), webOutEdge(0), webUrl(std::move(url)) {}

    // Needed getters and setters
    int getId() const {
        return id;
    }

    double getRank() const {
        return webRank;
    }

    void setRank(double rank) {
        webpage::webRank = rank;
    }

    int getOutEdge() const {
        return webOutEdge;
    }

    void setOutEdge(int outEdge) {
        webpage::webOutEdge = outEdge;
    }

    string getUrl() const {
        return webUrl;
    }
};

class AdjacencyList {
    // Abstract data structure to help simulate a graph
private:
    // Member variable declaration
    int count = 0;
    map<string , vector<webpage *>> graph;

public:
    // Main constructor
    AdjacencyList() = default;

    // Function to process input data and initialize AdjacencyList graph
    void initializeGraph (int lineNum) {
        // Variable declaration
        string from, to;

        // For loop to process data and create graph representation
        for(int i = 0; i < lineNum; i++) {
            // Variable assignment from input
            cin >> from >> to;
            // Check if from url is already in the graph
            if (graph.find(from)==graph.end()) {
                // If not, create webpage vertex and add it to graph
                graph[from].push_back(new webpage(from, count));
                // Increment count, vertex counter and identifier
                ++count;
            }
            // Check if to url is already in the graph
            if (graph.find(to)==graph.end()) {
                // If not, create webpage vertex and add it to graph
                graph[to].push_back(new webpage(to, count));
                // Increment count since it is a new vertex
                ++count;
            }
            // If from and to url already exist in the graph create edge
            graph[from].push_back(graph.find(to)->second[0]);
        }
    };

    // Function to print graph result after pagerank algorithm
    void printGraph() {
        // Iterator declaration
        map<string, vector<webpage *>>::iterator it;
        // Printing parameters configuration
        cout << fixed;
        cout << setprecision(2);
        // For loop to print results
        for(it = graph.begin(); it != graph.end(); ++it) {
            cout << it->second[0]->getUrl() << " " << it->second[0]->getRank() << "\n";
        }
    }

    // Function to initialize webpage node
    void initializeWebpage() {
        // Variable declaration
        int degree;
        double rankZero = 1.00/count;
        // Iterator declaration
        map<string, vector<webpage *>>::iterator it;

        // For loop to initialize webpage in graph
        for(it = graph.begin(); it != graph.end(); ++it) {
            // Reset degree to zero
            degree = 0;
            // Assign initial rank and count connections/out-degrees
            for(auto & j : it->second) {
                j->setRank(rankZero);
                ++degree;
            }
            // Adjust and assign connection number
            it->second[0]->setOutEdge(degree - 1);
        }
    }

    // Function to calculate the rank of the webpage after a number of iteration
    void pageRank(int powIter) {
        // Variable declaration
        int x, y;
        double matrix[count][count], rankVector[count], ans[count];
        // Iterator declaration
        map<string, vector<webpage *>>::iterator it;

        // Variable matrices initialization for loop
        for(int i = 0; i < count; ++i) {
            for(int j = 0; j < count; ++j) {
                matrix[i][j] = 0;
            }
            rankVector[i] = (1.0)/count;
        }

        // Matrix variable assigment
        for(it = graph.begin(); it != graph.end(); ++it) {
            x = it->second[0]->getId();
            for(int j = 1; j < it->second.size(); j++) {
                y = it->second[j]->getId();
                matrix[y][x] = (1.0)/(it->second[0]->getOutEdge());
            }
        }

        // For loop to repeat iteration powIter - 1 times
        for(int l = 0; l < powIter - 1; ++l) {
            // Matrix multiplication algorithm
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    // Answer array reset
                    ans[i] = 0;
                    for (int k = 0; k < count; k++) {
                        // Answer array assignment of result
                        ans[i] += matrix[i][k] * rankVector[k];
                    }
                }
            }
            // Update rank array
            for (int k = 0; k < count; k++) {
                rankVector[k] = ans[k];
            }
        }
        // Update webpage rank
        for(it = graph.begin(); it != graph.end(); ++it) {
            it->second[0]->setRank(rankVector[it->second[0]->getId()]);
        }
    }
};

// Main function
int main() {
    // Variable declaration
    int no_lines, powIter;

    // Create a graph object
    AdjacencyList graph = AdjacencyList();

    // Input variable assignment
    cin >> no_lines;
    cin >> powIter;

    // Initialize graph and webpages
    graph.initializeGraph(no_lines);
    graph.initializeWebpage();

    // Calculate rank of each webpage based on iteration provided
    graph.pageRank(powIter);

    // Print results
    graph.printGraph();

    // End of main
    return 0;
};

