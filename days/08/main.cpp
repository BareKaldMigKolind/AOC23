#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <unordered_map>

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

#define COORDINATE std::string


int solution1(){
    std::string commands = lines[0];

    std::unordered_map<COORDINATE, std::pair<COORDINATE, COORDINATE>> coordinates;

    for(int i = 2; i < numberOfLines; i++){
        std::string nodes = lines[i];

        std::string sourceNode = nodes.substr(0,3);
        std::string firstNode = nodes.substr(7,3);
        std::string secondNode = nodes.substr(12,3);

        std::pair<COORDINATE, COORDINATE> nodePair(firstNode, secondNode);

        coordinates.insert(std::make_pair(sourceNode, nodePair));

    }

    std::string currentSource = "AAA";
    int index = 0;
    int steps = 0;

    while(currentSource != "ZZZ"){
        std::pair<COORDINATE, COORDINATE> nodeLine = coordinates[currentSource];
        
        if(commands[index] == 'L'){
            currentSource = nodeLine.first;
        }
        else{
            currentSource = nodeLine.second;
        }

        steps++;
        index = steps % commands.length();
    }

    return steps;
}

int64_t solution2(){
    std::string commands = lines[0];

    std::unordered_map<COORDINATE, std::pair<COORDINATE, COORDINATE>> coordinates;
    std::vector<std::string> endsOnA;

    for(int i = 2; i < numberOfLines; i++){
        std::string nodes = lines[i];

        std::string sourceNode = nodes.substr(0,3);
        std::string firstNode = nodes.substr(7,3);
        std::string secondNode = nodes.substr(12,3);

        std::pair<COORDINATE, COORDINATE> nodePair(firstNode, secondNode);

        coordinates.insert(std::make_pair(sourceNode, nodePair));

        if(sourceNode[2] == 'A'){
            endsOnA.push_back(sourceNode);
        }
    }

    std::vector<std::string> sourceVector = endsOnA;
    std::vector<int> stepsToz;

    for(int i = 0; i < sourceVector.size(); i++){
        std::string currentSource = sourceVector[i];
        int index = 0;
        int steps = 0;

        while(currentSource[2] != 'Z'){
            std::pair<COORDINATE, COORDINATE> nodeLine = coordinates[currentSource];
        
            if(commands[index] == 'L'){
                currentSource = nodeLine.first;
            }
            else{
                currentSource = nodeLine.second;
            }

            steps++;
            index = steps % commands.length();
        } 
        stepsToz.push_back(steps); 
    }

    int64_t totalSteps = calculateLCM(stepsToz);

    return totalSteps;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}