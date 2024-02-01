#include <QCoreApplication>
#include <QFile>
#include <QXmlQuery>
#include <QXmlFormatter>

void convertXmlToHtml(const QString &xmlFilePath, const QString &xslFilePath, const QString &htmlFilePath) {
    QFile xmlFile(xmlFilePath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open XML file";
        return;
    }

    QFile xslFile(xslFilePath);
    if (!xslFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open XSL file";
        return;
    }

    QFile htmlFile(htmlFilePath);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open HTML file";
        return;
    }

    QXmlQuery query;
    query.setFocus(&xmlFile);

    // Применяем XSLT-стиль
    query.setQuery(QUrl::fromLocalFile(xslFilePath));

    QByteArray htmlData;
    QXmlFormatter formatter(&htmlData, query.namePool());

    if (query.evaluateTo(&formatter)) {
        QTextStream htmlStream(&htmlFile);
        htmlStream << htmlData;
    } else {
        qDebug() << "XSLT transformation failed";
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString xmlFilePath = "path/to/your/input.xml";
    QString xslFilePath = "path/to/your/stylesheet.xsl";
    QString htmlFilePath = "path/to/your/output.html";

    convertXmlToHtml(xmlFilePath, xslFilePath, htmlFilePath);

    return a.exec();
}
