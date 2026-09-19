#include <iostream>
#include <librdkafka/rdkafkacpp.h>

int main() {
    // std::string brokers = "localhost:9092";
    std::string brokers = "192.168.3.71:9092";
    std::string topic_name = "test_topic";
    std::string errstr;

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
