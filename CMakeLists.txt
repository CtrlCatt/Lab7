cmake_minimum_required(VERSION 3.10)
project(dungeon_editor)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



# Добавляем единственный исходный файл
add_executable(dungeon_editor main.cpp)

# тесты
enable_testing()

add_executable(
  googltest
  googltest.cpp
  include/BattleSystem.h
  include/ConsoleLogger.h
  include/FileLogger.h
  include/Knight.h
  include/NPC.h
  include/NPCFactory.h
  include/Observer.h
  include/SlaveTrader.h
  include/Squirrel.h
)
target_link_libraries(
  googltest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(googltest)