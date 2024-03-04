# SPDX-FileCopyrightText: 2017 Citra Emulator Project
# SPDX-License-Identifier: GPL-2.0-or-later

add_executable(atlantis-room
    precompiled_headers.h
    atlantis_room.cpp
    atlantis_room.rc
)

target_link_libraries(atlantis-room PRIVATE common network)
if (ENABLE_WEB_SERVICE)
    target_compile_definitions(atlantis-room PRIVATE -DENABLE_WEB_SERVICE)
    target_link_libraries(atlantis-room PRIVATE web_service)
endif()

target_link_libraries(atlantis-room PRIVATE mbedtls mbedcrypto)
if (MSVC)
    target_link_libraries(atlantis-room PRIVATE getopt)
endif()
target_link_libraries(atlantis-room PRIVATE ${PLATFORM_LIBRARIES} Threads::Threads)

if(UNIX AND NOT APPLE)
    install(TARGETS atlantis-room)
endif()

if (atlantis_USE_PRECOMPILED_HEADERS)
    target_precompile_headers(atlantis-room PRIVATE precompiled_headers.h)
endif()

create_target_directory_groups(atlantis-room)
