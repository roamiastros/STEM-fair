#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

int password_check(const std::string& filename, std::string_view password) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) if (!file) {std::cerr << "error: file " << filename << " not found/n";return 2;}

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
                        return 0;
                    }
                    current_line.clear();
                }
            } else {
                current_line.push_back(c); //add char to line beacause its not a newline
            }
        }
    }
    
    if (!current_line.empty() && current_line == password) {
        return 0;
    } 
    
    return 1;
}

int main(){
    std::string password;
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    int check = (password_check("/Users/ellioteror/password-breaking", password));//MAKE SURE THAT THIS IS THE ACTUAL PATH 
    if(check==0){ 
        std::cout << "password " << password<< " was found in the given file\n";
    }else if(check==1){
        std::cout << "password " << password << " was not found in the given file\n";
    }
}