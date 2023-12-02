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






