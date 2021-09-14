#!/usr/bin/env bash

find src/ tests/ include/ -iname *.h -o -iname *.c | xargs clang-format -i
