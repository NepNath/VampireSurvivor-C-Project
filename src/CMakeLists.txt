add_executable(BaseProject main.cpp "game/game.cpp" "game/game.h") #nom à changer

target_link_libraries(BaseProject PUBLIC sfml::sfml
# ou selon les besoins : sfml-system sfml-window sfml-graphics ...
)
