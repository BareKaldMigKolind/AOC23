#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <unordered_set>
#include <unordered_map>

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

void moveRockNorth(int i, int j, std::vector<std::string>& pattern){
    // Basecase
    if(i == 0 || pattern[i-1][j] == 'O' || pattern[i-1][j] == '#'){
        pattern[i][j] = 'O';
        //load += numberOfLines - i;
        return;
    } 

    pattern[i][j] = '.';
    moveRockNorth(i-1, j, pattern);
}

int64_t calculateLoad(std::vector<std::string>& pattern){
    int64_t load = 0;
    for(int i = 0; i < numberOfLines; i++){
        for(int j = 0; j < pattern[0].length(); j++){
            if(pattern[i][j] == 'O'){
                load += numberOfLines - i;
            }
        }
    }
    return load;
}

void rotate(std::vector<std::string>& pattern) {
    std::vector<std::string> rotatedPattern;

    std::string savedPattern = "";
    for(int i = 0; i < pattern[0].length(); i++){
        for(int j = 0; j < pattern.size(); j++){
            savedPattern += pattern[j][i];
        }
        std::reverse(savedPattern.begin(), savedPattern.end());
        rotatedPattern.push_back(savedPattern);
        savedPattern = "";
    }

    pattern = rotatedPattern;
}

struct VectorHash {
   std::size_t operator()(const std::vector<std::string>& v) const {
       std::size_t seed = 0;
       for(std::size_t i = 0; i < v.size(); ++i) {
           for(std::size_t j = 0; j < v[i].size(); ++j) {
               int value;
               switch(v[i][j]) {
                  case '.': value = 1; break;
                  case '#': value = 200; break;
                  case 'O': value = 30000; break;
                  default: value = 0;
               }
               seed += i * j * value;
           }
       }
       return seed;
   }
};

int solution1(){
    auto pattern = lines;
    for(int i = 0; i < numberOfLines; i++){
        for(int j = 0; j < pattern[0].length(); j++){
            if(pattern[i][j] == 'O'){
                moveRockNorth(i,j, pattern);
            }
        }
    }

    int load = calculateLoad(pattern);
    return load;
}

int solution2(){

    bool cycleFound = false;

    auto pattern = lines;

    std::unordered_map<std::vector<std::string>, int, VectorHash> setOfCycles;

    setOfCycles.insert(std::make_pair(pattern, 0));

    int index = 0;
    int numberOfCycles = 1000000000;

    // Running all cycles. 
    while (index < numberOfCycles){

        // 4 rolls per cycle
        for(int k = 0; k < 4; k++){

            //Rolling, rolling, rolling on the riveeeerrr.
            for(int i = 0; i < numberOfLines; i++){
                for(int j = 0; j < pattern[0].length(); j++){
                    if(pattern[i][j] == 'O'){
                        moveRockNorth(i,j, pattern);
                    }
                }
            }

            // When were done rolling, we rotate and just keep rolling north.
            rotate(pattern);
        }

        if(!cycleFound && setOfCycles.find(pattern) != setOfCycles.end()){
            cycleFound = true;

            // Skipping ahead so my poor computer don't have to run for 1000000000 cycles. 
            int cycleLength = index - setOfCycles[pattern];
            int remainingCycles = numberOfCycles - setOfCycles[pattern] ;
            int cyclesToSkip = remainingCycles / cycleLength;
            index += cyclesToSkip * cycleLength - cycleLength;
        }
        
        setOfCycles.insert(std::make_pair(pattern, index));
        index++;
    }

    int load = calculateLoad(pattern);

    return load;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}