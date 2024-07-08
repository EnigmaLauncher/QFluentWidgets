project(QFUICore
    VERSION ${QFLUENTWIDGETS_VERSION}
    LANGUAGES CXX
)

set(_src
    Common/Config.h
    Common/Icon.h
    Common/SmoothScroll.h
    Common/Theme.h
    Common/enum.h
    DateTime/DatePicker.h
    DateTime/PickerBase.h
    DateTime/TimePicker.h
    DialogBox/ColorDialog.h
    DialogBox/Dialog.h
    DialogBox/FolderListDialog.h
    DialogBox/HuePanel.h
    DialogBox/MaskDialogBase.h
    DialogBox/MessageDialog.h
    Layout/ExpandLayout.h
    Layout/FlowLayout.h
    Layout/VBoxLayout.h
    Navigation/NavigationInterface.h
    Navigation/NavigationPanel.h
    Navigation/NavigationWidget.h
    QFluentWidgets.h
    Common/AutoWrap.h
    Common/ImageUtils.h
    Common/StyleSheet.h
    Settings/CustomColorSettingCard.h
    Settings/ExpandGroupSettingCard.h
    Settings/FolderListSettingCard.h
    Settings/OptionsSettingCard.h
    Settings/SettingCard.h
    Settings/SettingCardGroup.h
    Widgets/AcrylicLabel.h
    Widgets/Button.h
    Widgets/CheckBox.h
    Widgets/ComboBox.h
    Widgets/CycleListWidget.h
    Widgets/IconWidget.h
    Widgets/InfoBar.h
    Widgets/Label.h
    Widgets/LineEdit.h
    Widgets/Menu.h
    Widgets/MultiSelectComboBox.h
    Widgets/ScrollArea.h
    Widgets/Slider.h
    Widgets/SpinBox.h
    Widgets/StackedWidget.h
    Widgets/StateToolTip.h
    Widgets/SwitchButton.h
    Widgets/ThreeStateButton.h
    Widgets/ToolTip.h
    Widgets/TreeView.h
    Common/Config.cpp
    Common/Icon.cpp
    Common/SmoothScroll.cpp
    DateTime/DatePicker.cpp
    DateTime/PickerBase.cpp
    DateTime/TimePicker.cpp
    DialogBox/ColorDialog.cpp
    DialogBox/Dialog.cpp
    DialogBox/FolderListDialog.cpp
    DialogBox/HuePanel.cpp
    DialogBox/MaskDialogBase.cpp
    DialogBox/MessageDialog.cpp
    Layout/ExpandLayout.cpp
    Layout/FlowLayout.cpp
    Layout/VBoxLayout.cpp
    Navigation/NavigationInterface.cpp
    Navigation/NavigationPanel.cpp
    Navigation/NavigationWidget.cpp
    QFluentWidgets.cpp
    Common/AutoWrap.cpp
    Common/ImageUtils.cpp
    Common/StyleSheet.cpp
    Settings/CustomColorSettingCard.cpp
    Settings/ExpandGroupSettingCard.cpp
    Settings/FolderListSettingCard.cpp
    Settings/OptionsSettingCard.cpp
    Settings/SettingCard.cpp
    Settings/SettingCardGroup.cpp
    Widgets/AcrylicLabel.cpp
    Widgets/Button.cpp
    Widgets/CheckBox.cpp
    Widgets/ComboBox.cpp
    Widgets/CycleListWidget.cpp
    Widgets/IconWidget.cpp
    Widgets/InfoBar.cpp
    Widgets/Label.cpp
    Widgets/LineEdit.cpp
    Widgets/Menu.cpp
    Widgets/MultiSelectComboBox.cpp
    Widgets/ScrollArea.cpp
    Widgets/Slider.cpp
    Widgets/SpinBox.cpp
    Widgets/StackedWidget.cpp
    Widgets/StateToolTip.cpp
    Widgets/SwitchButton.cpp
    Widgets/ThreeStateButton.cpp
    Widgets/ToolTip.cpp
    Widgets/TreeView.cpp
)

set(_links_private)

set(_sync_include_options)

if(Qt6_FOUND)
    qfui_add_library(${PROJECT_NAME} AUTOGEN
        SOURCES ${_src}
        FEATURES cxx_std_17
        LINKS_PRIVATE ${_links_private}
        QT_LINKS Core Gui Widgets Svg Xml Core5Compat
        QT_INCLUDE_PRIVATE Core Gui Widgets Svg Xml Core5Compat
        INCLUDE_PRIVATE kernel contexts shared
        PREFIX QFUI_Core
        SYNC_INCLUDE_OPTIONS ${_sync_include_options}
    )
else()
    qfui_add_library(${PROJECT_NAME} AUTOGEN
        SOURCES ${_src}
        FEATURES cxx_std_17
        LINKS_PRIVATE ${_links_private}
        QT_LINKS Core Gui Widgets Svg Xml
        QT_INCLUDE_PRIVATE Core Gui Widgets Svg Xml
        PREFIX QFUI_Core
        SYNC_INCLUDE_OPTIONS ${_sync_include_options}
    )
endif()

set(QFLUENTWIDGETS_ENABLED_TARGETS ${QFLUENTWIDGETS_ENABLED_TARGETS} ${PROJECT_NAME} PARENT_SCOPE)
set(QFLUENTWIDGETS_ENABLED_SUBDIRECTORIES ${QFLUENTWIDGETS_ENABLED_SUBDIRECTORIES} core PARENT_SCOPE)
