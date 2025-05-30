#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

const int PORT = 8080;

// класс Connection описывает ребро
struct Connection {
    // имя выходящей вершины
    std::string from;
    // имя входящей вершины
    std::string to;
    // расстояние между вершинами
    double distance;
    Connection(std::string f, std::string t, double r) : from(f), to(t), distance(r) {}
};

class NetworkData {
private:
    // u_map, в котором хранятся вершины вида: <имя, координата х, координата у>
    std::unordered_map<std::string, std::pair<double, double>> towers;
    // вектор connections, в котором хранятся все ребра
    std::vector<Connection> connections;
    // вектор result, в котором хранятся ребра Минимального Остовного Дерева
    std::vector<Connection> result;
    // u_map хранит вершину и его родителя
    std::unordered_map<std::string, std::string> parent;
    // строка error_descr хранит ошибки некорректных входных данных
    std::string error_descr;

public:
    // обработка входных данных
    void input(const json& j);
    // функция find_root находит корень дерева (компоненты связности)
    std::string find_root(const std::string& u);
    //функция unite объединяет компоненты связности
    void unite(std::string& u1, const std::string& u2);
    // алгоритм Краскаля (Крускаля)
    void kruscal();
    // функция возвращает готовые выходные данные для клиента
    std::string output();
};

void NetworkData::input(const json& j) {
    // проверяем наличие основного поля "towers"
    if (!j.contains("towers")) {
        error_descr = "'towers' is missed";
        return;
    }
    //проверяем, что towers - это массив
    if (!j["towers"].is_array()) {
        error_descr = "'towers' is not an array. [] expected";
        return;
    }
    for (const auto& tower_json : j["towers"]) {
        // проверяем наличие поля "id"
        if (!tower_json.contains("id")) {
            error_descr = "Tower missing 'id'";
            return;
        }
        // проверяем, что id - это строка
        if (!tower_json["id"].is_string()) {
            error_descr = "'id' is not a string. String type expected";
            return;
        }
        // проверяем наличие поля "coordinates"
        if (!tower_json.contains("coordinates")) {
            error_descr = "tower missing 'coordinates'";
            return;
        }
        // проверяем, что coordinates - это объект
        if (!tower_json["coordinates"].is_object()) {
            error_descr = "'coordinates' is not an object. {} expected";
            return;
        }
        std::string tower_name = tower_json["id"].get<std::string>();
        
        // проверяем наличие поля "x"
        if (!tower_json["coordinates"].contains("x")) {
            error_descr = "coordinates missing 'x'";
            return;
        }
        // проверяем наличие поля "y"
        if (!tower_json["coordinates"].contains("y")) {
            error_descr = "coordinates missing 'y'";
            return;
        }
        // проверяем, что координаты х и у являются числами
        if (!tower_json["coordinates"]["x"].is_number() || !tower_json["coordinates"]["y"].is_number()) {
            error_descr = "Coordinates must be numbers";
            return;
        }
        
        double x = tower_json["coordinates"]["x"].get<double>();
        double y = tower_json["coordinates"]["y"].get<double>();
        // добавляем вершину в вектор towers
        towers.emplace(tower_name, std::make_pair(x, y));
    }
    // проверяем наличие основного поля connections
    if (!j.contains("connections")) {
        error_descr = "'connections' is missed";
        return;
    }
    // проверяем, что connections - Это массив
    if (!j["connections"].is_array()) {
        error_descr = "'connections' is not an array. [] expected";
        return;
    }
    for (const auto& conn_json : j["connections"]) {
        // проверяем наличие поля "from"
        if (!conn_json.contains("from")) {
            error_descr = "Tower missing 'from'";
            return;
        }
        // проверяем, что from - это строка
        if (!conn_json["from"].is_string()) {
            error_descr = "'from' is not a string";
            return;
        }
        // проверяем наличие поля "to"
        if (!conn_json.contains("to")) {
            error_descr = "Tower missing 'to'";
            return;
        }
        // проверяем, что to - это строка
        if (!conn_json["to"].is_string()) {
            error_descr = "'to' is not a string";
            return;
        }
        std::string from = conn_json["from"].get<std::string>();
        std::string to = conn_json["to"].get<std::string>();
        // проверяем существование вершины from
        if (towers.find(from) == towers.end()) {
            error_descr = "tower '" + from + "' not found";
            return;
        }
        // проверяем существование вершины to
        if (towers.find(to) == towers.end()) {
            error_descr = "tower '" + to + "' not found";
            return;
        }
        // считаем расстояние между вершинами
        double dist = std::hypot(towers[to].first - towers[from].first, towers[to].second - towers[from].second);
        //добавляем ребро в вектор connections
        connections.push_back(Connection(from, to, dist));
    }
}
std::string NetworkData::find_root(const std::string& u) {
    if (u == parent[u])
        return u;
    else
        return find_root(parent[u]);
}
void NetworkData::unite(std::string& u1, const std::string& u2) {
    parent[u1] = parent[u2];
}
void NetworkData::kruscal() {
    if (error_descr.size() != 0)
        return;
    // сортируем ребра по возрастанию
    sort(connections.begin(), connections.end(), [](const Connection& a, const Connection& b) {
        return a.distance < b.distance;
    });
    std::string from, to;
    // изначально каждая вершина является отдельной компонентой связности
    for (const auto& tow : towers)
        parent.emplace(tow.first, tow.first);
    // добавляем по порядку ребра так, чтобы не образовался цикл
    for (const auto& conn : connections) {
        from = find_root(conn.from);
        to = find_root(conn.to);
        if (from != to) {
            result.push_back(conn);
            unite(from, to);
        }
    }
}
std::string NetworkData::output() {
        // если есть ошибки в корректности входных данных, то их и возвращаем
        if (error_descr.length() != 0)
            return error_descr;

        json res;
        double total_cost = 0;

        // создаём JSON-массив и заполняем его данными, обработанными алгоритмом Краскаля
        json mst_array = json::array(); 
        // добавляем ребра в массив
        for (const auto& connection : result) {
            json edge;
            edge["from"] = connection.from;
            edge["to"] = connection.to;
            total_cost += connection.distance;
            mst_array.push_back(edge);
        }
        // Заполняем итоговый JSON и возвращем его в формате std::string
        res["minimum_spanning_tree"] = mst_array;
        res["total_cost"] = total_cost;
        return res.dump(4);
    }
