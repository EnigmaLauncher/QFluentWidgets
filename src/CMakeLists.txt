qm_import(Preprocess)

set(QFLUENTWIDGETS_PROJECT_DESCRIPTION "Cross-platform Fluent UI framework")
set(QFLUENTWIDGETS_PROJECT_COPYRIGHT "Copyright 2024 sepera_okeq")
set(QFLUENTWIDGETS_GENERATED_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../include)
set(QFLUENTWIDGETS_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/etc/include)

set(QFLUENTWIDGETS_ENABLED_TARGETS)
set(QFLUENTWIDGETS_ENABLED_SUBDIRECTORIES)

# ----------------------------------
# Configurations
# ----------------------------------
set(QMSETUP_DEFINITION_SCOPE DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(QMSETUP_DEFINITION_NUMERICAL on)

qm_generate_config(${QFLUENTWIDGETS_BUILD_INCLUDE_DIR}/QFUICore/qfuiconfig.h)

if(QFLUENTWIDGETS_INSTALL)
    install(FILES ${QFLUENTWIDGETS_BUILD_INCLUDE_DIR}/QFUICore/qfuiconfig.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${QFLUENTWIDGETS_INSTALL_NAME}/QFUICore
    )
endif()
# ----------------------------------
# CMake API
# ----------------------------------
macro(qfui_add_library _target)
    set(options AUTOGEN NO_SYNC_INCLUDE NO_WIN_RC)
    set(oneValueArgs SYNC_INCLUDE_PREFIX PREFIX)
    set(multiValueArgs SYNC_INCLUDE_OPTIONS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(FUNC_AUTOGEN)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTORCC ON)
    endif()

    if(QFLUENTWIDGETS_BUILD_STATIC)
        set(_type STATIC)
    else()
        set(_type SHARED)
    endif()

    add_library(${_target} ${_type})

    if(WIN32 AND NOT FUNC_NO_WIN_RC AND(${_type} STREQUAL "SHARED"))
        qm_add_win_rc(${_target}
            NAME ${QFLUENTWIDGETS_INSTALL_NAME}
            DESCRIPTION ${QFLUENTWIDGETS_PROJECT_DESCRIPTION}
            COPYRIGHT ${QFLUENTWIDGETS_PROJECT_COPYRIGHT}
        )
    endif()

    if(FUNC_PREFIX)
        set(_prefix_option PREFIX ${FUNC_PREFIX})
    else()
        set(_prefix_option)
    endif()

    # Set global definitions
    qm_export_defines(${_target} ${_prefix_option})

    # Configure target
    qm_configure_target(${_target} ${FUNC_UNPARSED_ARGUMENTS})

    # Add include directories
    target_include_directories(${_target} PRIVATE ${QFLUENTWIDGETS_BUILD_INCLUDE_DIR})
    target_include_directories(${_target} PRIVATE .)

    # Library name
    if(${_target} MATCHES "^QFUI(.+)")
        set(_name ${CMAKE_MATCH_1})
        set_target_properties(${_target} PROPERTIES EXPORT_NAME ${_name})
    else()
        set(_name ${_target})
    endif()

    add_library(${QFLUENTWIDGETS_INSTALL_NAME}::${_name} ALIAS ${_target})

    if(FUNC_SYNC_INCLUDE_PREFIX)
        set(_inc_name ${FUNC_SYNC_INCLUDE_PREFIX})
    else()
        set(_inc_name ${_target})
    endif()

    set(_install_options)

    if(QFLUENTWIDGETS_INSTALL)
        install(TARGETS ${_target}
            EXPORT ${QFLUENTWIDGETS_INSTALL_NAME}Targets
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
        )

        target_include_directories(${_target} PUBLIC
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${QFLUENTWIDGETS_INSTALL_NAME}>"
        )

        set(_install_options
            INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/${QFLUENTWIDGETS_INSTALL_NAME}/${_inc_name}"
        )
    endif()

    if(NOT FUNC_NO_SYNC_INCLUDE)
        # Generate a standard include directory in build directory
        qm_sync_include(. "${QFLUENTWIDGETS_GENERATED_INCLUDE_DIR}/${_inc_name}" ${_install_options}
            ${FUNC_SYNC_INCLUDE_OPTIONS} FORCE
        )
        target_include_directories(${_target} PUBLIC
            "$<BUILD_INTERFACE:${QFLUENTWIDGETS_GENERATED_INCLUDE_DIR}>"
        )
    endif()
endmacro()

# ----------------------------------
# Main Project
# ----------------------------------

add_subdirectory(core)

# ----------------------------------
# Documentation
# ----------------------------------
if(QFLUENTWIDGETS_BUILD_DOCUMENTATIONS)
    if(NOT DOXYGEN_EXECUTABLE)
        find_package(Doxygen REQUIRED)
    endif()

    set(_install_options)

    if(QFLUENTWIDGETS_INSTALL)
        set(_install_options INSTALL_DIR share/doc/${QFLUENTWIDGETS_INSTALL_NAME})
    endif()

    set(_doc_targets ${QFLUENTWIDGETS_ENABLED_TARGETS})

    set(QFLUENTWIDGETS_DOXYGEN_TAGFILE
        ${CMAKE_BUILD_SHARE_DIR}/doc/${QFLUENTWIDGETS_INSTALL_NAME}/${QFLUENTWIDGETS_INSTALL_NAME}_tagfile.xml
        CACHE FILEPATH "QFluentWidgets doxygen tag file path" FORCE
    )

    qm_import(Doxygen)
    qm_setup_doxygen(QFLUENTWIDGETS_RunDoxygen
        NAME "QFluentWidgets"
        DESCRIPTION "${QFLUENTWIDGETS_PROJECT_DESCRIPTION}"
        MDFILE ../README.md
        OUTPUT_DIR ${CMAKE_BUILD_SHARE_DIR}/doc/${QFLUENTWIDGETS_INSTALL_NAME}
        INPUT ${QFLUENTWIDGETS_ENABLED_SUBDIRECTORIES}
        TARGETS ${_doc_targets}
        DEPENDS ${_doc_targets}
        NO_EXPAND_MACROS Q_OBJECT Q_GADGET Q_DECLARE_TR_FUNCTIONS
        COMPILE_DEFINITIONS Q_SIGNALS=Q_SIGNALS Q_SLOTS=Q_SLOTS
        GENERATE_TAGFILE "${QFLUENTWIDGETS_DOXYGEN_TAGFILE}"
        ${_install_options}
    )
endif()

# ----------------------------------
# Install
# ----------------------------------
if(QFLUENTWIDGETS_INSTALL)
    # Add install target
    set(_install_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${QFLUENTWIDGETS_INSTALL_NAME})

    # Add version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${QFLUENTWIDGETS_INSTALL_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Add configuration file
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/${QFLUENTWIDGETS_INSTALL_NAME}Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${QFLUENTWIDGETS_INSTALL_NAME}Config.cmake"
        INSTALL_DESTINATION ${_install_dir}
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    # Install cmake files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${QFLUENTWIDGETS_INSTALL_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${QFLUENTWIDGETS_INSTALL_NAME}ConfigVersion.cmake"
        DESTINATION ${_install_dir}
    )

    # Install cmake targets files
    install(EXPORT ${QFLUENTWIDGETS_INSTALL_NAME}Targets
        FILE "${QFLUENTWIDGETS_INSTALL_NAME}Targets.cmake"
        NAMESPACE ${QFLUENTWIDGETS_INSTALL_NAME}::
        DESTINATION ${_install_dir}
    )

    # Install shared files
    include("../share/install.cmake")
endif()
