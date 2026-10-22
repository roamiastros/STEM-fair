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
    // FIX: Remove std::ios::ate so it reads from the beginning!
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    constexpr std::size_t CHUNK_SIZE = 64 * 1024;
    std::vector<char> buffer(CHUNK_SIZE);

    std::string current_line;
    current_line.reserve(256);

    while (file.read(buffer.data(), CHUNK_SIZE) || file.gcount() > 0) {
        std::streamsize bytes_read = file.gcount();

        for (std::streamsize i = 0; i < bytes_read; ++i) {
            char c = buffer[i];

            if (c == '\n' || c == '\r') {
                // Only evaluate the line if we actually collected characters
                if (!current_line.empty()) {
                    if (current_line == password) {
                        return true;
                    }
                    current_line.clear();
                }
            } else {
                current_line.push_back(c);
            }
        }
    }
    
    // Check the very last line if the file didn't end with a newline
    if (!current_line.empty() && current_line == password) {
        return true;
    }
    
    return false;
}

int main(){
    std::string password;
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    if (password_check("/home/sami/Downloads/rockyou.txt", password)){
        std::cout << "password " << password<< " was found in rockyou.txt\n";
    }else{
        std::cout << "password " << password << " was not found in rockyou.txt\n";
    }
}