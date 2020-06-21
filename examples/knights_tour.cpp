//Graph code is derived from the following book: https://github.com/pearcej/cppds, sections 9.11-9.14
//Otherwise authored by Jesse Walker

#include <map>
#include <list>
#include <algorithm>
#include <utility>

#include "CTurtle.hpp"

namespace ct = cturtle;

class Vertex{
public:
    int id = 0;
    bool visited = false;
    std::list<int> connections;

    Vertex(int id = 0) : id(id){}
    Vertex(const Vertex& copy) : id(copy.id), visited(copy.visited), connections(copy.connections){}

    void addConnection(int id){
        //ensure unique
        //the connections list is never going to be very large in this case
        if(std::find(connections.begin(), connections.end(), id) == connections.end())
            connections.push_back(id);
    }
};

class Graph{
public:
    std::map<int, Vertex*> vertices;
    bool directional = false;

    Graph(bool directional = false) : directional(directional){}

    bool hasVertex(int id){
        return vertices.find(id) != vertices.end();
    }

    Vertex& addVertex(int id){
        if(hasVertex(id)){
            Vertex* v = vertices[id];
            v->id = id;
            v->connections.clear();
            return *v;
        }

        Vertex* v = new Vertex(id);
        vertices[id] = v;
        return *v;
    }

    Vertex& getVertex(int id){
        return *vertices[id];
    }

    void addEdge(int from, int to){
        if(!hasVertex(from))
            addVertex(from);
        if(!hasVertex(to))
            addVertex(to);
        vertices[from]->addConnection(to);
        if(!directional)
            vertices[to]->addConnection(from);
    }

    ~Graph(){
        for(auto& kvPair : vertices){
            delete kvPair.second;
        }
        vertices.clear();
    }

    /*array access operator*/
    Vertex& operator[](int id){
        return *vertices[id];
    }
};

class ChessBoard{
public:
    int size = 0;
    int tileSize = 0;
    int halfTileSize = 0;

    ChessBoard(int sizeTiles, int tileSize){
        this->size = sizeTiles;
        this->tileSize = tileSize;
        this->halfTileSize = tileSize / 2;
    }

    bool isLegalCoord(int x, int y){
        return (x > -1 && y > -1 && x < size && y < size);
    }

    int getTileID(int x, int y){
        return y * size + x;
    }

    void getTileCoordinate(int id, int& destX, int& destY){
        destX = id % size;
        destY = (id - destX) / size;
    }

    std::list<int> genLegalMoves(int srcTileID){
        int srcX, srcY;
        getTileCoordinate(srcTileID, srcX, srcY);

        std::list<int> newMoves;
        static const std::list<std::pair<int,int>> validMoves = {
                {-1, -2},
                {-1,  2},
                {-2, -1},
                {-2,  1},
                {1,  -2},
                {1,   2},
                {2,  -1},
                {2,   1}
        };

        for(const std::pair<int,int>& point : validMoves){
            int newX = srcX + point.first; //1st element in pair is X
            int newY = srcY + point.second;//2nd element in pair is Y
            if(isLegalCoord(newX, newY)){
                newMoves.push_back(getTileID(newX, newY));
            }
        }

        return newMoves;
    }

    void genKnightGraph(Graph& g){
        g = Graph(false);
        for(int x = 0; x < size; x++){
            for(int y = 0; y < size; y++){
                int fromID = getTileID(x,y);
                std::list<int> newMoves = genLegalMoves(fromID);
                for(int toID : newMoves){
                    g.addEdge(fromID, toID);
                }
            }
        }
    }

    void drawChessBoard(ct::Turtle& turtle){
        bool isWhite = false;
        for(int y = 0; y < size; y++){
            isWhite = y % 2 == 0;
            for(int x = 0; x < size; x++){
                turtle.goTo(-200 + (x * tileSize), -200 + (y * tileSize) + tileSize);

                turtle.fillcolor({isWhite ? "white" : "grey"});

                turtle.begin_fill();
                for(int i = 0; i < 4; i++){
                    turtle.forward(tileSize);
                    turtle.right(90);
                }
                turtle.end_fill();

                isWhite = !isWhite;
            }
        }
    }

    void traverseToTile(ct::Turtle& t, int id){
        int x, y;
        getTileCoordinate(id, x, y);
        float destX = -200 + (x * tileSize) + halfTileSize;
        float destY = -200 + (y * tileSize) + halfTileSize;
        t.goTo(destX, destY);
    }

