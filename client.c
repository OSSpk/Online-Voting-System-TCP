#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int port_number = 2007;

int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000], client_message[2000];
	
	//Cleaning the Buffers	
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//Creating Socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		printf("Could Not Create Socket. Error!!!!!\n");
		return -1;
	}
	
	printf("Socket Created\n");
	
	//Specifying the IP and Port of the server to connect
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//------------------------------------------------------------------------------------------------//
	
    //Now connecting to the server accept() using connect() from client side
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Connection Failed. Error!!!!!");
		return -1;
	}
 
	//Receive the connection message back from the server		
	if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	{
		printf("Receive Failed. Error!!!!!\n");
		return -1;
	}
	
	printf("Server Message: %s\n\n",server_message);
	
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));				

	//Get Input from the User
	printf("Enter your name and CNIC in format (Haris Muneer/35601-4426749-2): ");
	fgets(client_message, 200, stdin);

	//Send credentials back to Server	
	if(send(socket_desc, client_message, strlen(client_message),0) < 0)
	{
		printf("Send Failed. Error!!!!\n");
		return -1;
	}		

	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));				

	
	//Receive the message back from the server		
	if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	{
		printf("Receive Failed. Error!!!!!\n");
		return -1;
	}

	printf("Server Message: %s\n\n",server_message);

	if (strcmp(server_message, "Sorry! Your name is not in the authorized voters list.\n") != 0)
	{
		//Receive the message back from the server		
		if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
		{
			printf("Receive Failed. Error!!!!!\n");
			return -1;
		}

		printf("Server Message: %s\n\n",server_message);

		if (strcmp(server_message, "Sorry! You have already casted a vote. You can't vote again.\n") != 0)
		{
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));				

			//Get Input Symbol from the User	
			printf("Enter the candidate's symbol: ");
			fgets(client_message, 200, stdin);
		
			//Send the symbol back to server			
			if(send(socket_desc, client_message, strlen(client_message),0) < 0)
			{
				printf("Send Failed. Error!!!!\n");
				return -1;
			}		
			
			//Receive confirmation from server		
			if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
			{
				printf("Receive Failed. Error!!!!!\n");
				return -1;
			}

			printf("Server Message: %s\n\n",server_message);
		}			
	}

	//Closing the Socket
	close(socket_desc);
	return 0;
}

