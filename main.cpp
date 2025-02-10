#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>


void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Get current cursor settings
    cursorInfo.bVisible = FALSE;                      // Hide cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Apply changes
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Show cursor again
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void progressBar(int len, int duration) {
    hideCursor();
    for (int i = 1; i <= len; i++) {
        char temp[len+1];
        std::fill(temp, temp + i, '#');
        std::fill(temp + i, temp + len, '=');
        temp[len]='\0';
        std::cout << '\r' << '[' << temp << ']' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration/len)); // Why the actual fuck doesnt this properly update the shits in the intellij terminal 😔
    }
    std::cout << '\r' << std::endl;
    showCursor();
}

std::string exec(const char* cmd) {
    /// Thank you random stackoverflow answer
    /// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po

    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {

     // Disable syncing with C stdio for performance
    char input_buffer[1024];
    std::cout << "What command do you wanna run bich? ";
    std::cin.getline(input_buffer, 1024);

    std::cout << "Oh my god, Look at this W progress bar!" << std::endl;
    progressBar(100, 500*strlen(input_buffer));

    std::string output;
    output = exec(input_buffer);

    std::cout << "Da command outputted this shi!" << std::endl << output << std::endl;

    return 0;
}
