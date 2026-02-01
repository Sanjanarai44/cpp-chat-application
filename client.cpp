#include <iostream>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

void receiveMessages(int sock) {
    char buffer[1024];
    while (true) {
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes > 0) {
            cout << "\nMessage: " << string(buffer, bytes) << endl;
        }
    }
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    thread t(receiveMessages, clientSocket);
    t.detach();

    string msg;
    while (true) {
        getline(cin, msg);
        send(clientSocket, msg.c_str(), msg.size(), 0);
    }

    close(clientSocket);
    return 0;
}
