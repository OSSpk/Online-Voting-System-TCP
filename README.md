# Online Voting System-TCP

Online Voting system
You are to devise an online vote casting system using TCP multithreaded server-client program. The voters will log on from client systems and cast their votes. Note that:
One client can cast a vote ONCE AND ONLY ONCE. 
A list of registered voters is available in a text file in the following format: 
Name/CNIC number
System should be secure and should only allow clients with authentic name and CNIC to cast the vote.
The Server shall 
•	First of all take the client’s name and CNIC and match it with the content of the text file (Voters_List.txt). 
•	If the details match, then it will welcome the voter and display the names and poll symbols of the candidates on the terminal.(Candidates_List.txt) 
•	The voter will then cast the vote by MENTIONING THE POLL SYMBOL (not the name) OF THE CANDIDATE. All these details are to be recorded in an output text file. This system should work perfectly for at least 5 different clients. 
•	If there is problem of load shedding of electric light (as is norm in Pakistan), then your system should not lose track of the votes being already casted once your server restarts again when light comes back on.
•	Assume that when the record of votes will be written by one thread in an output file, no other thread will make a read to the output file.

