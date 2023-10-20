// server_fifo.cpp
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

int main() {
    const char* fifo_path_to_server = "/tmp/ipc_fifo_to_server";
    const char* fifo_path_from_server = "/tmp/ipc_fifo_from_server";
    mkfifo(fifo_path_to_server, 0666);
    mkfifo(fifo_path_from_server, 0666);

    char buf[100];
    int fifo_fd_to_server = open(fifo_path_to_server, O_RDONLY);
    int fifo_fd_from_server = open(fifo_path_from_server, O_WRONLY);

    while(true) {
        // Leer mensaje del cliente
        if(read(fifo_fd_to_server, buf, sizeof(buf)) > 0) {
            std::cout << "Servidor recibió: " << buf << std::endl;
        }

        // Enviar respuesta
        const char* response = "Mensaje desde el servidor";
        write(fifo_fd_from_server, response, strlen(response));
        sleep(2); // Esperar 2 segundos antes de enviar otro mensaje
    }

    close(fifo_fd_to_server);
    close(fifo_fd_from_server);
    unlink(fifo_path_to_server);
    unlink(fifo_path_from_server);
    return 0;
}
