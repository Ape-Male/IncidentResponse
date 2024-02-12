#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "conio.h"
#include <random>
#include <cstdlib>
#include <ctime> 


//declarations



void createIncident();
void mainMenu();
void phishIncident();
void generateRandomID();



std::vector<std::string> splitComma(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string userName, passWord;
    std::cout << R"(

_________ _        _______ _________ ______   _______  _       _________   _______  _______  _______  _______  _______  _        _______  _______   _________ _______  _______  _       
\__   __/( (    /|(  ____ \\__   __/(  __  \ (  ____ \( (    /|\__   __/  (  ____ )(  ____ \(  ____ \(  ____ )(  ___  )( (    /|(  ____ \(  ____ \  \__   __/(  ___  )(  ___  )( \      
   ) (   |  \  ( || (    \/   ) (   | (  \  )| (    \/|  \  ( |   ) (     | (    )|| (    \/| (    \/| (    )|| (   ) ||  \  ( || (    \/| (    \/     ) (   | (   ) || (   ) || (      
   | |   |   \ | || |         | |   | |   ) || (__    |   \ | |   | |     | (____)|| (__    | (_____ | (____)|| |   | ||   \ | || (_____ | (__         | |   | |   | || |   | || |      
   | |   | (\ \) || |         | |   | |   | ||  __)   | (\ \) |   | |     |     __)|  __)   (_____  )|  _____)| |   | || (\ \) |(_____  )|  __)        | |   | |   | || |   | || |      
   | |   | | \   || |         | |   | |   ) || (      | | \   |   | |     | (\ (   | (            ) || (      | |   | || | \   |      ) || (           | |   | |   | || |   | || |      
___) (___| )  \  || (____/\___) (___| (__/  )| (____/\| )  \  |   | |     | ) \ \__| (____/\/\____) || )      | (___) || )  \  |/\____) || (____/\     | |   | (___) || (___) || (____/\
\_______/|/    )_)(_______/\_______/(______/ (_______/|/    )_)   )_(     |/   \__/(_______/\_______)|/       (_______)|/    )_)\_______)(_______/     )_(   (_______)(_______)(_______/
                                                                                                                                                                                        
)" << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "LOGIN:\n";
    std::cout << "Username: ";
    std::cin >> userName;
    std::cout << "\n";
    std::cout << "Password: ";
    passWord = ""; 

    char ch;
    while ((ch = _getch()) != '\r') {  //password obfuscation with conio
        if (ch == '\b') { 
            if (!passWord.empty()) {
                std::cout << "\b \b"; 
                passWord.pop_back(); 
            }
        }
        else {
            std::cout << '*'; 
            passWord += ch;
        }
    }

    std::cout << std::endl;

  
    std::ifstream file("Logins.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1;
    }

    bool loggedIn = false;
    std::string line;

    while (getline(file, line)) {

        std::vector<std::string> parts = splitComma(line, ',');
        if (parts.size() == 2) {
            std::string storedUsername = parts[0];
            std::string storedPassword = parts[1];

            if (userName == storedUsername && passWord == storedPassword) {
                loggedIn = true;
                break;
            }
        }
    }


    file.close();


    if (loggedIn) {
        std::cout << "You are logged in as: " + userName + "" << std::endl;
        mainMenu();
    }
    else {
        std::cout << "Incorrect username or password." << std::endl;
    }

    return 0;
}

void generateRandomID(int& randomNumber) {
    const int MIN = 100000000;  
    const int MAX = 999999999; 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    randomNumber = MIN + (std::rand() % (MAX - MIN + 1)); 
}
void mainMenu() {
    int mainMenuChoice;
    std::cout << "\n";
    std::cout << "Menu";
    std::cout << "\n";
    std::cout << "1)Create Incident";
    std::cout << "\n";
    std::cout << "2)Search Incidents";
    std::cout << "\n";
    std::cout << "3)Delete Incidents";
    std::cout << "\n";
    std::cin >> mainMenuChoice;

    switch (mainMenuChoice) {
    case 1:
        createIncident();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }

}


void createIncident() {
    int incidentCreationChoice;
    std::cout << "Please select what kind of incident you want to log:" << std::endl;
    std::cout << "1.) Phishing Incident" << std::endl;
    std::cout << "2.) Data Breach" << std::endl;
    std::cout << "3.) Malware Attack" << std::endl;
    std::cin >> incidentCreationChoice;

    switch (incidentCreationChoice) {
    case 1:
        std::cout << "You have selected: Phishing Incident " << std::endl;
        phishIncident();
        break;
    case 2:
        // Log data breach
        break;
    case 3:
        // Log malware attack
        break;
    case 4:
        // Log insider threat
        break;
    case 5:
        // Log DoS attack
        break;
    case 6:
        // Log ransomware attack
        break;
    case 7:
        // Log social engineering attack
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
    }
}

void phishIncident() {
    int randomID;
    generateRandomID(randomID);
    std::string senderEmail, subject, hasAttachmentsStr, attachmentSHA, senderIP, dateTime, recipient, recipientActions;
    char confirmSave;

    std::cout << "Enter Suspicious Sender's Email Address: ";
    std::cin >> senderEmail;

    std::cout << "Enter Subject of Email: ";
    std::cin.ignore();
    std::getline(std::cin, subject);

    std::cout << "Does the email include attachments? (Y/N): ";
    std::cin >> hasAttachmentsStr;
    while (hasAttachmentsStr != "Y" && hasAttachmentsStr != "N") {
        std::cout << "Invalid input. Please enter 'Y' or 'N': ";
        std::cin >> hasAttachmentsStr;
    }
    bool hasAttachments = (hasAttachmentsStr == "Y");

    if (hasAttachments) {
        std::cout << "Enter SHA Hash of Attachment(s) if applicable: ";
        std::cin >> attachmentSHA;
    }

    std::cout << "Enter Sender's IP Address: ";
    std::cin >> senderIP;

    std::cout << "Enter Date and Time of Incident: ";
    std::cin.ignore();
    std::getline(std::cin, dateTime);

    std::cout << "Enter Recipient: ";
    std::cin >> recipient;

    std::cout << "Enter Recipient's Actions after Receiving: ";
    std::cin.ignore();
    std::getline(std::cin, recipientActions);

    std::cout << "\n\n--- Incident Details ---\n";
    std::cout << "Sender's Email Address: " << senderEmail << std::endl;
    std::cout << "Subject of Email: " << subject << std::endl;
    std::cout << "Includes Attachments: " << (hasAttachments ? "Yes" : "No") << std::endl;
    if (hasAttachments) {
        std::cout << "Attachment SHA Hash: " << attachmentSHA << std::endl;
    }
    std::cout << "Sender's IP Address: " << senderIP << std::endl;
    std::cout << "Date and Time of Incident: " << dateTime << std::endl;
    std::cout << "Recipient: " << recipient << std::endl;
    std::cout << "Recipient's Actions: " << recipientActions << std::endl;

    std::cout << "\nDo you want to save this incident? (Y/N): ";
    std::cin >> confirmSave;
    if (confirmSave == 'Y' || 'y') {
        std::ofstream file("Database/Phish.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open CSV file!" << std::endl;
            return;
        }

      
        file << randomID << ",";
        file << senderEmail << ",";
        file << subject << ",";
        file << hasAttachmentsStr << ",";
        file << attachmentSHA << ",";
        file << senderIP << ",";
        file << dateTime << ",";
        file << recipient << ",";
        file << recipientActions << std::endl;
        file.close();

        std::cout << "Incident saved successfully." << std::endl;
        std::cout << "Incident ID: #" + randomID << std::endl;
    }
    else {
        std::cout << "Incident not saved." << std::endl;
    }
}
