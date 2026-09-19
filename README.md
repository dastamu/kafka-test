# kafka-test
Testing Kafka brocker

## Dependences
```sh
@ EL
sudo dnf install librdkafka-devel
```

## Building
```sh
meson setup build
meson compile -C build
```

## Runing
```sh
docker compose up -d
docker exec -it kafka-broker kafka-console-consumer --bootstrap-server localhost:9092 --topic test_topic --from-beginning

./build/consumer_app &

./build/producer_app
```

## License
MIT

## Author
dastamu
