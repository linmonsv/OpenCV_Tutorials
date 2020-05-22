#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // read an image
    cv::Mat image = cv::imread("C:/Users/d/source/repos/OpenCV_Tutorials/data/lena.jpg", 1);
    //if(!image.data) {
        // create image window named "My Image"
        cv::namedWindow("My Image");
        // show the image on window
        cv::imshow("My Image", image);
    //}
    qDebug() << "app.exec...";

    return app.exec();
}