int main() {

    // создаем сокет
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // настраиваем адрес сервера
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // связываем адрес и сокет
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // переводим сокет в режим прослушивания (в очереди максимум одно соединение)
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int new_socket, addrlen = sizeof(address);
    // принимаем соединение с клиентом
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // получаем количество наборов входных данных
    size_t file_count;
    recv(new_socket, &file_count, sizeof(file_count), 0);

    // обрабатываем каждый набор входных данных
    for (int i = 0; i < file_count; ++i) {

        // получаем размер входных данных
        size_t json_size;
        if (recv(new_socket, &json_size, sizeof(json_size), 0) < 0) {
            std::cerr << "recv() Failed" << std::endl;
            return -1;
        }

        // получаем входные данные
        char* json_buffer = new char[json_size + 3];
        if (recv(new_socket, json_buffer, json_size, 0) < 0) {
            std::cerr << "recv() Failed" << std::endl;
            return -1;
        }
        json_buffer[json_size] = '\0';

        // в переменной str_result_data будут храниться данные для отправки клиенту
        std::string str_result_data;

        // преобразуем данные в json, сохраняем в json_data
        json json_data;
        try {
            json_data = json::parse(json_buffer);
            delete[] json_buffer;
        } catch (const json::parse_error& e) {
            // если возникли ошибки с синтаксисом во входных данных, то сохраняем их в str_result_data
            str_result_data = e.what();
        }

        // если ошибок нет, то начинаем обработку данных
        if (str_result_data.empty()) {
            NetworkData network;
            network.input(json_data);  // обрабатываем входные данные
            network.kruscal();  // запускаем алгоритм Краскаля
            str_result_data = network.output(); // сохраняем выходные данные в str_result_data
        }

        // отправляем размер выходных данных
        size_t data_size = str_result_data.size();
        if (send(new_socket, &data_size, sizeof(data_size), 0) < 0) {
            std::cerr << "send() / Failed" << std::endl;
            return -1;
        }

        // отправляем выходные данные
        if (send(new_socket, str_result_data.c_str(), str_result_data.size(), 0) < 0) {
            std::cerr << "send() // Failed" << std::endl;
            return -1;
        }
    }

    // закрываем соединение с клиентом
    close(new_socket);

    // закрываем серверный сокет
    close(server_fd);
    return 0;
}