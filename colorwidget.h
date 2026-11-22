#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QColor>
#include <QVector>
#include <QWidget>

class ColorWidget : public QWidget // 1. Исправлена опечатка в названии
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);
    ~ColorWidget() override;

    void addColor(const QColor &c);
    void resetPalette();
    QColor currentColor() const;

    void stepForward();
    void stepBackward();
    void setRandomColor();
    void toggleBlink();

signals:
    void colorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QColor> m_palette; // 2. Исправлены круглые скобки на угловые
    int m_index;
    bool m_blinkOn;
    QColor m_blinkBackup;

    static QVector<QColor> defaultPalette();
    void emitCurrent();
}; // 3. Добавлена точка с запятой

#endif // COLORWIDGET_H