#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

vector<int> clients;
mutex mtx;

void handleClient(int clientSocket) {
    char buffer[1024];

    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;

        lock_guard<mutex> lock(mtx);
        for (int sock : clients) {
            if (sock != clientSocket) {
                send(sock, buffer, bytes, 0);
            }
        }
    }

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    cout << "Server running on port 8080\n";

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        {
            lock_guard<mutex> lock(mtx);
            clients.push_back(clientSocket);
        }

        thread t(handleClient, clientSocket);
        t.detach();
    }

    close(serverSocket);
    return 0;
}
