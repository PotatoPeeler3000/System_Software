//Nick Kitchel
// CS 270
// Client Server assignment

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //libaries to include for running program
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char* msg) //function is called when a system call fails
{
    perror(msg);        //print error message
    exit(0);
}

int main(int argc, char* argv[])        //command line arguments
{
    int sockfd, portno, n;      //varibles to store prot number and size and more
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];       //reading data buffer
    if (argc < 3) 
    {               //error print and exit, not enough command line arguments
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);     //store the portnumber
    sockfd = socket(AF_INET, SOCK_STREAM, 0);       //create socket
    if (sockfd < 0)     //socket failed
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {       //if the host doesn't work print and exit
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char*)&serv_addr, sizeof(serv_addr));        //set buffer all to zero
    serv_addr.sin_family = AF_INET;     //sets the fields in the struct serv_addr
    bcopy((char*)server->h_addr,        //copies data
        (char*)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0) //check if we can connect
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer, 256);     //read into buffer
    fgets(buffer, 255, stdin);      //store input to buffer
    n = write(sockfd, buffer, strlen(buffer));      //write data to server
    if (n < 0)      //check if we are successful or not
        error("ERROR writing to socket");
    bzero(buffer, 256);     //clear data from buffer and set to zero
    n = read(sockfd, buffer, 255);      //read data back from server
    if (n < 0)      //check if we have an error
        error("ERROR reading from socket");
    printf("The returned result to client is: %s\n", buffer);
    close(sockfd);      //close socket for safety
    return 0;
}
