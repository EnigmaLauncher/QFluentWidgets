﻿#ifndef INFOBAR_H
#define INFOBAR_H

#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QToolButton>
#include <QParallelAnimationGroup>
#include "Common/Icon.h"

class InfoBarCloseButton : public QToolButton
{
    Q_OBJECT
public:
    explicit InfoBarCloseButton(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QScopedPointer<FluentIcon> m_ficon;
};

class InfoBarIcon : public FluentIconBase
{
    Q_OBJECT
public:
    enum IconType
    {
        INFORMATION = 0,
        SUCCESS,
        WARNING,
        ERROR
    };

    Q_ENUM(IconType)
    //    const QString INFORMATION = "Info";
    //    const QString SUCCESS     = "Success";
    //    const QString WARNING     = "Warning";
    //    const QString ERROR       = "Error";
    static QString iconName(IconType type);

    InfoBarIcon(IconType type, Qfw::Theme t = Qfw::AUTO);
    ~InfoBarIcon();

    QString iconPath();

    // FluentIconBase interface
    QIcon icon() override;
    QString typeName() const override;
    QString enumName() const override;
    FluentIconBase *clone() override;
    Qfw::Theme theme() const;
    void setTheme(const Qfw::Theme &theme) override;

private:
    Qfw::Theme m_theme;
    IconType m_type;
};

enum InfoBarPosition
{
    INFOBAR_TOP          = 0,
    INFOBAR_BOTTOM       = 1,
    INFOBAR_TOP_LEFT     = 2,
    INFOBAR_TOP_RIGHT    = 3,
    INFOBAR_BOTTOM_LEFT  = 4,
    INFOBAR_BOTTOM_RIGHT = 5,
    INFOBAR_NONE         = 6
};

class InfoIconWidget : public QWidget
{
    Q_OBJECT
public:
    InfoIconWidget(FluentIconBase *icon, QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QScopedPointer<FluentIconBase> m_icon;
};

class InfoBar : public QFrame
{
    Q_OBJECT
public:
    explicit InfoBar(FluentIconBase *ficon, const QString &title, const QString &content,
                     Qt::Orientation orient = Qt::Horizontal, bool isClosable = true, int duration = 1000,
                     InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

    void adjustSize();
    void addWidget(QWidget *widget, int stretch = 0);
    void setCustomBackgroundColor(const QColor &light, const QColor &dark);

    static InfoBar *creator(FluentIconBase *ficon, const QString &title, const QString &content,
                            Qt::Orientation orient = Qt::Horizontal, bool isClosable = true, int duration = 1000,
                            InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

    static InfoBar *info(const QString &title, const QString &content, Qt::Orientation orient = Qt::Horizontal,
                         bool isClosable = true, int duration = 1000,
                         InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

    static InfoBar *success(const QString &title, const QString &content, Qt::Orientation orient = Qt::Horizontal,
                            bool isClosable = true, int duration = 1000,
                            InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

    static InfoBar *warning(const QString &title, const QString &content, Qt::Orientation orient = Qt::Horizontal,
                            bool isClosable = true, int duration = 1000,
                            InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

    static InfoBar *error(const QString &title, const QString &content, Qt::Orientation orient = Qt::Horizontal,
                          bool isClosable = true, int duration = 1000,
                          InfoBarPosition position = InfoBarPosition::INFOBAR_TOP_RIGHT, QWidget *parent = nullptr);

protected:
    void adjustText();

    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    void closedSignal();

private:
    void initWidget();
    void setQss();
    void initLayout();

private slots:
    void fadeOut();

private:
    QString m_title;
    QString m_content;
    Qt::Orientation m_orient;
    QSharedPointer<FluentIconBase> m_ficon;
    //    FluentIconBase *m_ficon;
    int m_duration;
    bool m_isClosable;
    InfoBarPosition m_position;

    QLabel *m_titleLabel;
    QLabel *m_contentLabel;
    InfoBarCloseButton *m_closeButton;
    InfoIconWidget *m_iconWidget;
    QVBoxLayout *m_vBoxLayout;
    QHBoxLayout *m_hBoxLayout;
    QBoxLayout *m_contentLayout;
    QGraphicsOpacityEffect *m_opacityEffect;
    QPropertyAnimation *m_opacityAni;
    QColor m_lightBackgroundColor;
    QColor m_darkBackgroundColor;
};

Q_DECLARE_METATYPE(QPropertyAnimation *)

class InfoBarManagerBase : public QObject
{
    Q_OBJECT
public:
    InfoBarManagerBase(QObject *parent = nullptr);

    void add(InfoBar *infoBar);
    void remove(InfoBar *infoBar);

    int spacing;
    int margin;
    QHash<QWidget *, QList<InfoBar *>> infoBars;
    QHash<QWidget *, QParallelAnimationGroup *> aniGroups;
    QList<QPropertyAnimation *> slideAnis;
    QList<QPropertyAnimation *> dropAnis;

protected:
    QPropertyAnimation *createSlideAni(InfoBar *infoBar);
    void updateDropAni(QWidget *parent);
    virtual QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) = 0;
    virtual QPoint slideStartPos(InfoBar *infoBar)                          = 0;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

class TopInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit TopInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class TopRightInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit TopRightInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class BottomRightInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit BottomRightInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class TopLeftInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit TopLeftInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class BottomLeftInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit BottomLeftInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class BottomInfoBarManager : public InfoBarManagerBase
{
    Q_OBJECT
public:
    explicit BottomInfoBarManager(QObject *parent = nullptr);

    // InfoBarManagerBase interface
protected:
    QPoint pos(InfoBar *infoBar, const QSize &parentSize = QSize()) override;
    QPoint slideStartPos(InfoBar *infoBar) override;
};

class InfoBarManagerFactory
{
public:
    static InfoBarManagerBase &factory(InfoBarPosition postion);
};

#endif  // INFOBAR_H
