project('kafka-cpp-example', 'cpp',
  version : '0.1',
  default_options : ['cpp_std=c++17'])

# 1. Znalezienie zależności librdkafka
# Meson automatycznie sprawdzi pkg-config lub cmake, aby namierzyć bibliotekę
rdkafka_dep = dependency('rdkafka++')
#rdkafka_dep = dependency('rdkafka')

# 2. Definicja pliku wykonywalnego dla Producenta
executable('producer_app',
           'src/producer.cpp',
           dependencies : rdkafka_dep)

# 3. Definicja pliku wykonywalnego dla Konsumenta
executable('consumer_app',
           'src/consumer.cpp',
           dependencies : rdkafka_dep)
