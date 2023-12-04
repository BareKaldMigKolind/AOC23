#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/// @brief Prints a vector of Type T
/// @tparam T Ideally is either int or String.
/// @param vec The vector to print
/// @param name This is just to identify what is being printed
template <typename T>
void print_vector(std::vector<T> vec, std::string name){
    std::cout << "Elements in "<< name << std::endl;
    std::cout << "=================================" << std::endl;
    for(T element : vec){
        std::cout << "\"" << element << "\"" << std::endl;
    }
    std::cout << "=================================" << std::endl;
}

/// @brief Method to convert binary to integers
/// @param binaryString - the string of a binary number you want to convert. 
/// @return integer number of the given binary
int binaryToInt(const std::string& binaryString) {
   return std::stoi(binaryString, nullptr, 2);
}

/// @brief Takes a string, returns the int
/// @param str The integer as string
/// @return The corresponding int for the given string.
int stringToInt(std::string str){
    return std::stoi(str);
}

/// @brief Takes a character returns the corresponding int. 
/// @param ch The char, preferably a digit as char.
/// @return The corresponding int, (0-9)
int charToInt(char ch){
    return int(ch) - 48;
}

/// @brief Method to split a string into a vector on a given char.
/// @param str The string you want to split
/// @param ch The char to split on
/// @return Returns a vector with elements n + 1, where n is occurences of ch in str. Each element is a string
template <typename T>
std::vector<T> split_on_char(std::string str, char ch) {
   std::stringstream ss(str);

   std::string word;
   std::vector<T> words;

   while(std::getline(ss, word, ch)) {
       if constexpr (std::is_same_v<T, std::string>) {
           words.push_back(word);
       } else if constexpr (std::is_integral_v<T>) {
           words.push_back(std::stoi(word));
       }
   }
   return words;
}

/// @brief Method to convert a string of numbers seperated by the same char into a vector of int.
/// @param str The string of ints 
/// @param seperator The seperator to split on.
/// @return A int vector with all ints from the string. 
std::vector<int> stringOfIntsToIntVector(std::string str, char seperator){
    std::vector<std::string> stringVector = split_on_char<std::string>(str, seperator);
    std::vector<int> intVector;

    for(auto element : stringVector){
        if(element.length() == 0){
            continue;
        } else{
            intVector.push_back(stringToInt(element));
        }
    }
    return intVector;
}

/// @brief Often input data starts with "Game 1:" or something like that, this will clean that.
/// @param vec The vector loaded from file
/// @param character The char to split the line on. Often ':'
/// @return A vector where all lines begins after the seperator. 
std::vector<std::string> cleanedLines(std::vector<std::string> vec, char character){
    std::vector<std::string> cleanVector;

    for(auto line : vec){
        std::vector<std::string> splittedLine = split_on_char<std::string>(line, character);
        cleanVector.push_back(splittedLine[1]);
    }

    return cleanVector;
}

/// @brief Sums the values of a vector.
/// @param vec The int vector to sum over.
/// @return The sum...
int sumOfVector(std::vector<int> vec){
    int sum = 0;
    for(int value : vec){
        sum += value;
    }
    return sum;
}






