#include <iostream>
#include <string>
#include <librdkafka/rdkafkacpp.h>

int main() {
    std::string brokers = "localhost:9092";
    //std::string brokers = "192.168.3.71:9092";
    std::string topic_name = "test_topic";
    std::string errstr;

    // 1. Konfiguracja
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", brokers, errstr);

    // 2. Tworzenie producenta
    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);

    // 3. Wysyłanie wiadomości
    std::string message = "Cześć z aplikacji w C++!";
    producer->produce(topic_name, RdKafka::Topic::PARTITION_UA,
                      RdKafka::Producer::RK_MSG_COPY,
                      const_cast<char *>(message.c_str()), message.size(),
                      NULL, 0, 0, NULL, NULL);

    std::cout << "Wysłano: " << message << std::endl;

    // Sprzątanie
    producer->flush(10000);
    delete producer;
    delete conf;
    return 0;
}
