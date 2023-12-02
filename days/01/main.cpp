#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int n = lines[0].length();
// ======================================================== //

int solution1(){
    int sum = 0;

    for(auto line : lines){
        int first = -1;
        int last = -1;
        for(int i = 0; i < line.length(); i++){
            if(isdigit(line[i])){
                first = int(line[i]) - 48;
                break;
            }
        }
        for(int i = line.length(); i >= 0; i--){
            if(isdigit(line[i])){
                last = int(line[i]) - 48;
                break;
            }
        }
       
        int combined = first * 10 + last;
        sum += combined;
        //std::cout << sum << std::endl;
    }

    return sum;
}

std::vector<std::string> numbersAsString{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

/// @brief Method to find either first or last occurence of a written number, e.g. "one", "two", etc. 
/// @param str The string you want to check the occurrence of a number in.
/// @param findFirst Bool to decide if you are looking for the first or last occurence. 
/// @return A pair of ints. First is the index, Last is the value of the int. -1 means no occurence. 
std::pair<int, int> occurenceOfWrittenNumber(std::string str, bool findFirst){
    std::pair<int, int> currentIndexPair;
    currentIndexPair.first = findFirst ? 100000 : -1;
    currentIndexPair.second = -1;

        for(int i = 0; i < numbersAsString.size(); i++){
        int wordFoundAt = findFirst ? str.find(numbersAsString[i]) : str.rfind(numbersAsString[i]);

        if(wordFoundAt == -1){
            continue;
        }

        if((findFirst && wordFoundAt < currentIndexPair.first) || (!findFirst && wordFoundAt > currentIndexPair.first)){
            currentIndexPair.first = wordFoundAt;
            currentIndexPair.second = i + 1;
        };        
    }

    if(currentIndexPair.first == 100000){
        currentIndexPair.first = -1;
    }

    return currentIndexPair;
}


int solution2(){

    int sum = 0;

    for(auto line : lines){
        int first = -1;
        int last = -1;

        for(int i = 0; i < line.length(); i++){
            
            if(isdigit(line[i])){
                std::string subline = line.substr(0, i);
                std::pair<int, int> written_int_pair = occurenceOfWrittenNumber(subline, true);

                if(written_int_pair.first != -1 && written_int_pair.first < i){
                    first = written_int_pair.second;
                } else {
                    first = int(line[i]) - 48;
                }
                break;
            } 

            if(first == -1 ){
                std::pair<int, int> written_int_pair = occurenceOfWrittenNumber(line, true);
                first = written_int_pair.second;
            }
        }

        for(int i = line.length(); i >= 0; i--){

            if(isdigit(line[i])){
                std::pair<int, int> written_int_pair = occurenceOfWrittenNumber(line, false);

                if(written_int_pair.first != -1 && written_int_pair.first > i){
                    if(written_int_pair.first == 1 && written_int_pair.second == 5){
                    }
                    last = written_int_pair.second;
                } else{
                    last = int(line[i]) - 48;
                }

                break;
            }

            if(last == -1){
                std::pair<int, int> written_int_pair = occurenceOfWrittenNumber(line, false);
                last = written_int_pair.second;
            }
        }
       
        int combined = first * 10 + last;
        sum += combined;
    }

    return sum;
}

int main(){

    std::cout << "Solution for part 1 is: " << solution1() << std::endl;
    std::cout << "Solution for part 2 is: " << solution2() << std::endl;

    return 0;
}