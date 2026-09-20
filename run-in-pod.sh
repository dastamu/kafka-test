#!/bin/bash

# Tworzenie Poda i wystawienie portu 9092 na zewnątrz
podman pod create --name kafka-pod -p 9092:9092

# Uruchomienie kontenera wewnątrz tego Poda ze wszystkimi Twoimi zmiennymi
podman run -d --pod kafka-pod --name kafka-broker --replace \
  -e KAFKA_NODE_ID=1 \
  -e KAFKA_PROCESS_ROLES='broker,controller' \
  -e KAFKA_CONTROLLER_QUORUM_VOTERS='1@localhost:9093' \
  -e KAFKA_LISTENERS='PLAINTEXT://0.0.0.0:9092,CONTROLLER://0.0.0.0:9093' \
  -e KAFKA_INTER_BROKER_LISTENER_NAME='PLAINTEXT' \
  -e KAFKA_CONTROLLER_LISTENER_NAMES='CONTROLLER' \
  -e KAFKA_LISTENER_SECURITY_PROTOCOL_MAP='CONTROLLER:PLAINTEXT,PLAINTEXT:PLAINTEXT' \
  -e KAFKA_ADVERTISED_LISTENERS='PLAINTEXT://localhost:9092' \
  -e KAFKA_CLUSTER_ID='MkU3OEVBNTcwNTJDRDk1Qg' \
  -e KAFKA_OFFSETS_TOPIC_REPLICATION_FACTOR=1 \
  -e KAFKA_GROUP_INITIAL_REBALANCE_DELAY_MS=0 \
  -e KAFKA_HEAP_OPTS="-Xms512M -Xmx512M" \
  docker.io/confluentinc/cp-kafka:latest

