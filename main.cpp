#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

class EllipseWidget : public QWidget {
public:
    EllipseWidget(QWidget *parent = nullptr) : QWidget(parent), m_x(0) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &EllipseWidget::onTimer);
        timer->start(10);

        m_intervalLineEdit = new QLineEdit(this);
        m_intervalLineEdit->setText("50");
        m_intervalLineEdit->setGeometry(10, 10, 80, 30);

        m_widthButton = new QPushButton(this);
        m_widthButton->setText("Width");
        m_widthButton->setGeometry(100, 10, 80, 30);
        connect(m_widthButton, &QPushButton::clicked, this, &EllipseWidget::onWidthButtonClicked);

        m_heightButton = new QPushButton(this);
        m_heightButton->setText("Height");
        m_heightButton->setGeometry(190, 10, 80, 30);
        connect(m_heightButton, &QPushButton::clicked, this, &EllipseWidget::onHeightButtonClicked);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(m_x, height() / 2, 50, 50);
    }

private slots:
    void onTimer() {
        m_x += 1;
        if (m_x >= width())
            m_x = 0;
        update();
    }

    void onWidthButtonClicked() {
        int width = m_intervalLineEdit->width();
        m_intervalLineEdit->setFixedWidth(width + 10);
    }

    void onHeightButtonClicked() {
        int height = m_intervalLineEdit->height();
        m_intervalLineEdit->setFixedHeight(height + 10);
    }

private:
    int m_x;
    QLineEdit *m_intervalLineEdit;
    QPushButton *m_widthButton;
    QPushButton *m_heightButton;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EllipseWidget *widget = new EllipseWidget();
    widget->setFixedSize(400, 200);
    widget->show();

    return app.exec();
}
