#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>

bool password_check(const std::string& filename, std::string_view password) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) if (!file) {return false;  std::cerr<<"FILE NOT FOUND";}

    constexpr std::size_t CHUNK_SIZE = 64 * 1024; //64kb chunks
    std::vector<char> buffer(CHUNK_SIZE);//using buffer beacuse we may have 100+gb files but not ram

    std::string current_line;
    current_line.reserve(256);

    while (file.read(buffer.data(), CHUNK_SIZE) || file.gcount() > 0) {
        std::streamsize bytes_read = file.gcount(); //Read how big the file is

        for (std::streamsize i = 0; i < bytes_read; ++i) {
            char c = buffer[i]; //add thing to buffer.

            if (c == '\n' || c == '\r') { //newlines
                if (!current_line.empty()) { 
                    if (current_line == password) {
                        return true;
                    }
                    current_line.clear();
                }
            } else {
                current_line.push_back(c); //add char to line beacause its not a newline
            }
        }
    }
    
    if (!current_line.empty() && current_line == password) {
        return true;
    } 
    
    return false;
}

int main(){
    std::string password;
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    if (password_check("/home/sami/Downloads/weakpass.txt", password)){ //MAKE SURE THAT THIS IS THE ACTUAL PATH 
        std::cout << "password " << password<< " was found in the given file\n";
    }else{
        std::cout << "password " << password << " was not found in the given file\n";
    }
}