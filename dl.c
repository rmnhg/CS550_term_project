#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include <string.h>
#include <time.h> 

#define MAX_LENGTH 256


int ReadHttpStatus(int sock){
    char c;
    char buff[1024]="",*ptr=buff+1;
    int bytes_received, status;
    printf("Begin Response ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("ReadHttpStatus");
            exit(1);
        }

        if((ptr[-1]=='\r')  && (*ptr=='\n' )) break;
        ptr++;
    }
    *ptr=0;
    ptr=buff+1;

    sscanf(ptr,"%*s %d ", &status);

    printf("%s\n",ptr);
    printf("status=%d\n",status);
    printf("End Response ..\n");
    return (bytes_received>0)?status:0;

}

//the only filed that it parsed is 'Content-Length' 
int ParseHeader(int sock){
    char c;
    char buff[1024]="",*ptr=buff+4;
    int bytes_received, status;
    printf("Begin HEADER ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("Parse Header");
            exit(1);
        }

        if(
            (ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&
            (ptr[-1]=='\r')  && (*ptr=='\n' )
        ) break;
        ptr++;
    }

    *ptr=0;
    ptr=buff+4;
    //printf("%s",ptr);

    if(bytes_received){
        ptr=strstr(ptr,"Content-Length:");
        if(ptr) {
            sscanf(ptr,"%*s %d",&bytes_received);

        } else
            bytes_received=-1; //unknown size

       printf("Content-Length: %d\n",bytes_received);
    }
    printf("End HEADER ..\n");
    return  bytes_received ;

}

void printHelp(char *binName) {
    printf("Usage: %s <IP> <port> <PathToFile> <destFile>\n", binName);
    printf("The destination file can be skipped, so that we just store the file in memory measuring the download time.\n");
    printf("Also remember to run \"python3 -m http.server\" in the folder you want to create the file server!\n");

}

int main(int argc, char **argv) {
    char domain[MAX_LENGTH];
    int port;
    char path[MAX_LENGTH];
    char dest_file[MAX_LENGTH];
    if (argc >= 4) {
        snprintf(domain, strlen(argv[1]) + 1, "%s", argv[1]);
        port = atoi(argv[2]);
        snprintf(path, strlen(argv[3]) + 1, "%s", argv[3]);
        printf("Using http://%s:%d/%s as file path.\n", domain, port, path);
        if (argc > 4) {
            snprintf(dest_file, strlen(argv[4]) + 1, "%s", argv[4]);
            printf("Using %s as target file.\n", dest_file);
        }
    } else {
        printHelp(argv[0]);
        return 0;
    }

    int sock, bytes_received;  
    char send_data[1024],recv_data[1024], *p;
    struct sockaddr_in server_addr;
    struct hostent *he;


    he = gethostbyname(domain);
    if (he == NULL){
       herror("gethostbyname");
       exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0))== -1){
       perror("Socket");
       exit(1);
    }
    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server_addr.sin_zero),8); 

    printf("Connecting ...\n");
    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
       perror("Connect");
       exit(1); 
    }

    printf("Sending data ...\n");

    snprintf(send_data, sizeof(send_data), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, domain);

    if(send(sock, send_data, strlen(send_data), 0)==-1){
        perror("send");
        exit(2); 
    }
    printf("Data sent.\n");  

    printf("Receiving data...\n\n");

    int contentLength;

    if (ReadHttpStatus(sock) && (contentLength=ParseHeader(sock))) { //CAMBIAR PARA DESCARGAR ARCHIVO Sí O SÍ SIN GUARDARLO SIEMPRE
        int bytes = 0;
        FILE* fd;
        clock_t t;
        if (argc > 4) {
            fd = fopen(dest_file, "wb");
            printf("Saving data to %s file...\n\n", dest_file);
        } else {
            printf("Downloading file to memory without storing it...\n");
        }

        t = clock(); // Start time
        while (bytes_received = recv(sock, recv_data, 1024, 0)) {
            if (bytes_received==-1) {
                perror("receive");
                exit(3);
            }

            if (argc > 4)
                fwrite(recv_data, 1, bytes_received, fd);
            bytes += bytes_received;
            printf("Bytes received: %d from %d (%.2f %%)\n", bytes, contentLength, ((float) bytes)/contentLength * 100);
            if (bytes == contentLength)
                break;
        }
        t = clock() - t; // Final time
        // Convert time to seconds
        double time_taken = ((double) t)/CLOCKS_PER_SEC; // in seconds
        printf("Downloaded file of %d bytes (%.2f MiBs) in %f seconds (%.2f Bps or %.2f MiBps)\n", contentLength, ((float) contentLength)/(1024 * 1024), time_taken, ((float) contentLength)/time_taken, ((float) contentLength)/(time_taken * 1024 * 1024));

        if (argc > 4)
            fclose(fd);
    }



    close(sock);
    printf("\n\nDone.\n\n");
    return 0;
}