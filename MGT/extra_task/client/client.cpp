#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <vector>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

const int PORT = 8080;
const char* SERVER_NAME = "server"; // Используем имя сервиса

// функция корректного считывания содержимого файла в строку
std::string readFileInDocker(const std::string& filePath) {
    // Абсолютный путь к файлу внутри контейнера
    std::string dockerPath = "/app/data/" + filePath;

    std::ifstream file(dockerPath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file at " << dockerPath << std::endl;
        std::cerr << "Current directory: ";
        system("pwd");
        throw std::runtime_error("File open failed");
    }
    std::string content((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>());
    return content;
}

// функция разделения строки на подстроки по символу '\n'
void split(std::vector<std::string>& vec, const std::string& str) {
    int begin = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            vec.push_back(str.substr(begin, i - begin));
            begin = i + 1;
        }
    }
    vec.push_back(str.substr(begin, str.length()));
}

int main() {

    // Создание сокета
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return 1;
    }
    
    // Получаем информацию о сервере по имени
    struct hostent* server = gethostbyname(SERVER_NAME);
    if (server == NULL) {
        std::cerr << "Error: Could not resolve hostname" << std::endl;
        return 1;
    }
    
    // Настраиваем структуру адреса
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // подключаемся к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return 1;
    }
    
    std::cout << "Connected to server\n";

    // читаем в temp файл list.txt, в котором находятся названия файлов с входными данными
    std::string temp;
    try {
        temp = readFileInDocker("list.txt");                
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::vector<std::string> input_files;
    split(input_files, temp);
    // теперь в input_files находятся имена файлов с входными данными

    // отправляем серверу количество наборов входных данных
    size_t file_count = input_files.size();
    std::cout << "there are " << file_count << " sets of input data\n";
    if (send(sock, &file_count, sizeof(file_count), 0) < 0) {
        std::cerr << "send() Failed" << std::endl;
        return 1;
    }

    for (int i = 0; i < file_count; ++i) {

        // читаем очередной файл
        std::string json_str;
        try {
            json_str = readFileInDocker(input_files[i]);                
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }

        // отправляем размер входных данных
        size_t json_size = json_str.size();
        if (send(sock, &json_size, sizeof(json_size), 0) < 0) {
            std::cerr << "send() Failed" << std::endl;
            return 1;
        }
        
        // Отправка входных данных данных
        if (send(sock, json_str.c_str(), json_str.size(), 0) < 0) {
            std::cerr << "send() Failed" << std::endl;
            return -1;
        }
        std::cout << "input data from file \"" << input_files[i] << "\" sent\n";

        // Получение размера данных, уже обработанных сервером
        if (recv(sock, &json_size, sizeof(json_size), 0) < 0) {
            std::cerr << "recv() Failed" << std::endl;
            return 1;
        }

        // Получение данных
        char* buffer = new char[json_size + 3];
        if (recv(sock, buffer, json_size, 0) < 0) {
            std::cerr << "recv() Failed" << std::endl;
            return 1;
        }
        buffer[json_size] = '\0';

        // Вывод данных в консоль
        if (buffer[0] != '{')
            std::cout << "JSON parse ERROR: ";
        else
            std::cout << "processed data received:\n";
        std::cout << buffer << "\n";

        delete[] buffer;
    }

    std::cout << "the client is finished\n";
    

    close(sock);
    return 0;
}