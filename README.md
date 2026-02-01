# Multi-Client Chat Application (C++ | Sockets)

A terminal-based multi-client chat application implemented using **TCP sockets in C++**.  
The system follows a **client-server architecture** and supports **concurrent communication** using multithreading.

---

## Features
- TCP socket-based communication
- Multi-client support
- Server-side message broadcasting
- Thread-safe client handling using mutex
- Linux-based networking (POSIX sockets)

---

##  Technologies Used
- C++
- TCP/IP Sockets
- Multithreading (`std::thread`)
- Mutex (`std::mutex`)
- Linux system calls

---

##  Project Structure
chat-application/
├── server.cpp
├── client.cpp
└── README.md

---

## ⚙️ How to Run

### Compile
```bash
g++ server.cpp -o server -pthread
g++ client.cpp -o client

Run Server
./server

Run Clients (in separate terminals)
./client

📌 Learning Outcomes

Hands-on experience with socket programming
Understanding of client-server models
Practical use of multithreading and synchronization
Real-time communication handling

📈 Future Improvements

Username support
Message timestamps
Graceful client disconnect handling
GUI integration