    void traverseTileIDs(ct::Turtle& t, std::list<int>& ids, bool writePath = true){
        if(ids.empty())
            return;
        t.penup();
        traverseToTile(t, ids.front());
        t.circle(5, 30, t.pencolor());

        t.pendown();
        t.fillcolor({"purple"});
        int i = 0;
        for(int id : ids){
            traverseToTile(t, id);
            if(writePath)
                t.write(std::to_string(i));
            i++;
        }
    }
};

std::list<int> warnsdorf(Graph& graph, std::list<int> neighbors){
    std::list<int> output;
    std::list<std::pair<int,int>> sortList;

    for(int neighborID : neighbors){
        std::list<int> moves = graph[neighborID].connections;
        int numMoves = 0;
        for(int move : moves){
            if(!graph[move].visited)
                numMoves++;
        }
        if(numMoves > 0)
            sortList.push_back({numMoves, neighborID});
    }

    sortList.sort();

    for(std::pair<int,int>& moveNeighborPair : sortList){
        output.push_back(moveNeighborPair.second);
    }

    return output;
}

bool tour(Graph& g, Vertex& start, std::list<int>& path){
    const int limit = g.vertices.size();

    if(start.visited)
        return false;

    path.push_back(start.id);
    start.visited = true;

    if(path.size() > limit)
        return true;

    std::list<int> sortedNeighbors = warnsdorf(g, start.connections);
    sortedNeighbors.unique();

    for(int neighborID : sortedNeighbors){
        Vertex& neighbor = g[neighborID];

        if(tour(g, neighbor, path))
            return true;
    }

    start.visited = false;
    path.pop_back();
    return false;
}

std::list<int> tourIterative(Graph& g, Vertex& start){
    const int limit = g.vertices.size();
    std::list<std::pair<int, std::list<int>>> frames;//stack frames

    //prepare first frame
    frames.push_back({start.id, start.connections});

    std::list<int> path;//"the road thus far"

    while(path.size() < limit){
        std::pair<int, std::list<int>>& frame = frames.back();
        Vertex& curVertex = g[frame.first];
        std::list<int>& curNeighbors = frame.second;

        if(!curVertex.visited){//Mark a vertex as visited if finding for the first time.
            curVertex.visited = true;
            path.push_back(curVertex.id);//Then add it to the path, 'cause it's new.
        }

        if(curNeighbors.empty()){
            //If the neighbor list if empty, we can pop this frame from the stack,
            //because it means that no path taken from this vertex with the frames prior
            //will lead to a solution.
            curVertex.visited = false;
            frames.pop_back();
            path.pop_back();
        }else{

            //Add a frame to evaluate a neighbor's path during the next iteration.
            //Get the next neighbor in this frame's list and pop it from this frame's list.
            //This ensures that every time we come back to this vertex,
            //we progress to the next neighbor as a possibility.
            Vertex& neighborVertex = g[curNeighbors.front()];
            curNeighbors.pop_front();

            if(!neighborVertex.visited){//If the vertex hasn't been visited...
                //Implicitly removes moves that don't have moves following them.
                std::list<int> neighborNeighbors = warnsdorf(g, neighborVertex.connections);
                if(!neighborNeighbors.empty()){//If there are possible moves, add another stack frame!
                    frames.push_back({neighborVertex.id, std::move(neighborNeighbors)});
                    //the next iteration, the process starts on the added vertex.
                    //this happens until a solution is found.
                }
            }
        }
    }

    return path;
}

std::list<int> tourTheKnight(ChessBoard& board, int startX = 1, int startY = 1){
    Graph graph;
    board.genKnightGraph(graph);
    std::list<int> path = tourIterative(graph, graph[board.getTileID(startX, startY)]);
    return path;
}

int main(int argc, char**argv){
    ChessBoard board(8, 50);
    Graph g;
    board.genKnightGraph(g);

    ct::TurtleScreen scr(400, 400);
    ct::Turtle turtle(scr);

    turtle.penup();
    turtle.pencolor({"black"});

    scr.tracer(1000, 0);
    turtle.speed(ct::TS_FASTEST);
    board.drawChessBoard(turtle);

    std::list<int> path = tourTheKnight(board, 3, 3);

    turtle.shape("square");
    turtle.seth(-90);
    scr.tracer(0, 10);
    turtle.penup();
    turtle.speed(ct::TS_SLOW);
    board.traverseTileIDs(turtle, path, true);

    scr.update();

    scr.bye();
    return 0;
}
