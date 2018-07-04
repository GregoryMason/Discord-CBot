cmake_minimum_required(VERSION 3.5)
project(DiscordBot C)

set(CMAKE_C_STANDARD 11)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(DiscordBot main.c restAction.c restAction.h discordAPI.c discordAPI.h cJSON.c cJSON.h)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(DiscordBot ${CURL_LIBRARIES})