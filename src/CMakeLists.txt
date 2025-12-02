include(GenerateExportHeader)

add_library(
    menu_ui SHARED 
    menu/ui/window.cpp
    menu/ui/window.hpp
)

add_library(
    game SHARED
    game/game.cpp
    game/game.hpp
)

target_link_libraries(menu_ui 
    PUBLIC sfml::sfml
    game
)
target_link_libraries(game 
    PUBLIC sfml::sfml
)

target_include_directories(menu_ui PUBLIC 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} # Pour inclure le fichier généré menu_export.h   
)
target_include_directories(game PUBLIC 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} # Pour inclure le fichier généré menu_export.h
)

set_target_properties(menu_ui PROPERTIES DEFINE_SYMBOL MENU_WINDOW_EXPORTS)
generate_export_header(menu_ui
    BASE_NAME        MENU
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/menu_export.h
)

set_target_properties(game PROPERTIES DEFINE_SYMBOL GAME_WINDOW_EXPORTS)
generate_export_header(game
    BASE_NAME        GAME
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/game_export.h
)

add_executable(BaseProject main.cpp) 

target_link_libraries(BaseProject 
    PUBLIC sfml::sfml
    menu_ui
    game
# ou selon les besoins : sfml-system sfml-window sfml-graphics ...
)