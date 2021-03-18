# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zenoh_app_intree)

# add_subdirectory(external/zenoh-pico)

target_sources(app PRIVATE
  external/zenoh-pico/src/codec.c
  external/zenoh-pico/src/collection.c
  external/zenoh-pico/src/iobuf.c
  external/zenoh-pico/src/utils.c
  src/main.c)
target_include_directories(app PRIVATE external/zenoh-pico/include/)
