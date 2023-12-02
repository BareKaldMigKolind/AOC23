#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class File {
    private:
       std::ifstream myfile;
       std::ifstream mytest;

    public:
       File(const std::string filename, const std::string testname)
           : myfile(filename), mytest(testname) {}

       ~File() {
           if (myfile.is_open()) {
               myfile.close();
           }
           if (mytest.is_open()) {
               mytest.close();
           }
       }
        /// @brief Makes a file into a vector of lines
        /// @tparam T Should mainly be either int or string.
        /// @param useTestFile The File class can hold both the input file and the test bit. This determines wether to use.
        /// @return Returns a vector of type T consisting of each line in the file
        template <typename T>
        std::vector<T> file_to_vector(bool useTestFile) {
            std::ifstream& tempfile = useTestFile ? mytest : myfile;

            std::vector<T> lines;
            std::string line;

            while (std::getline(tempfile, line)) {
                if constexpr (std::is_integral_v<T>) {
                    lines.push_back(std::stoi(line));
                } else {
                    lines.push_back(line);
                }
            }
        return lines;
    }
};
