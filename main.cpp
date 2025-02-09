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

void progressBar(int len) {
    hideCursor();
    for (int i = 1; i <= len; i++) {
        char temp[len+1];
        std::fill(temp, temp + i, '#');
        std::fill(temp + i, temp + len, '=');
        temp[len]='\0';
        std::cout << '\r' << '[' << temp << ']' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Why the actual fuck doesnt this properly update the shits in the intellij terminal 😔
    }
    std::cout << '\r' << std::endl;
    showCursor();
}

int main() {
    std::cout << "Oh my god, Look at this W progress bar!" << std::endl;
    std::ios_base::sync_with_stdio(false); // Disable syncing with C stdio for performance
    progressBar(100);
    return 0;
}
