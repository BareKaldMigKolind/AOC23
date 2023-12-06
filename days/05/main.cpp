#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <map>

#define DESTINATION int64_t
#define SOURCE int64_t
#define RANGE int64_t


// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int64_t numberOfLines = lines.size();
// ======================================================== //

std::vector<int64_t> getSeeds(){
    std::vector<std::string> tempVector = split_on_char<std::string>(lines[0], ':');
    return stringOfIntsToLLVector(tempVector[1], ' ');
}

// Given a range and source, it will tell if the inputKey is in the range.
bool isInRange(SOURCE givenKey, SOURCE keyInMap, std::map<SOURCE, std::pair<DESTINATION, RANGE>>& givenMap){
    std::pair<DESTINATION, SOURCE> temp = givenMap[keyInMap];

    return givenKey  >= keyInMap && givenKey <= keyInMap + temp.second;
}
// mapKey is myInput key, mapsIndex is to get the correct map, vectorOfMaps is given by the name.
int64_t getValueFromMap(SOURCE mapKey, int64_t mapsIndex, std::vector<std::map<SOURCE, std::pair<DESTINATION, RANGE>>>& vectorOfMaps){
    //If mapKey doesn't have any instructions(if its not in the map) it should return it self. 
    int64_t value = -100000;
    auto it = vectorOfMaps[mapsIndex].begin();
    auto next = std::next(it);

    // Will find the source that the inputKey might be in range of
    while(next->first <= mapKey && next != vectorOfMaps[mapsIndex].end()){
        it = next;
        next = std::next(it);
    }
    
    //Updates the value to either the destination or it self based on the bool outcome
    if(it != vectorOfMaps[mapsIndex].end() && isInRange(mapKey, it->first, vectorOfMaps[mapsIndex])){
        value = mapKey + (it->second.first - it->first);
        } 
        else{
            value = mapKey;
    }

    return value;
}

// Jumping from one map to antoher.
int64_t getLocation(int64_t seed, std::vector<std::map<SOURCE, std::pair<DESTINATION, RANGE>>>& vectorOfMaps){ 
    int64_t soil = getValueFromMap(seed, 0, vectorOfMaps);
    int64_t fertilizer = getValueFromMap(soil, 1, vectorOfMaps);
    int64_t water = getValueFromMap(fertilizer, 2, vectorOfMaps);
    int64_t light = getValueFromMap(water, 3, vectorOfMaps);
    int64_t temperatur = getValueFromMap(light, 4, vectorOfMaps);
    int64_t humid = getValueFromMap(temperatur, 5, vectorOfMaps);
    int64_t location = getValueFromMap(humid, 6, vectorOfMaps);
    
    return location;   
}

int64_t getLowestLocation(std::vector<int64_t>& seeds, std::vector<std::map<SOURCE, std::pair<DESTINATION, RANGE>>>& vectorOfMaps){
    int64_t lowest = INT_MAX;

    for(auto seed : seeds){
        int64_t location = getLocation(seed, vectorOfMaps);
        if(location < lowest){
            lowest = location;
        }
    }

    return lowest;
}


int64_t solution1(){
    std::vector<int64_t> seeds = getSeeds();

    //MAP: key is source number, pair is <destination, range>
    std::vector<std::map<SOURCE,std::pair<DESTINATION, RANGE>>> vectorOfMaps;
    int64_t mapsIndex = -1;

    for(int64_t i = 1; i < numberOfLines; i++){

        if(lines[i].length() == 0){
            //Making a new map to store the "map" in
            std::map<SOURCE,std::pair<DESTINATION, RANGE>> newMap;
            vectorOfMaps.push_back(newMap);
            mapsIndex++;
            i += 2;
        }

        // Gets instructions as a vector.
        std::vector<int64_t> mapInstructions = stringOfIntsToLLVector(lines[i], ' ');

        // Inserts {source, pair<destination, range>} in the map. 
        vectorOfMaps[mapsIndex].insert({mapInstructions[1], {mapInstructions[0], mapInstructions[2]}});
        if(i % 1000000 == 0){
            std::cout << "runde" << std::endl;
        }
    }
    // Should be able to run the seeds through the system now. 
    int64_t lowest = getLowestLocation(seeds, vectorOfMaps);

    return lowest;
}

// This more a getSomeMoreSeeds method, as it doesn't get all seeds, because of memory.. Instead it runs one range of a time. Still it's not good, but will be able to power through it. 
std::vector<int64_t> getAllSeeds(std::vector<int64_t>& seeds, int64_t index){
    // Also just for the sake of updates. 
    std::cout << "Working on seeds in index " << index << std::endl;
    std::vector<int64_t> returnVector;
    for(int64_t i = 0; i < seeds[index+1]; i++){
        returnVector.push_back(seeds[index] + i);
    } 
    return returnVector;
}

int solution2(){
    std::vector<int64_t> someSeeds = getSeeds();
    int64_t runningLowest = LONG_MAX;

    // Runs for everyother seed in input file. 
    for(int i = 0; i < someSeeds.size(); i += 2){
        std::vector<int64_t> seeds = getAllSeeds(someSeeds, i);

        //MAP: key is source number, pair is <destination, range>
        std::vector<std::map<SOURCE,std::pair<DESTINATION, RANGE>>> vectorOfMaps;
        int64_t mapsIndex = -1;

        for(int64_t i = 1; i < numberOfLines; i++){

            if(lines[i].length() == 0){
                //Making a new map to store the "map" in
                std::map<SOURCE,std::pair<DESTINATION, RANGE>> newMap;
                vectorOfMaps.push_back(newMap);
                mapsIndex++;
                i += 2;
            }

            // Gets instructions as a vector.
            std::vector<int64_t> mapInstructions = stringOfIntsToLLVector(lines[i], ' ');

            // Inserts {source, pair<destination, range>} in the map. 
            vectorOfMaps[mapsIndex].insert({mapInstructions[1], {mapInstructions[0], mapInstructions[2]}});
        }

        // Should be able to run the seeds through the system now. 
        int64_t lowest = getLowestLocation(seeds, vectorOfMaps);
        if(lowest < runningLowest){

            // This is just to get some updates while it's running. (Also incase it crashes. )
            std::cout << "New lowest: " << lowest << std::endl;
            runningLowest = lowest;
        }
    }

    return runningLowest;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}