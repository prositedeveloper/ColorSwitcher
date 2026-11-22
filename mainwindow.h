#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMetaObject>
#include <QPointer>
#include <QTimer>
#include <QWidget>

#include "colorwidget.h"
#include "palettebutton.h"

class QLabel;
class QVBoxLayout;
class QGridLayout;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void toggleTimer();
    void decreaseInterval();
    void increaseInterval();
    void cycleMode(); // цикл -> случайный -> мигание -> цикл
    void addColorButton(); // динамическое создание соединения
    void clearPaletteButtons(); // разрыв динамических соединений
    void toggleClickHandler(); // переподключение сигнала холста
private:
    enum class Mode { Cycle, Random, Blink };
    void setupUi();
    void rebuildTimeoutConnection(); // пересоздание соединения таймера
    void reconnectCanvasHandler(); // пересоздание соединения холста
    void setStatus(const QString &text);
    void updateIntervalLabel(); // подпись интервала таймера
    void updateModeLabel(); // подпись текущего режима
    QString modeName() const;
    QTimer m_timer;
    ColorWidget m_canvas;
    Mode m_mode;
    bool m_clickHandlerAlt; // переключатель обработчика colorChanged
    QMetaObject::Connection m_timeoutConn; // соединение таймера (можно рвать)
    QMetaObject::Connection m_clickConn; // соединение холста (можно рвать)
    QVBoxLayout *m_rootLayout;
    QGridLayout *m_paletteGrid;
    QLabel *m_statusLabel;
    QLabel *m_intervalLabel;
    QLabel *m_modeLabel;
    QList<QPointer<PaletteButton>> m_paletteButtons; // живые указатели
    QList<QMetaObject::Connection> m_dynamicConnections; // соединения кнопок
};

#endif // MAINWINDOW_H