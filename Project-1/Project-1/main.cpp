#include <iostream>
#include <filesystem>

int main() {
    std::cout << "Hello from Windows 11 C++17 Console App!\n";

    // C++17 filesystem demo
    std::cout << "Current Path: "<< std::filesystem::current_path() << "\n";

    return 0;
}
