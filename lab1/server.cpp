#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <jsoncpp/json/json.h>
#include<bits/stdc++.h>
using namespace std;

struct KnockKnockJoke
{
    string knock;
    string whosThere;
    string ans;
    string ansWho;
    string punchline;
};

vector<KnockKnockJoke> jokes;

void loadTheJokes(string fileName){
    
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {

        cerr << "Error opening file." << endl;
        return ;
    }

    // Parse JSON data from the file
    Json::Value roots;
    inputFile >> roots;

    KnockKnockJoke joke;
    for (const auto& root : roots) {
        joke.knock = root["knock"].asString();
        joke.whosThere = root["whosthere"].asString();
        joke.ans = root["answer"].asString();
        joke.ansWho = root["answerwho"].asString();
        joke.punchline = root["punchline"].asString();

        jokes.push_back(joke);

    }
    inputFile.close();


    // for (const KnockKnockJoke& joke : jokes) {
    //     cout << joke.knock << endl;
    //     cout << joke.whosThere << endl;
    //     cout << joke.ans << endl;
    //     cout << joke.ansWho << endl;
    //     cout << joke.punchline << endl;
    // }

}


void handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));


    // Respond to the client
    const char* response = "Would you like to hear a joke?";
    if (write(clientSocket, response, strlen(response)) == -1) {
        cerr << "Error sending response to client." << endl;
    }

    // Read data from client
    string y_n;
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        cerr << "Error reading from client" << endl;
    } else { y_n = buffer; }
    
    while(true){
        
        KnockKnockJoke joke = jokes[rand()%18];

        if (!strcasecmp(y_n.c_str(), "y") ||  !strcasecmp(y_n.c_str(), "yes")){
            // cout << buffer << endl;
            
            //start joke - knock knock
            if (write(clientSocket, (joke.knock).c_str(), strlen((joke.knock).c_str())) == -1) {
                cerr << "Error sending response to client." << endl;
                break;
            } else {
                cout << "knock knock sent" << endl;
            }
            

            //get reply - Who's there?
            string data;
            char bufferData[1024];
            memset(bufferData, 0, sizeof(bufferData));
            int bytesRead = read(clientSocket, bufferData, sizeof(bufferData));
            if (bytesRead <= 0) {
                cerr << "Error reading from client" << endl;
                break;
            } else { data = bufferData; }

            if(strcasecmp(data.c_str(),joke.whosThere.c_str()) == 0){
                // cout << data << joke.whosThere  << " matched" << endl;
                // matched
            }else{
                cout << data << joke.whosThere  << " unmatched" << endl;
                string message = "You are supposed to say,\""+joke.whosThere+"\". Let’s try again.";
                if (write(clientSocket, message.c_str(), message.size()) == -1) {
                    cerr << "Error sending message to client." << endl;
                    break;
                } 
                // cout << "error in Who's there server";
                y_n = "y";
                this_thread::sleep_for (chrono::milliseconds(500));
                continue;
            }


            //Send joke ans - Answer
            if (write(clientSocket, (joke.ans).c_str(), joke.ans.size()) == -1) {
                cerr << "Error sending response to client." << endl;
            }
            // this_thread::sleep_for (chrono::milliseconds(200));



            //get reply - Answer who?
            memset(bufferData, 0, sizeof(bufferData));
            bytesRead = read(clientSocket, bufferData, sizeof(bufferData));
            if (bytesRead <= 0) {
                cerr << "Error reading from client" << endl;
                break;
            } else { data = bufferData; }

            cout << data << endl;
            if(strcasecmp(data.c_str(),joke.ansWho.c_str()) == 0){
                cout << data << joke.ansWho  << " matched" << endl;
                //matched
            }else{
                cout << data << joke.ansWho  << " matched" << endl;
                string message = "You are supposed to say,\""+joke.ansWho+"\". Let’s try again.";
                if (write(clientSocket, message.c_str(), message.size()) == -1) {
                    cerr << "Error sending message to client." << endl;
                    break;
                }
                y_n = "y";
                this_thread::sleep_for (chrono::milliseconds(500));
                continue;
            }

            
            //Deliver the punchline
            if (write(clientSocket, (joke.punchline).c_str(), strlen((joke.punchline).c_str())) == -1) {
                cerr << "Error sending response to client." << endl;
            }
            
            //ask for continuation
            // const char* response = "Would you like to hear another joke?";
            // if (write(clientSocket, response, strlen(response)) == -1) {
            //     cerr << "Error sending response to client." << endl;
            // }

            this_thread::sleep_for (chrono::milliseconds(500));

            string message = "Would you like to hear another joke?";
            if (write(clientSocket, message.c_str(), message.size()) == -1) {
                cerr << "Error sending message to client." << endl;
                break;
            }
            //expect yes or no for another joke
            memset(bufferData, 0, sizeof(bufferData));
            bytesRead = read(clientSocket, bufferData, sizeof(bufferData));
            if (bytesRead <= 0) {
                cerr << "Error reading from client" << endl;
                break;
            } else { data = bufferData; }
            y_n = data;


        } else if( !strcasecmp(y_n.c_str(), "n") || !strcasecmp(y_n.c_str(), "no")){
            cout << "client answered:" << y_n << endl;
            break;
        } else {
            const char* response = "Please enter a valid answer";
            if (write(clientSocket, response, strlen(response)) == -1) {
                cerr << "Error sending response to client." << endl;
            }

            // read again for another answer
            char bufferData[1024];
            string data;
            memset(buffer, 0, sizeof(buffer));
            bytesRead = read(clientSocket, bufferData, sizeof(bufferData));
            if (bytesRead <= 0) {
                cerr << "Error reading from client" << endl;
                break;
            } else { data = bufferData; }
            y_n = data;
        }     

    }

    cout << "Closing connection...." << endl;
    
    this_thread::sleep_for (chrono::milliseconds(800));

    // Close the client socket
    close(clientSocket);
}



int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;

    //load the jokes from jokes.txt
    loadTheJokes("./jokes.json");

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error creating socket." << endl;
        return -1;
    }


    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    // cout << serverAddr.sin_family << "  " << serverAddr.sin_port   << endl;

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error binding socket to address." << endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 2) == -1) {
        cerr << "Error listening for connections." << endl;
        close(serverSocket);
        return -1;
    }

    cout << "Server listening on port 8080..." << endl;

    vector<thread> threads;

    while (true) {
        socklen_t clientAddrSize = sizeof(clientAddr);
        // Accept incoming connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            cerr << "Error accepting connection." << endl;
            continue;
        }

        // Create a new thread to handle the client
        threads.emplace_back(handleClient, clientSocket);
    }

    // Close the server socket (not reachable in this example)
    close(serverSocket);
    return 0;
}





