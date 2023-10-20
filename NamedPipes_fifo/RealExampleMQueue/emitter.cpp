//
// Created by Alejandro Gabriel Guerrero on 19/10/23.
//
// emitter.cpp
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>


int main() {
    const char* fifo_path = "/tmp/http_fifo";
    mkfifo(fifo_path, 0666);

    int fifo_fd = open(fifo_path, O_WRONLY);

    srand(time(nullptr)); // Para generar números aleatorios

    while(true) {
        int codes[] = {200, 201, 400, 404, 500}; // Puedes expandir la lista
        int random_index = rand() % 5; // Asumiendo que hay 5 códigos
        int code = codes[random_index];

        write(fifo_fd, &code, sizeof(code));
        sleep(1); // Esperar 1 segundo antes de enviar otro código
    }

    close(fifo_fd);
    unlink(fifo_path);
    return 0;
}
