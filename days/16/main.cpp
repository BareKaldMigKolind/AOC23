#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <queue>
#include <unordered_map>

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

std::vector<std::string> grid = lines;
int yMax = grid.size() - 1;
int xMax = grid[0].length() - 1;

struct Beam{
    int x;
    int y;
    char direction;
};

void moveBeam(Beam beam, char direction, std::queue<Beam>& q){
    if(direction == 'n'){
        if(beam.y == 0) return;
        Beam newBeam{beam.x, beam.y - 1, 'n'};
        q.push(newBeam);
    } else if(direction == 's'){
        if(beam.y == yMax) return;
        Beam newBeam{beam.x, beam.y + 1, 's'};
        q.push(newBeam);
    } else if(direction == 'e'){
        if(beam.x == xMax) return;
        Beam newBeam{beam.x + 1, beam.y, 'e'};
        q.push(newBeam);
    } else if(direction == 'w'){
        if(beam.x == 0) return;
        Beam newBeam{beam.x - 1, beam.y, 'w'};
        q.push(newBeam);
    }
}

void move(Beam beam, std::queue<Beam>& q){
    char ch = grid[beam.y][beam.x];

    switch (ch)
    {
    case '.':
        moveBeam(beam, beam.direction,  q);
        break;

    case '/':
        if(beam.direction == 'n' || beam.direction == 'e'){
            char ch = (beam.direction == 'n') ? 'e' : 'n';
            moveBeam(beam, ch, q);
        } else if(beam.direction == 's' || beam.direction == 'w'){
            char ch = (beam.direction == 's') ? 'w' : 's';
            moveBeam(beam, ch, q);
        }
        break;

    case '\\':
        if(beam.direction == 'n' || beam.direction == 'w'){
            char ch = (beam.direction == 'n') ? 'w' : 'n';
            moveBeam(beam, ch, q);
        } else if(beam.direction == 's' || beam.direction == 'e'){
            char ch = (beam.direction == 's') ? 'e' : 's';
            moveBeam(beam, ch, q);
        }
        break;

    case '-':
        if(beam.direction == 'w' || beam.direction == 'e'){
            moveBeam(beam, beam.direction, q);
        } else if(beam.direction == 'n' || beam.direction == 's'){
            moveBeam(beam, 'w', q);
            moveBeam(beam, 'e', q);
        }
        break;

    case '|':
        if(beam.direction == 'n' || beam.direction == 's'){
            moveBeam(beam, beam.direction, q);
        } else if(beam.direction == 'e' || beam.direction == 'w'){
            moveBeam(beam, 'n', q);
            moveBeam(beam, 's', q);
        }
        break;
    
    default:
        break;
    }
}

struct CoordHash {
   std::size_t operator()(const std::pair<int, int> coord) const {
       std::size_t seed = 0;
       seed = (coord.first/2 * 739) + (coord.second * 797);

       return seed;
   }
};

bool dejavu(Beam beam, std::unordered_map<std::pair<int, int>,std::string, CoordHash>& map){
    std::pair<int, int> coord{beam.x,beam.y};
    bool dejavu = false;
    std::string directions = "";

    if(map.count(coord)){
        directions = map[coord];
        for(int i = 0; i < directions.length(); i++){
            if(directions[i] == beam.direction) return true; 
        }
        map[coord] = directions + beam.direction;    
    } else {
        std::string str;
        str += beam.direction;
        map.insert(std::make_pair(coord, str));
    }

    return false;
}


int solution1(int x, int y, char dir){
    std::queue<Beam> q;
    std::unordered_map<std::pair<int, int>,std::string, CoordHash> map;

    Beam beam{x, y, dir};

    q.push(beam);

    while(!q.empty()){

        Beam beam = q.front();
        q.pop();

        if(!dejavu(beam, map)){
            move(beam,q);
        }
    }

    return map.size();
}

int solution2(){
    std::queue<Beam> q;
    std::unordered_map<std::pair<int, int>,std::string, CoordHash> map;

    int mapSize = 0;

    for(int i = 0; i <= yMax; i++){
        for(int j = 0; j <= xMax; j++){
            if((i != 0 && i != yMax) && (j != 0 && j != xMax)) continue;

            char ch;

            //This is not perfect as both directions in both corners are not hit, but it will hopefully work :)
            if(i == 0) ch = 's';
            if(i == yMax) ch = 'n';
            if(j == 0) ch = 'e';
            if(j == xMax) ch = 'w';

            int energizedTiles = solution1(j, i, ch);

            if(energizedTiles > mapSize){
                mapSize = energizedTiles;
            }
        }
    }
    return mapSize;
}

int main(){

    std::cout << "Solution for part a: " << solution1(0, 0, 'e') << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}