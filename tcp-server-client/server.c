#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    char *reply = "Hello from server";

    // 1. Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    // 2. Allow immediate reuse of the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    // 3. Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    // 4. Start listening
    if (listen(server_fd, 10) < 0) { // Increased backlog queue to 10
        perror("Listen failed");
        close(server_fd);
        return EXIT_FAILURE;
    }
    
    printf("Server is listening on port %d... (Press Ctrl+C to stop)\n", PORT);

    // 5. Infinite loop to continuously accept connections
    while (1) {
        // Accept blocks until a client connects
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue; // Move to the next iteration instead of crashing
        }
        
        printf("\n[New Connection] Client connected from %s:%d\n", 
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // Clear the buffer before reading
        memset(buffer, 0, BUFFER_SIZE);

        // 6. Read data sent by the client
        ssize_t valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Client says: %s\n", buffer);
            
            // 7. Send a response back to the client
            send(new_socket, reply, strlen(reply), 0);
            printf("Reply message sent\n");
        } else if (valread == 0) {
            printf("Client disconnected without sending data.\n");
        } else {
            perror("Read failed");
        }

        // 8. Close the client socket for this session
        close(new_socket);
        printf("[Disconnected] Connection closed.\n");
    }

    // This line is technically unreachable now, but kept for completeness
    close(server_fd);
    return EXIT_SUCCESS;
}