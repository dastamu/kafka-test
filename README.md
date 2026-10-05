# kafka-test
Testing Kafka broker

## Dependences
```sh
# @ EL10
sudo dnf install meson ninja-build
sudo dnf install librdkafka-devel
sudo dnf install podman podman-compose

# @ MSYS2 UCRT64
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-meson mingw-w64-ucrt-x86_64-ccache mingw-w64-ucrt-x86_64-sccache
```

## Building
### Meason
```sh
meson setup build-meson --buildtype=release
meson compile -C build-meson
```
### CMake
```sh
mkdir build-cmake && cd build-cmake
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
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
[License](LICENSE) MIT

## Author
**dastamu** - [Profil GitHub](https://github.com/dastamu)
