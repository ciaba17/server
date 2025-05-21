#include <asio.hpp>
#include <iostream>

using namespace std;

int main() {
    try {
        asio::io_context io;

        // Creazione del server: indirizzo e porta
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 1235);
        asio::ip::tcp::acceptor acceptor(io, endpoint);

        cout << "Server in ascolto sulla porta 1235...\n\n";

        // Socket per accettare la connessione
        asio::ip::tcp::socket socket(io);
        acceptor.accept(socket); // blocca finché un client si connette
    
        cout << "Client connesso!\n";

        // Invia un messaggio al client
        string messaggio = "Ciao cai, sono il server!\n\n";
        asio::write(socket, asio::buffer(messaggio));

        // Riceve risposta
        char data[128];
        size_t length = socket.read_some(asio::buffer(data));
        cout << "Messaggio ricevuto: " << string(data, length) << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }
}