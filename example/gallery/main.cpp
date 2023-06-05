﻿#include "view/MainWindow.h"

#include <QApplication>
#include <FramelessHelper/Core/private/framelessconfig_p.h>
#include "shared/log.h"

#include <QTranslator>

FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[])
{
#if (QT_VERSION > QT_VERSION_CHECK(5, 14, 0))
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    Log::setup(FRAMELESSHELPER_STRING_LITERAL("mainwindow"));

    // Not necessary, but better call this function, before the construction
    // of any Q(Core|Gui)Application instances.
    FramelessHelper::Widgets::initialize();

#if 0
    if (!qEnvironmentVariableIsSet("QT_WIDGETS_RHI")) {
        qputenv("QT_WIDGETS_RHI", FRAMELESSHELPER_BYTEARRAY_LITERAL("1"));
    }
#endif

    const auto application = std::make_unique<QApplication>(argc, argv);

    application->setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    // Must be called after QGuiApplication has been constructed, we are using
    // some private functions from QPA which won't be available until there's
    // a QGuiApplication instance.
    FramelessHelper::Core::setApplicationOSThemeAware();

    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
    FramelessConfig::instance()->set(Global::Option::DisableLazyInitializationForMicaMaterial);

    const auto mainWindow = std::make_unique<MainWindow>();
    mainWindow->waitReady();
    mainWindow->show();

    return QCoreApplication::exec();
}
