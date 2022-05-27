cmake_minimum_required(VERSION 3.13)

project(mela_build_sim C)

add_compile_options(-pthread)
add_compile_options(-w)

include_directories(CMSIS_Sim)
include_directories(MeLaLib)
include_directories(simulation)

# Crée des variables avec les fichiers à compiler
file(GLOB CMSISSIM_SRC CONFIGURE_DEPENDS "CMSIS_Sim/*.h" "CMSIS_Sim/*.c")
file(GLOB MELA_SRC CONFIGURE_DEPENDS "MeLaLib/*.h" "MeLaLib/*.c")
file(GLOB SIM_SRC CONFIGURE_DEPENDS "simulation/*.h" "generated/simulation/*.c")

# On indique que l'on veut un exécutable compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(main ${SIM_SRC} ${MELA_SRC} ${CMSISSIM_SRC})



