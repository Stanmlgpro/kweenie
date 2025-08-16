cmake_minimum_required(VERSION 3.20)
project(project)


# Stel het pad naar SFML in
set(SFML_DIR "C:\\Users\\stan1\\CLionProjects\\sfml\\2.6.2\\lib\\cmake\\SFML")


find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
    main.cpp
    Game.h
        Game.cpp
        GameRenderer.h
        GameRenderer.cpp
        GUI.h
        GUI.cpp
        RenderState.h
        uiButton.h
        uiButton.cpp
        Entity.h
        Entity.cpp
        Player.h
        Player.cpp
        Projectile.h
        Projectile.cpp
        Enemy.h
        Enemy.cpp
        Ally.h
        Ally.cpp
        Wave.h
        Wave.cpp
)
add_executable(project ${SOURCE_FILES})
target_link_libraries(project sfml-graphics sfml-window sfml-system)