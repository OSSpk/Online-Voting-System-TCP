#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <pthread.h>

int port_number = 2007;

void *communicate (void *message)
{
	int client_sock = (int) message;
	char server_message[2000], client_message[2000];
	
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
    

	//--------------------------------------------------------------------------//	
	// Take name and CNIC from client

	//Receive Name/CNIC from the client
	if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
	{
		printf("Receive Failed. Error!!!!!\n");
	}
	
	char credentials[255];
	strcpy(credentials, client_message);

	//remove newline character
	char *newline;
	newline = strchr(credentials,'\n');
	if(newline != NULL)
		*newline = '\0';
	
	// Read Voters_List.txt and match CNIC and name, if match_exists then allow to vote else end thread
	FILE *fp;
	char buff[255];
	fp = fopen("./Voters_List.txt", "r");
	int voter_found = 0;
	
	while(fgets(buff, sizeof(buff), fp) != NULL)
	{	
		//remove newline and carriage return characters
		char *newline,*carriage_return;
		newline = strchr(buff,'\n');
		if(newline != NULL)
			*newline = '\0';

		carriage_return = strchr(buff,'\r');
		if(carriage_return != NULL)
			*carriage_return = '\0';	
	
		if (strcmp(credentials, buff) == 0)
		{
			voter_found = 1;
			break;
		}		
	}
	
	fclose(fp);

	// Check if this client has already casted a vote or note. If yes, then end thread
	if (voter_found == 1)
	{
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));

		//Send a greeting message back to client
		strcpy(server_message, "Welcome Voter.");

		if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
			printf("Send Failed. Error!!!!!\n");
		}	       

		fp = fopen("./Votes.txt", "r");
		
		int vote_casted = 0;
		
		while(fgets(buff, 200, fp) != NULL)
		{
			//parse string
			char *temp_comma;
			temp_comma = strchr(buff,',');
			if(temp_comma != NULL)
				*temp_comma = '\0';
						
			if (strcmp(credentials, buff) == 0)
			{
				vote_casted = 1;
				break;
			}		
		}
		
		fclose(fp);
		
		//vote not casted previously, so allow to cast vote
		if (vote_casted == 0)
		{
			//display candidates list
			fp = fopen("./Candidates_List.txt", "r");
								
			char candidates[1000];
			
			strcpy(candidates, "Following are the list of candidates and their symbols: \n");
			
			while (fgets(buff, sizeof(buff), fp) != NULL)
			{
				strcat(candidates,buff);
			}
			
			fclose(fp);		

			//send candidates data back to client
			
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			strcpy(server_message, candidates);

			if (send(client_sock, server_message, strlen(server_message),0)<0)
			{
				printf("Send Failed. Error!!!!!\n");
			}	       
			

			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			//Receive candidate's symbol from client
			if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
			{
				printf("Receive Failed. Error!!!!!\n");
			}
			
			//write this vote in Votes.txt
			char symbol[100];
			strcpy(symbol, client_message);

			char vote[200];
			strcpy(vote, credentials);
			strcat(vote, ",");
			strcat(vote, symbol);
			strcat(vote, "\n");
			
			fp = fopen("./Votes.txt", "a");
			fputs(vote, fp);
			fclose(fp);

			//send a vote casted message back to client
			
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			strcpy(server_message, "Congratulations! You have succesfully casted your vote.\n");

			if (send(client_sock, server_message, strlen(server_message),0)<0)
			{
				printf("Send Failed. Error!!!!!\n");
			}	       						
		}
		else
		{
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			strcpy(server_message, "Sorry! You have already casted a vote. You can't vote again.\n");

			if (send(client_sock, server_message, strlen(server_message),0)<0)
			{
				printf("Send Failed. Error!!!!!\n");
			}	       
		}	
	}
	else
	{
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));

		strcpy(server_message, "Sorry! Your name is not in the authorized voters list.\n");

		if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
			printf("Send Failed. Error!!!!!\n");
		}	       
	}
	
	//------------------------------------------------------------------------------//

	close(client_sock);
	pthread_exit(NULL); 
}



int main(void)
{
	int socket_desc, client_sock, client_size; 
	struct sockaddr_in server_addr, client_addr;
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
	
	//Binding IP and Port to socket        
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
	{
			printf("Bind Failed. Error!!!!!\n");
			return -1;
	}        
	
	printf("Bind Done\n");
	
	//Put the socket into Listening State        
	if(listen(socket_desc, 1) < 0)
	{
			printf("Listening Failed. Error!!!!!\n");
			return -1;
	}
	
	printf("Listening for Incoming Connections.....\n");
	
	//---------------------------------------------------------------------------//
	while (1)
	{		
		//Accept the incoming Connections	
		client_size = sizeof(client_addr);
		client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
	
		if (client_sock < 0)
		{
			printf("Accept Failed. Error!!!!!!\n");
			return -1;
		}
		
		printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
				
		strcpy(client_message, "Connection Established!");

		// Send the connection message back to client
		if (send(client_sock, client_message, strlen(client_message),0)<0)
		{
			printf("Send Failed. Error!!!!!\n");
			return -1;
		}
		
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));
		
		pthread_t thread1;
	
		//create new thread for each client
		pthread_create(&thread1,NULL,communicate,(void*)client_sock);
	}
    
	//Closing the Socket        
	close(socket_desc);
	return 0;       
}
