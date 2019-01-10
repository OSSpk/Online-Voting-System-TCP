# 🗳️ Online Voting System using Multi-Threaded TCP Sockets
[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](#)
[![GitHub Forks](https://img.shields.io/github/forks/harismuneer/Online-Voting-System-TCP.svg?style=social&label=Fork&maxAge=2592000)](https://www.github.com/harismuneer/Online-Voting-System-TCP/fork)
[![Build Status](https://semaphoreapp.com/api/v1/projects/d4cca506-99be-44d2-b19e-176f36ec8cf1/128505/badge.svg)](#)
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Online-Voting-System-TCP.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Online-Voting-System-TCP/issues)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat&label=Contributions&colorA=red&colorB=black	)](#)


This is an online vote casting system using **TCP multithreaded server-client program**. The voters will log on from client systems and cast their votes. 

## Description
System should be secure and should only allow clients with authentic name and CNIC to cast the vote.

• A list of registered voters is available in a text file in the following format: **Name/CNIC number**

## Complete Workflow
The Server shall:

•	First of all take the **client’s name and CNIC** and match it with the content of the text file **(Voters_List.txt)**. 

•	If the details match, then it will **welcome the voter** and display the names and poll symbols of the candidates on the terminal.(Candidates_List.txt) 

•	The voter will then **cast the vote** by mentioning the poll symbol (not the name) of the candidate. All these details are to be recorded in an output text file. **This system should work perfectly for at least 5 different clients at the same time**. 

•	If there is problem of load shedding of electric light, then your system should not lose track of the votes being already casted once your server restarts again when light comes back on.

•	Assume that when the record of votes will be written by one thread in an output file, no other thread will make a read to the output file.

## Note
•	One client can cast a vote ONCE AND ONLY ONCE.

•	The Server should **allocate a new thread for every new incoming Client**. 

## How to Run
The client. and server.c files are provided. Just compile each file using the following command on Linux terminal or Windows Bash and run it (For client, obviously replace the server.c filename with client.c). Make sure the server is running before running any client.

``` gcc –pthread server.c -o server.out ```

----------

## Author
You can get in touch with me on my LinkedIn Profile: [![LinkedIn Link](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=linkedin&longCache=true&style=social&label=Connect
)](https://www.linkedin.com/in/harismuneer)

You can also follow my GitHub Profile to stay updated about my latest projects: [![GitHub Follow](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=Github&longCache=true&style=social&label=Follow)](https://github.com/harismuneer)

If you liked the repo then kindly support it by giving it a star ⭐!

## Contributions Welcome
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](#)

If you find any bug in the code or have any improvements in mind then feel free to generate a pull request.

## Issues
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Online-Voting-System-TCP.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Online-Voting-System-TCP/issues)

If you face any issue, you can create a new issue in the Issues Tab and I will be glad to help you out.

## License
[![MIT](https://img.shields.io/cocoapods/l/AFNetworking.svg?style=style&label=License&maxAge=2592000)](../master/LICENSE)

Copyright (c) 2018-present, harismuneer                                                        

