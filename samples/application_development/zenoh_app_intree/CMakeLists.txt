# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zenoh_app_intree)

add_subdirectory(external)

target_sources(app PRIVATE ${CMAKE_SOURCE_DIR}/src/main.c)
