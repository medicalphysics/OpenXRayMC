

#include <QApplication>
#include <QDir>
#include <QGraphsTheme>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QQuickWidget>
#include <QScatterSeries>
#include <QSplashScreen>
#include <QSurfaceFormat>

class TestWidget : public QWidget {
public:
    TestWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        setMinimumSize(800, 600);

        m_quickWidget = new QQuickWidget;
        auto layout = new QVBoxLayout(this);
        layout->addWidget(m_quickWidget);
        // m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        // m_quickWidget->setSource(QUrl::fromLocalFile("graphsview.qml"));
        //  Apply a theme to the graphs
        // QGraphsTheme* theme = new QGraphsTheme(m_quickWidget->engine());
        // theme->setBaseTheme(QGraphsTheme::BaseTheme::Dark);
        // m_quickWidget->rootContext()->setContextProperty("graphsTheme", theme);

        m_scatterSeries = new QScatterSeries(this);
        m_scatterSeries->setName("Scatter Series Example");
        m_scatterSeries->append(1, 3);
        m_scatterSeries->append(2, 5);
        m_scatterSeries->append(3, 2);
        initializeQuickWidget();
    }
    void initializeQuickWidget()
    {
        m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        m_quickWidget->loadFromModule("QtGraphs", "GraphsView");
        auto theme = new QGraphsTheme(m_quickWidget);
        theme->setTheme(QGraphsTheme::Theme::BlueSeries);
        theme->setLabelBorderVisible(true);
        theme->setLabelBackgroundVisible(true);
        theme->setBackgroundColor(Qt::black);

        m_quickWidget->setInitialProperties({ { "theme", QVariant::fromValue(theme) },
            { "seriesList", QVariant::fromValue(m_scatterSeries) } });
    }

private:
    QQuickWidget* m_quickWidget;
    QScatterSeries* m_scatterSeries;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // setting current dir to exe dir
    const auto exeDirPath = QCoreApplication::applicationDirPath();
    QDir::setCurrent(exeDirPath);

    app.setStyle("fusion");

    app.processEvents();

    QMainWindow win;
    QString title = "qt graphs test";

    auto test = new TestWidget(&win);
    win.setCentralWidget(test);

    win.setWindowTitle(title);
    win.show();

    return app.exec();

    return 0;
}