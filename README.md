# kafka-test
Testing Kafka broker

## Dependences
```sh
@ EL
sudo dnf install meson ninja-build
sudo dnf install librdkafka-devel
sudo dnf install podman podman-compose
```

## Building
```sh
meson setup build
meson compile -C build
```

## Runing
### Method 1
```sh
docker compose up -d
docker exec -it kafka-broker kafka-console-consumer --bootstrap-server localhost:9092 --topic test_topic --from-beginning # diagnostic

./build/consumer_app &
./build/producer_app
./build/producer_app
./build/producer_app

# Stop & remove
docker stop kafka-broker
docker rmi kafka-broker
```
### Method 2
```sh
podman-compose up -d
podman exec -it kafka-broker kafka-console-consumer --bootstrap-server localhost:9092 --topic test_topic --from-beginning # diagnostic

./build/consumer_app &
./build/producer_app
./build/producer_app
./build/producer_app

# Stop & remove
podman stop kafka-broker
podman rmi kafka-broker
```
### Method 3
```sh 
./run-in-pod.sh
./build/consumer_app &
./build/producer_app
./build/producer_app
./build/producer_app

# Stop & remove
podman pod stop kafka-pod
podman pod rm -f kafka-pod
```
## License
MIT

## Author
dastamu
