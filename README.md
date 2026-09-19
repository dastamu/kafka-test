# kafka-test
Testing Kafka brocker

# Dependences
```
@ EL
sudo dnf install librdkafka-devel
```

# Run
```
docker exec -it kafka-broker kafka-console-consumer --bootstrap-server localhost:9092 --topic test_topic --from-beginning

./build/consumer_app &

./build/producer_app
```

# License
MIT

# Author
dastamu
