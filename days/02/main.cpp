#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

std::vector<std::string> colors{"blue", "red", "green"};

/// @brief Method to find color in string.
/// @param setDraw string to search in. 
/// @return Returns 0 if blue, 1 if red, 2 if green and -1 if no color found(Error)
int getColor(std::string setDraw){
    for(int i = 0; i < colors.size(); i++){
        int colorIndex = setDraw.find(colors[i]);
        if(colorIndex != std::string::npos){
            return i;
        }
    }
    return -1;    
}

/// @brief Method to get int from a string
/// @param str string you want to find int in
/// @return The FIRST integer in the string. 
int getInt(std::string str){

    std::stringstream ss;
    ss << str;

    std::string temp;
    int found;

    while(!ss.eof()){
        ss >> temp;

        if (std::stringstream(temp) >> found){
            return found;
        }

        temp = "";
    }
    return -1;
}

/// @brief Method to return the sum of game ID's of the possible games
/// @param vec Possible games vector
/// @return The sum of the game ID's
int sumOfIDs(std::vector<bool> vec){
    int sum = 0;
    
    for(int i = 0; i < vec.size(); i++){
        if(vec[i]){
            sum += i + 1;
        }
    }
    return sum;
}

int solution1(){
    int red = 12;
    int green = 13;
    int blue = 14;
    std::vector<std::string> gameLines = cleanedLines(lines, ':');
    std::vector<bool> possibleGames;

    // For loop on every line in the game
    for(int i = 0; i < numberOfLines; i++){

        bool lineIsOk = true;
        std::vector<std::string> sets = split_on_char<std::string>(gameLines[i], ';');

        // For loop on every set in each line
        for(int j = 0; j < sets.size(); j++){
            if(lineIsOk == false){
                break;
            }
            std::vector<std::string> drawing = split_on_char<std::string>(sets[j], ',');

            // For loop on each draw in each set
            for(auto draw : drawing){
                if(lineIsOk == false){
                    break;
                };
                int color = getColor(draw);

                // Draw is blue
                if(color == 0){
                    if(getInt(draw) > blue){
                        possibleGames.push_back(false);
                        lineIsOk = false;
                        break;
                    }
                
                // Draw is red
                } else if(color == 1){
                    if(getInt(draw) > red){
                        possibleGames.push_back(false);
                        lineIsOk = false;
                        break;
                    }

                // Draw is green
                } else if(color == 2){
                    if(getInt(draw) > green){
                        possibleGames.push_back(false);
                        lineIsOk = false;
                        break;
                    }
                }
            }

            if(j == sets.size() - 1 && lineIsOk){
                possibleGames.push_back(true);
            }
        }
    }

    return sumOfIDs(possibleGames);       
}

int solution2(){
    int sum = 0;

    std::vector<std::string> gameLines = cleanedLines(lines, ':');
    std::vector<bool> possibleGames;

    // For loop on every line in the game
    for(int i = 0; i < numberOfLines; i++){
        int blue = 0;
        int red = 0;
        int green = 0;
        int combined = 0; 

        std::vector<std::string> sets = split_on_char<std::string>(gameLines[i], ';');

        // For loop on every set in each line
        for(int j = 0; j < sets.size(); j++){

            std::vector<std::string> drawing = split_on_char<std::string>(sets[j], ',');

            // For loop on each draw in each set
            for(auto draw : drawing){
                int color = getColor(draw);
                int number = getInt(draw);

                // Draw is blue
                if(color == 0){
                    if(number > blue){
                        blue = number;
                    }
                
                // Draw is red
                } else if(color == 1){
                    if(number > red){
                        red = number;
                    }

                // Draw is green
                } else if(color == 2){
                    if(number > green){
                        green = number;
                    }
                }
            }
        }

        combined = blue * red * green;
        sum += combined;
    }

    return sum;
}


int main(){

    std::cout << "Solution for part a: "<< solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}