cmake_minimum_required(VERSION 3.14)
project(ASpaceGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML COMPONENTS graphics REQUIRED)
find_package(SFML COMPONENTS window REQUIRED)
find_package(SFML COMPONENTS audio REQUIRED)

add_subdirectory(test)
set(SOURCE_FILES Game.cpp Game.h ResourceManager.cpp ResourceManager.h Spaceship.cpp Spaceship.h Player.cpp Player.h Raptor.cpp Raptor.h Bomber.cpp Bomber.h Enemy.cpp Enemy.h Kamikaze.cpp Kamikaze.h Fighter.cpp Fighter.h Assaulter.cpp Assaulter.h Boss.cpp Boss.h Cannon.cpp Cannon.h Asteroid.cpp Asteroid.h Background.cpp Background.h PowerUp.cpp PowerUp.h FireRate.cpp FireRate.h FullHealth.cpp FullHealth.h Speed.cpp Speed.h Strength.cpp Strength.h AuxiliaryCannon.cpp AuxiliaryCannon.h LaserCannon.cpp LaserCannon.h EnhanceSpecial.cpp EnhanceSpecial.h Projectile.cpp Projectile.h Minion.cpp Minion.h Functions.cpp Functions.h Animator.cpp Animator.h EntityManager.cpp EntityManager.h Subject.h Observer.h Achievement.cpp Achievement.h EnemyFactory.cpp EnemyFactory.h)
add_executable(ASpaceGame main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-graphics sfml-window sfml-audio)
target_link_libraries(ASpaceGame core)