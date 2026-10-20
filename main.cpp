#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>


bool password_check(const std::string& filename, std::string_view password){
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) return false;

    constexpr std::size_t CHUNK_SIZE = 64 * 1024;
    std::vector<char> buffer(CHUNK_SIZE);

    std::string current_line;
    current_line.reserve(256);

    while (file.read(buffer.data(), CHUNK_SIZE) || file.gcount() > 0){
        std::streamsize bytes_read = file.gcount();

        for (std::streamsize i = 0; i<bytes_read;++i){
            char c = buffer[i];

            if (c == '\n' || c == '\r'){
                if (!current_line.empty()){
                    if (current_line==password){
                        return true;
                    }
                    current_line.clear();
                }
            } else{
                current_line.push_back(c);
            }
        }
    }
    if (!current_line.empty() && current_line == password) return true;
    return false;
}

int main(){
    std::string password;
    std::cout << "Enter your password: ";
    std::cin >> password;
    if (password_check("/home/sami/Downloads/rockyou.txt", password)){
        std::cout << "PASSWORD " << password<< " FOUND IN rockyou.txt";
    }else{
        std::cout << "PASSWORD " << password << " was not found in rockyou.txt";
    }
}