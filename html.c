#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>

void convertXmlToHtml(const QString& xmlFilePath, const QString& htmlFilePath) {
    QFile xmlFile(xmlFilePath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open XML file";
        return;
    }

    QFile htmlFile(htmlFilePath);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open HTML file";
        return;
    }

    QXmlStreamReader xmlReader(&xmlFile);
    QDomDocument htmlDocument;
    QDomElement htmlRoot = htmlDocument.createElement("html");
    htmlDocument.appendChild(htmlRoot);

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QDomElement divElement = htmlDocument.createElement("div");
            QDomElement spanElement = htmlDocument.createElement("span");

            spanElement.setAttribute("class", xmlReader.name().toString());

            xmlReader.readNext();
            if (xmlReader.tokenType() == QXmlStreamReader::Characters) {
                QDomText textNode = htmlDocument.createTextNode(xmlReader.text().toString());
                spanElement.appendChild(textNode);
            }

            divElement.appendChild(spanElement);
            htmlRoot.appendChild(divElement);
        }
    }

    QTextStream htmlStream(&htmlFile);
    htmlDocument.save(htmlStream, 2); // Save with indentation
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString xmlFilePath = "path/to/your/input.xml";
    QString htmlFilePath = "path/to/your/output.html";

    convertXmlToHtml(xmlFilePath, htmlFilePath);

    return a.exec();
}
