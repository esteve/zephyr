# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(external_lib)

target_sources(app PRIVATE src/main.c)

# The external static library that we are linking with does not know
# how to build for this platform so we export all the flags used in
# this zephyr build to the external build system.
#
# Other external build systems may be self-contained enough that they
# do not need any build information from zephyr. Or they may be
# incompatible with certain zephyr options and need them to be
# filtered out.
zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_definitions_for_lang_as_string(       C definitions)
zephyr_get_compile_options_for_lang_as_string(           C options)

set(external_project_cflags
  "${includes} ${definitions} ${options} ${system_includes}"
  )

include(ExternalProject)

# Add an external project to be able download and build the third
# party library. In this case downloading is not necessary as it has
# been committed to the repository.
# set(zenoh_pico_src_dir   ${CMAKE_CURRENT_SOURCE_DIR}/zenoh_pico)
# set(zenoh_pico_build_dir ${CMAKE_CURRENT_BINARY_DIR}/zenoh_pico)

set(zenoh_pico_build_dir ${CMAKE_CURRENT_BINARY_DIR}/zenoh_pico_install)

set(zenoh_pico_LIB_DIR     ${zenoh_pico_build_dir}/lib)
set(zenoh_pico_INCLUDE_DIR ${zenoh_pico_src_dir}/include)

# if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
# # https://www.gnu.org/software/make/manual/html_node/MAKE-Variable.html
# set(submake "$(MAKE)")
# else() # Obviously no MAKEFLAGS. Let's hope a "make" can be found somewhere.
# set(submake "make")
# endif()

ExternalProject_Add(
  zenoh_pico_project
  SOURCE_DIR "/home/esteve/Projects/adlink/zenoh-pico"
  # GIT_REPOSITORY https://github.com/esteve/zenoh-pico.git
  # GIT_TAG 9015569675a3f9fb872d7f40d5116e2d40508b9b
  # GIT_SHALLOW ON
  # TIMEOUT 60
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${zenoh_pico_build_dir}
    -DUNIX_TARGET=OFF
    -DZEPHYR_TARGET=ON
    -DEXAMPLES=OFF
    -DTESTS=OFF
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_AR=${CMAKE_AR}
    -DCMAKE_C_COMPILER_WORKS=1
    -DZENOH_ZEPHYR=1
    # -DCONFIG_PTHREAD_IPC=y
    # -DCONFIG_POSIX_API=y
    # -DCONFIG_NET_NATIVE_IPV4=y
    # -DCONFIG_NET_IPV4=y
    # -DCONFIG_NET_IF_UNICAST_IPV4_ADDR_COUNT=1
    # -DCONFIG_NET_IF_MCAST_IPV4_ADDR_COUNT=1
    # # -DCONFIG_ARM=1
    # -DCONFIG_SOC_SERIES_STM32F4X=y
    # -DCONFIG_SOC_STM32F407XG=y
    # -DCONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC=168000000
    # -DCONFIG_ARM_MPU=y
    # -DCONFIG_HW_STACK_PROTECTION=y
    # -DCONFIG_SERIAL=y
    # -DCONFIG_CONSOLE=y
    # -DCONFIG_UART_CONSOLE=y
    # -DCONFIG_PINMUX=y
    # -DCONFIG_GPIO=y
    # -DCONFIG_CLOCK_CONTROL=y
    # -DCONFIG_CLOCK_STM32_HSE_CLOCK=12000000
    # -DCONFIG_CLOCK_STM32_SYSCLK_SRC_PLL=y
    # -DCONFIG_CLOCK_STM32_PLL_SRC_HSE=y
    # -DCONFIG_CLOCK_STM32_PLL_M_DIVISOR=6
    # -DCONFIG_CLOCK_STM32_PLL_N_MULTIPLIER=168
    # -DCONFIG_CLOCK_STM32_PLL_P_DIVISOR=2
    # -DCONFIG_CLOCK_STM32_PLL_Q_DIVISOR=7
    # -DCONFIG_CLOCK_STM32_AHB_PRESCALER=1
    # -DCONFIG_CLOCK_STM32_APB1_PRESCALER=4
    # -DCONFIG_CLOCK_STM32_APB2_PRESCALER=2
    # BUILD_BYPRODUCTS ${zenoh_pico_LIB_DIR}/libzenoh_pico.a
)

# zenoh_pico_project                 # Name for custom target
#   PREFIX     ${zenoh_pico_build_dir} # Root dir for entire project
#   SOURCE_DIR ${zenoh_pico_src_dir}
#   BINARY_DIR ${zenoh_pico_src_dir} # This particular build system is invoked from the root
#   CONFIGURE_COMMAND ""    # Skip configuring the project, e.g. with autoconf
#   BUILD_COMMAND
#   ${submake}
#   PREFIX=${zenoh_pico_build_dir}
#   CC=${CMAKE_C_COMPILER}
#   AR=${CMAKE_AR}
#   CFLAGS=${external_project_cflags}
#   INSTALL_COMMAND ""      # This particular build system has no install command
#   BUILD_BYPRODUCTS ${zenoh_pico_LIB_DIR}/libzenoh_pico.a
#   )

# Create a wrapper CMake library that our app can link with
# add_library(zenoh_pico_lib STATIC IMPORTED GLOBAL)
# add_dependencies(
#   zenoh_pico_lib
#   zenoh_pico_project
#   )
# set_target_properties(zenoh_pico_lib PROPERTIES IMPORTED_LOCATION             ${zenoh_pico_LIB_DIR}/libzenoh_pico.a)
# set_target_properties(zenoh_pico_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${zenoh_pico_INCLUDE_DIR})

# target_link_libraries(app PUBLIC zenoh_pico_lib)

# add_library(zenoh_pico_lib STATIC IMPORTED GLOBAL)
add_dependencies(
  app
  zenoh_pico_project
  )
