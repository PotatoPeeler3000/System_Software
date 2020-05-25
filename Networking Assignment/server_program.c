    //Nick Kitchel
//CS 270
//Client Server assignment

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     //libraries needed to run program
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char* msg)     //prints error message if called, then exits
{
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[])        //command line arguments
{
    int sockfd, newsockfd, portno;      //variables for socket data, buffer size, and host number
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;      //counter for valid input
    if (argc < 2) {         //check for correct command line arguments
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);        //if not exit
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);       //create socket
    if (sockfd < 0)     //check if it was successful or not
        error("ERROR opening socket");
    bzero((char*)&serv_addr, sizeof(serv_addr));        //clear the serv_addr and input size of it as well
    portno = atoi(argv[1]);     //set port number
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr*) & serv_addr,        //bind to the client
        sizeof(serv_addr)) < 0)     //check if it is valid
        error("ERROR on binding");
    listen(sockfd, 5);      //then listen to client, this call should never fail it bind is working
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,      //create new sockets
        (struct sockaddr*) & cli_addr,
        &clilen);
    if (newsockfd < 0)      //check if it is set up correctly
        error("ERROR on accept");
    bzero(buffer, 256);     //clear buffer and set to all zero
    n = read(newsockfd, buffer, 255);       //read from client
    if (n < 0) error("ERROR reading from socket");      //check if it worked or not
   
    char* sign;     //calculator sigh
    char* num1_input;
    char* num2_input;       //input storage of number spots
    char space[2] = " ";    //token stopper
    char returned_result[18];   //piped char back to client variable

    double num1;
    double num2;        //two numbers to calculate together
    int cpnum1;
    int cpnum2;
    double result;

    sign = strtok(buffer, space);       //set sign to the first input from command line
    num1_input = strtok(NULL, space);
    num2_input = strtok(NULL, space);       //declar numbers to the input string numbers

    num1 = atoi(num1_input);
    num2 = atoi(num2_input);        //convert to numbers to be calculated

    if (strcmp(sign, "*") == 0)     //check for a *
    {
        result = num1 * num2;       //calculate if find it
    }
    else if (strcmp(sign, "+") == 0)        //check for a +
    {
        result = num1 + num2;       //perform calculation
    }
    else if (strcmp(sign, "-") == 0)    //keep checking for different calculating types
    {
        result = num1 - num2;
    }
    else if (strcmp(sign, "/") == 0)
    {
        result = num1 / num2;
    }
    else if (strcmp(sign, "%") == 0)
    {
        cpnum1 = num1;      //if we are using '%' then convert numbers to int so it will work
        cpnum2 = num2;
        result = cpnum1 % cpnum2;       //store the result
    }

    printf("Result on server side: %f\n", result);

    sprintf(returned_result, "%f", result);     //convert number to string to send to client

    n = write(newsockfd, returned_result, 18);      //write back to client the result
    if (n < 0) error("ERROR writing to socket");        //check if it worked or not and print message
    close(newsockfd);
    close(sockfd);      //close sockets to end program
    return 0;
}
