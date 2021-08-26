//Cliente
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define MAX 255
   
int main(int argc, char const *argv[]){
    //vars
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello;
    char buffer[1024] = {0};
    
	//Creacion del socket
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Error en la creacion del socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    //Se convierte las direcciones IPv4 y IPv6 de texto a binario
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("\nDireccion invalida/Direccion no soportada \n");
        return -1;
    }
    
	//Llamada al sistema que conecta al socket al que hace referencia sock
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nError de conexion \n");
        return -1;
    }
    
    //Recibo la bienvenida/pregunta.
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    scanf("%[^\n]",hello);
    
    //Envio respuesta al servidor
    send(sock , hello , strlen(hello) , 0);
    printf("Mensaje enviado correctamente.\n");
    
    //Recibir bienvenida completa
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    return 0;
}