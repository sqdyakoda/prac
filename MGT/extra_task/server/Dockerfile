FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y g++ && \
    rm -rf /var/lib/apt/lists/*

# Устанавливаем nlohmann/json через apt (официальный пакет Ubuntu)
RUN apt-get update && \
    apt-get install -y nlohmann-json3-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY server.cpp .

RUN g++ -std=c++11 server.cpp -o server  

CMD ["./server"]