cmake_minimum_required(VERSION 3.10)
project(SeaBattle)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем путь к заголовочным файлам
include_directories(include)
include_directories(Ability)  # Добавляем папку Ability

# Добавляем исходные файлы из папок
file(GLOB_RECURSE SOURCES
    "Ability/*.cpp"
    "exceptions/*.cpp"
    "factory/*.cpp"
    "gamelogic/*.cpp"
    "holders/*.cpp"
    "Players/*.cpp"
    "shipsAndMap/*.cpp"
    "main.cpp"
)

# Добавляем исполняемый файл
add_executable(SeaBattle ${SOURCES})

# Указываем путь к заголовочным файлам nlohmann_json
include_directories(/home/maxim/json/vcpkg/installed/x64-linux/include)

# Указываем путь к заголовочным файлам OpenSSL
include_directories(/usr/include)

# Линкуем библиотеки OpenSSL
target_link_libraries(SeaBattle PRIVATE ssl crypto)