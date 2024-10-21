cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_atomics C)

add_bare_module(bare_atomics)

target_sources(
  ${bare_atomics}
  PRIVATE
    binding.c
)
