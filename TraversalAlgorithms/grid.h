#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <utility>

#define PRIORITY_QUEUE std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >, std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >>

class WeightedGrid{
    private:
        unsigned int startX,startY;

        // Representation of the 2D Grid.
        // The first parameter represents the Y axis. The second is an array of X coordinates.
        std::unordered_map<unsigned int, std::vector<int>> adjGrid; 
        // For our Dijkstra, every cell that we store will have a parent cell, to make a path.
        std::map< std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> > previousCell;
        std::set<std::pair<unsigned int, unsigned int>> visitedCell;
    public:
        void initGrid(unsigned int width, unsigned int height);
        void setWall(unsigned int x, unsigned int y);
        void pushNeighbour(int &vertexX, int &vertexY, PRIORITY_QUEUE &pq);
        void dijkstraGrid(unsigned int x, unsigned int y);
        void printGrid(unsigned int width, unsigned int height);
        void findPath(unsigned int endX, unsigned int endy);
};
