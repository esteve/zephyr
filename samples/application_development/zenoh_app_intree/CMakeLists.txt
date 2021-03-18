# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zenoh_app_intree)

# add_subdirectory(external/zenoh-pico)

target_sources(app PRIVATE
  external/zenoh-pico/src/codec.c
  external/zenoh-pico/src/collection.c
  external/zenoh-pico/src/iobuf.c
  # external/zenoh-pico/src/net/codec.c
  # external/zenoh-pico/src/net/internal.c
  # external/zenoh-pico/src/net/lease_task.c
  # external/zenoh-pico/src/net/msgcodec.c
  # external/zenoh-pico/src/net/property.c
  # external/zenoh-pico/src/net/read_task.c
  # external/zenoh-pico/src/net/rname.c
  # external/zenoh-pico/src/net/session.c
  # external/zenoh-pico/src/net/zephyr/network.c
  # external/zenoh-pico/src/net/zephyr/system.c
  # external/zenoh-pico/src/utils.c
  # src/rand.c
  src/strdup.c
  # src/strtof.c
  # src/strtok.c
  src/main.c)
target_include_directories(app PRIVATE external/zenoh-pico/include/)
target_compile_definitions(app PRIVATE -DZENOH_ZEPHYR=1)
