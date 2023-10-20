// client_fifo.cpp
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

int main() {
    const char* fifo_path_to_server = "/tmp/ipc_fifo_to_server";
    const char* fifo_path_from_server = "/tmp/ipc_fifo_from_server";
    char buf[100];

    int fifo_fd_to_server = open(fifo_path_to_server, O_WRONLY);
    int fifo_fd_from_server = open(fifo_path_from_server, O_RDONLY);

    while(true) {
        // Enviar mensaje
        const char* message = "Hola desde el cliente";
        write(fifo_fd_to_server, message, strlen(message));
        sleep(5); // Esperar 5 segundos antes de enviar otro mensaje

        // Leer respuesta del servidor
        if(read(fifo_fd_from_server, buf, sizeof(buf)) > 0) {
            std::cout << "Cliente recibió: " << buf << std::endl;
        }
    }

    close(fifo_fd_to_server);
    close(fifo_fd_from_server);
    return 0;
}
