set(_build_data_dir ${CMAKE_CURRENT_BINARY_DIR}/../etc/share)

# Install qmake files
if(TRUE)
    set(_qmake_install_dir "${CMAKE_INSTALL_DATADIR}/QFluentWidgets/qmake")
    set(_qmake_build_dir ${_build_data_dir}/${_qmake_install_dir})
    file(RELATIVE_PATH _qmake_install_prefix
        "${CMAKE_INSTALL_PREFIX}/${_qmake_install_dir}"
        "${CMAKE_INSTALL_PREFIX}"
    )
    string(REGEX REPLACE "/$" "" _qmake_install_prefix "${_qmake_install_prefix}")

    set(QMAKE_QFUI_INSTALL_PREFIX "\$\$PWD/${_qmake_install_prefix}")
    set(QMAKE_QFUI_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
    set(QMAKE_QFUI_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
    set(QMAKE_QFUI_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR})

    set(QMAKE_QFUI_CORE_NAME_RELEASE QFUICore)

    set(QMAKE_QFUI_CORE_NAME_DEBUG QFUICore${CMAKE_DEBUG_POSTFIX})

    file(GLOB _qmake_components "${CMAKE_CURRENT_LIST_DIR}/qmake/*.pri.in")

    foreach(_item IN LISTS _qmake_components)
        get_filename_component(_name ${_item} NAME_WLE)
        configure_file(${_item} ${_build_data_dir}/qmake/${_name} @ONLY)
    endforeach()

    install(DIRECTORY ${_build_data_dir}/qmake/
        DESTINATION ${_qmake_install_dir}
    )
endif()

# Install msbuild files
if(MSVC)
    macro(to_dos_separator _var)
        string(REPLACE "/" "\\" ${_var} ${${_var}})
    endmacro()

    set(_msbuild_install_dir "${CMAKE_INSTALL_DATADIR}/QFluentWidgets/msbuild")
    set(_msbuild_build_dir ${_build_data_dir}/${_msbuild_install_dir})
    file(RELATIVE_PATH _msbuild_install_prefix
        "${CMAKE_INSTALL_PREFIX}/${_msbuild_install_dir}"
        "${CMAKE_INSTALL_PREFIX}"
    )
    string(REGEX REPLACE "/$" "" _msbuild_install_prefix "${_msbuild_install_prefix}")

    set(MSBUILD_QFUI_INSTALL_PREFIX "\$(MSBuildThisFileDirectory)${_msbuild_install_prefix}")
    set(MSBUILD_QFUI_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
    set(MSBUILD_QFUI_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
    set(MSBUILD_QFUI_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR})

    set(MSBUILD_QFUI_LIBRARY_LIST_DEBUG
        QFUICore${CMAKE_DEBUG_POSTFIX}.lib
    )

    set(MSBUILD_QFUI_LIBRARY_LIST_RELEASE
        QFUICore.lib
    )

    to_dos_separator(MSBUILD_QFUI_INSTALL_PREFIX)
    to_dos_separator(MSBUILD_QFUI_INSTALL_BINDIR)
    to_dos_separator(MSBUILD_QFUI_INSTALL_LIBDIR)
    to_dos_separator(MSBUILD_QFUI_INSTALL_INCDIR)

    configure_file(${CMAKE_CURRENT_LIST_DIR}/msbuild/QFluentWidgets.props.in
        ${_build_data_dir}/msbuild/QFluentWidgets.props
        @ONLY
    )

    install(DIRECTORY ${_build_data_dir}/msbuild/
        DESTINATION ${_msbuild_install_dir}
    )
endif()