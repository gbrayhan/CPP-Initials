// consumer.cpp
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <csignal>

volatile bool keepRunning = true;

void handleSignal(int signal) {
    keepRunning = false;
}

const char* codeToMeaning(int code) {
    switch (code) {
        case 200: return "OK";
        case 201: return "Created";
        case 400: return "Bad Request";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default: return "Unknown";
    }
}

std::string getCurrentTime() {
    std::time_t t = std::time(nullptr);
    char buffer[100];
    if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) {
        return buffer;
    }
    return "Unknown time";
}

int main() {
    const char* fifo_path = "/tmp/http_fifo";
    mkfifo(fifo_path, 0666);

    int fifo_fd = open(fifo_path, O_RDONLY);

    std::ofstream logFile("log.txt", std::ios::app); // Abre o crea archivo para agregar datos

    // Registra el manejador de señales
    signal(SIGINT, handleSignal);

    while(keepRunning) {
        int code;
        if(read(fifo_fd, &code, sizeof(code)) > 0) {
            const char* meaning = codeToMeaning(code);
            std::string timeReceived = getCurrentTime();

            std::cout << "Message to write: " << code << " | " << meaning << " | " << timeReceived << std::endl;
            logFile << code << " | " << meaning << " | " << timeReceived << std::endl; // Usar std::endl
        }
    }

    // Estas líneas se ejecutarán cuando presiones Ctrl+C
    logFile.close();
    close(fifo_fd);
    unlink(fifo_path);
    return 0;
}
