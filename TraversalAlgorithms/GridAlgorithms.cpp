#include "grid.h"
#include <cstdint>
#include <iostream>
#include <climits>
#include <algorithm>

#define WALL -1
#define STRAIGHT 10
#define DIAGONAL 14

void WeightedGrid::initGrid(unsigned int width, unsigned int height){
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            adjGrid[i].push_back(INT8_MAX);
        }
    }
}

void WeightedGrid::setWall(unsigned int x, unsigned int y){
    adjGrid[y][x] = WALL;
}

void WeightedGrid::pushNeighbour(int &vertexX, int &vertexY, 
        std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >,
                        std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,
                        std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >
    > &pq){

        // TODO: Find a way to shorten and clean up this function.

        ////////// NOT DIAGONAL ///////////

        if( (vertexX-1) >= 0 && adjGrid[vertexY][vertexX]+STRAIGHT < adjGrid[vertexY][vertexX-1]){
            adjGrid[vertexY][vertexX-1] = adjGrid[vertexY][vertexX]+STRAIGHT;
            pq.push(std::make_pair(adjGrid[vertexY][vertexX-1], std::make_pair(vertexY,vertexX-1)));
            previousCell[{vertexY,vertexX-1}] = {vertexY,vertexX};
        }
        if( (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+STRAIGHT < adjGrid[vertexY-1][vertexX]){
           adjGrid[vertexY-1][vertexX] = adjGrid[vertexY][vertexX]+STRAIGHT;
           pq.push(std::make_pair(adjGrid[vertexY-1][vertexX], std::make_pair(vertexY-1,vertexX)));
           previousCell[{vertexY-1,vertexX}] = {vertexY,vertexX};
        }
        if( (vertexX+1) < 8 && adjGrid[vertexY][vertexX]+STRAIGHT < adjGrid[vertexY][vertexX+1]){
            adjGrid[vertexY][vertexX+1] = adjGrid[vertexY][vertexX]+STRAIGHT;
            pq.push(std::make_pair(adjGrid[vertexY][vertexX+1], std::make_pair(vertexY,vertexX+1)));
            previousCell[{vertexY,vertexX+1}] = {vertexY,vertexX};
        }
        if( (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+STRAIGHT < adjGrid[vertexY+1][vertexX]){
            adjGrid[vertexY+1][vertexX] = adjGrid[vertexY][vertexX]+STRAIGHT;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX], std::make_pair(vertexY+1,vertexX)));
            previousCell[{vertexY+1,vertexX}] = {vertexY,vertexX};
        }

        //////////// DIAGONAL ///////////

        if( (vertexX-1) >= 0 && (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+DIAGONAL < adjGrid[vertexY-1][vertexX-1]){
            adjGrid[vertexY-1][vertexX-1] = adjGrid[vertexY][vertexX]+DIAGONAL;
            pq.push(std::make_pair(adjGrid[vertexY-1][vertexX-1], std::make_pair(vertexY-1,vertexX-1)));
            previousCell[{vertexY-1,vertexX-1}] = {vertexY,vertexX};
        }
        if( (vertexX-1) >= 0 && (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+DIAGONAL < adjGrid[vertexY+1][vertexX-1]){
            adjGrid[vertexY+1][vertexX-1] = adjGrid[vertexY][vertexX]+DIAGONAL;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX-1], std::make_pair(vertexY+1,vertexX-1)));
            previousCell[{vertexY+1,vertexX-1}] = {vertexY,vertexX};
        }

        if( (vertexX+1) < 8 && (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+DIAGONAL < adjGrid[vertexY-1][vertexX+1]){
            adjGrid[vertexY-1][vertexX+1] = adjGrid[vertexY][vertexX]+DIAGONAL;
            pq.push(std::make_pair(adjGrid[vertexY-1][vertexX+1], std::make_pair(vertexY-1,vertexX+1)));
            previousCell[{vertexY-1,vertexX+1}] = {vertexY,vertexX};
        }
        if( (vertexX+1) < 8 && (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+DIAGONAL < adjGrid[vertexY+1][vertexX+1]){
            adjGrid[vertexY+1][vertexX+1] = adjGrid[vertexY][vertexX]+DIAGONAL;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX+1], std::make_pair(vertexY+1,vertexX+1)));
            previousCell[{vertexY+1,vertexX+1}] = {vertexY,vertexX};
        }
}

void WeightedGrid::dijkstraGrid(unsigned int x, unsigned int y){
    visitedCell.clear();

    adjGrid[y][x] = 0; // The start position will have the lowest weight. 
    startX = x;
    startY = y;

    std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >,
                        std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,
                        std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >
    > pq;

    pq.push(std::make_pair(0, std::make_pair(y,x)));

    while(!pq.empty()){
        std::pair< int,  int> current_vertex = pq.top().second;
        int cost = pq.top().first;
        int vertexY = current_vertex.first;
        int vertexX = current_vertex.second;
        pq.pop();

        if(visitedCell.find(current_vertex) != visitedCell.end())
            continue;

        if(cost == -1)
            continue;

        std::cout << "Y, X: " << vertexY << ", " << vertexX << ". Distance: " << cost << '\n';

        visitedCell.insert(std::make_pair(vertexY, vertexX));

        pushNeighbour(vertexX, vertexY, pq);
    }
}

void WeightedGrid::printGrid(unsigned int width, unsigned int height){
    for(unsigned int i = 0; i < height; i++){
        std::cout<<'\n';
        for(int j = 0; j < width; j++)
            std::cout<<adjGrid[i][j]<<' ';
    }
    std::cout<<'\n'<<std::endl;
}

void WeightedGrid::findPath(unsigned int endX, unsigned int endY){
    std::pair<unsigned int, unsigned int> start = { startY, startX };
    std::pair<unsigned int, unsigned int> prev;
    std::vector<std::pair<unsigned int, unsigned int>> path;

    int x = endX, y = endY;
    path.push_back({y,x});

    while(prev != start){
        prev = previousCell[{y,x}];
        y = prev.first;
        x = prev.second;
        path.push_back(prev);
    }

    std::reverse(path.begin(), path.end());

    for(auto const &cell : path)
        std::cout << cell.first << ' ' << cell.second << '\n';
}
