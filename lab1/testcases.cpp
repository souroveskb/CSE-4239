#include <arpa/inet.h>
#include <sys/socket.h>
#include<bits/stdc++.h>
using namespace std;

struct testcase{
    string firstreply;
    string whosthere;
    string answerwho;
    string punchline;
};

testcase loadTestCases(int testnumber){
    testcase tests;
    if(testnumber ==0){
        tests.firstreply = "no";
    } else if (testnumber ==1){
        tests.firstreply = "yes";
        tests.whosthere = "Who?";
    } else if (testnumber ==2){
        tests.firstreply = "yes";
        tests.whosthere = "Who's there?";
        tests.answerwho = "ererere";
    }  return tests;
}


int main(int argc, char *argv[]) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    int val = rand() % 3;

    testcase test = loadTestCases(val);

    cout << "TESTING TEST NUMBER: " << val+1 << endl;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Error creating socket." << endl;
        return -1;
    }

    // cout << clientSocket << endl;

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // cout << serverAddr.sin_family << "  " << serverAddr.sin_port   << endl;


    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error connecting to server." << endl;
        close(clientSocket);
        return -1;
    }


    // Receive response from server
    // Getting - would you like to hear a joke?
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        cerr << "Error reading from server." << endl;
    } else {
        cout  << buffer << endl;
    }

    // Send data to server
    // replying yes or no  
    string y_n; 
    // cin >> y_n;
    y_n = test.firstreply;
    if(write(clientSocket, y_n.c_str(), y_n.size()) == -1) {
        cerr << "Error sending data to server." << endl;
        close(clientSocket);
        return -1;
    } 
    while (true){
        if (strcasecmp(y_n.c_str(), "n")==0 || strcasecmp(y_n.c_str(), "no")== 0){
            close(clientSocket);
            return 0;
        } else if (strcasecmp(y_n.c_str(), "y")==0 || strcasecmp(y_n.c_str(), "yes")== 0){
            break;
        } else {
            memset(buffer, 0, sizeof(buffer));
            bytesRead = read(clientSocket, buffer, sizeof(buffer));
            cout << buffer << endl;
            cin >> y_n; 
            if(write(clientSocket, y_n.c_str(), y_n.size()) == -1) {
                cerr << "Error sending data to server." << endl;
                close(clientSocket);
                return -1;
            } 

        }
    }

    
    int first_time = true;

    while(true){

        //server replies - Knock knock
        memset(buffer, 0, sizeof(buffer));
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        cout << buffer << endl;

        
        // send message - Who's there?
        string reply;
        reply = test.whosthere;
        if (write(clientSocket, reply.c_str(), reply.size()) == -1) {
            cerr << "Error sending data to server." << endl;
            close(clientSocket);
            return -1;
        }

        // Read data from client
        string try_again;
        
    
        //server replies - Answer
        memset(buffer, 0, sizeof(buffer));
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            // cerr << "Error reading from server answer" << endl;
            break;
        } 
        try_again = buffer;
        cout << try_again << endl;
        if(try_again.find("try again")!= string::npos){
            // cout << "Error try again" << endl;
            memset(buffer, 0, sizeof(buffer));
            continue;
        }
        
        
        // send message - Answer who?
        // getchar();
        // getline(cin,reply);
        reply = test.answerwho;
        // cout << reply << endl;
        if (write(clientSocket, reply.c_str(), strlen(reply.c_str())) == -1) {
            cerr << "Error sending data to server." << endl;
            close(clientSocket);
            return -1;
        }

        //server replies - Punchline
        memset(buffer, 0, sizeof(buffer));
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            cerr << "Error reading from server punchline" << endl;
        } else {
            try_again = buffer;
            cout << try_again << endl;
        }
        if(try_again.find("try again")){
            memset(buffer, 0, sizeof(buffer));
            continue;
        }
        

        // want to hear another joke
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        reply = buffer;
        cout << reply << endl;
        this_thread::sleep_for (chrono::milliseconds(500));

        getchar();
        getline(cin,reply);
        if (write(clientSocket, reply.c_str(), strlen(reply.c_str())) == -1) {
            cerr << "Error sending data to server." << endl;
            close(clientSocket);
            return -1;
        }
        cout << reply;
        if( strcasecmp(reply.c_str(), "n")==0 || strcasecmp(reply.c_str(), "no") ==0){
            cout << "client answered:" << reply << endl;
            break;
        }

    }

    // Close the client socket
    close(clientSocket);
    return 0;
}
