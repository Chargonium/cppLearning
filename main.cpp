#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include <windows.h>
#include <SFML/Graphics.hpp>

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
        int percentage = 100 / len * i;
        char temp[len+1];
        std::fill(temp, temp + i, '#');
        std::fill(temp + i, temp + len, '=');
        temp[len]='\0';
        std::cout << '\r' << percentage << "% ";
        std::cout << '[' << temp << ']' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration/len)); // Why the actual fuck doesnt this properly update the shits in the intellij terminal 😔
    }
    std::cout << '\r' << std::endl;
    showCursor();
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void quit(int signal) {
    if (signal == SIGINT) {
        showCursor();
        std::exit(signal);
    }
}

int main() {
    int frame = 0;
    int fps = 60;
    int mode;

    char buffer;

    std::cout << "Oh my god, Im learning shit" << std::endl;
    std::cout << "Anyways, progress bar or window (p/w) ";
    std::cin >> buffer;

    if (buffer == 'p') {
        mode = 0;
    } else if (buffer == 'w') {
        mode = 1;
    } else {
        mode = -1;
    }

    if (mode == 0) {
        // Disable syncing with C stdio for performance
        char input_buffer[1024];
        std::cout << "What command do you wanna run bich? ";
        std::cin.ignore();
        std::cin.getline(input_buffer, 1024);

        std::cout << "Oh my god, Look at this W progress bar!" << std::endl;
        progressBar(100, 500*strlen(input_buffer));

        std::string output;
        output = exec(input_buffer);

        std::cout << "Da command outputted this shi!" << std::endl << output << std::endl;
    } else if (mode == 1) {
        std::cout << "Alright; Here have an random ahh window!" << std::endl;

        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(fps);

        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (frame % 4 == 0) {
                window.clear(sf::Color::White);
            } else {
                window.clear(sf::Color::Black);
            }

            window.display();
            frame++;

            std::signal(SIGINT, quit);

            hideCursor();

            std::cout << '\r' << frame << std::flush;
        }
    } else if (mode == -1) {
        return mode;
    }

    return 0;
}
