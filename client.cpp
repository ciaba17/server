#include <asio.hpp>
#include <iostream>

using namespace std;

int main() {
    try {
        asio::io_context io;

        // Creazione del socket e connessione al server
        asio::ip::tcp::resolver resolver(io);
        auto endpoints = resolver.resolve("127.0.0.1", "1235");
        asio::ip::tcp::socket socket(io);
        asio::connect(socket, endpoints);

        cout << "Connesso al server!\n\n";

        // Riceve il messaggio
        char data[128];
        size_t length = socket.read_some(asio::buffer(data));
        cout << "Messaggio dal server: " << string(data,length) << endl;

        // Invia la risposta
        string risposta;
        cout << "Inserisci risposta al server: ";
        cin >> risposta;
        asio::write(socket, asio::buffer(risposta));
    }
    catch (exception& e) {
        cerr << "Errore: " << e.what() << std::endl;
    }
}