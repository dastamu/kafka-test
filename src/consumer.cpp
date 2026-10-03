#include <iostream>
#include <librdkafka/rdkafkacpp.h>
#include <getopt.h>

int main(int argc, char* argv[]) {
    std::string brokers = "localhost:9092";
    //std::string brokers = "192.168.1.1:9092";
    std::string topic_name = "test_topic";
    std::string errstr;

    // Definicja struktur długich opcji
    // { nazwa_dluga, czy_wymaga_argumentu, flaga, wartosc_krotka }
    static struct option long_options[] = {
        {"broker",  required_argument, nullptr, 'b'},
        {"help",    no_argument,       nullptr, 'h'},
        {nullptr,   0,                 nullptr,  0 } // Koniec tablicy
    };

    int opt;
    int option_index = 0;

    // Pętla przetwarzająca argumenty
    // "b:h" oznacza: 'b' wymaga argumentu (dwukropek), 'h' nie wymaga argumentu
    while ((opt = getopt_long(argc, argv, "b:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'b':
                if (optarg) {
                    brokers = optarg; // optarg zawiera wartość przekazaną do opcji
                }
                break;
            case 'h':
                std::cout << "Użycie: " << argv[0] << " --broker <adres_ip:port> lub -b <adres_ip:port>\n";
                return 0;
            case '?':
                // getopt_long automatycznie wypisuje komunikat o błędzie w przypadku nieznanej opcji
                return 1;
            default:
                break;
        }
    }
    std::cout << "Adres IP i port brokera Kafta to: " << brokers << std::endl;

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", brokers, errstr);
    conf->set("group.id", "grupa_testowa", errstr); // Identyfikator grupy konsumentów

    RdKafka::KafkaConsumer *consumer = RdKafka::KafkaConsumer::create(conf, errstr);

    // Subskrypcja tematu
    std::vector<std::string> topics = {topic_name};
    consumer->subscribe(topics);

    std::cout << "Oczekiwanie na wiadomości..." << std::endl;

    while (true) {
        RdKafka::Message *msg = consumer->consume(1000); // timeout 1s
        if (msg->err() == RdKafka::ERR_NO_ERROR) {
            std::cout << "Odebrano: " << static_cast<const char *>(msg->payload()) << std::endl;
        }
        delete msg;
    }

    consumer->close();
    delete consumer;
    return 0;
}
