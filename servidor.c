// Servidor
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define MAX 255

//funcion auxiliar
void concatena(char *p1,char *p2,char *p3){
    strcat(p1,p2);
    strcat(p1,p3);
}

int main(int argc, char const *argv[]){
    
    //vars
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char hello[MAX],msj1[MAX],msj2[MAX];
       
    //Creacion del socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    //Set opciones del socket (opcional, previene error "Direccion ya en uso")
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    //Fijar socket al puerto address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //Se coloca al servidor en modo pasivo, esperando un cliente
    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("El servidor esta activo.\n");
    //Acepta la primer condicion de la cola de conexiones pendientes
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //Cargo el mensaje de bienvenida
    strcpy(hello,"Hola, soy el servidor. Como te llamas? ");
    
    //Envio Bienvenida
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Envie la bienvenida!\n");
    
    //Recibo el nombre del usuario
    valread = read( new_socket , buffer, 1024);
    printf("El cliente se llama: %s.\n",buffer );
    
    //Crear el mensaje predeterminado
    
    strcpy(msj1,"Hola ");
    strcpy(msj2,", ¡Bienvenido!");
    concatena(msj1,buffer,msj2);
    
    //Envio el mensaje predeterminado
    send(new_socket , msj1 , strlen(hello) , 0 );
    printf("Ya envie el mensaje predeterminado. Saludos!\n");

    return 0;
}