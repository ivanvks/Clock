#include <QByteArray>
#include <QBuffer>
#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlFormatter>
#include <QDebug>

void convertXmlToHtml(const QByteArray& xmlData, const QByteArray& xsltData)
{
    // Создание объекта QBuffer для работы с данными XML
    QBuffer xmlBuffer;
    xmlBuffer.setData(xmlData);
    xmlBuffer.open(QIODevice::ReadOnly);

    // Создание объекта QXmlQuery
    QXmlQuery query;
    query.setFocus(&xmlBuffer);

    // Установка XSLT-стиля для преобразования
    query.setQuery(xsltData);

    // Выполнение XSLT-преобразования
    QByteArray htmlData;
    QBuffer htmlBuffer(&htmlData);
    htmlBuffer.open(QIODevice::WriteOnly | QIODevice::Text);

    if (query.evaluateTo(&htmlBuffer))
    {
        // Вывод результата преобразования в консоль
        qDebug() << "HTML Result:";
        qDebug() << htmlData;
    }
    else
    {
        qDebug() << "Error during XSLT transformation:";
        qDebug() << query.hasError();
        qDebug() << query.errorString();
    }
}

int main()
{
    // Ваши данные XML и XSLT
    QByteArray xmlData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<asu version=\"1.0\">\n <email>\n <subject>msg</subject>\n <to>\n <contact>\n <contact_name>DL1</contact_name>\n <contact_ip>\n <ip>10.10.10.1</ip>\n </contact_ip>\n </contact>\n <contact>\n <contact_name>Dl2</contact_name>\n <contact_ip>\n <ip>11.11.11.2</ip>\n </contact_ip>\n </contact>\n </to>\n <body>text</body>\n </email>\n </asu>";
    QByteArray xsltData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">\n<xsl:template match=\"/\">\n<html>\n<head><title>Converted HTML</title></head>\n<body>\n<xsl:apply-templates/>\n</body>\n</html>\n</xsl:template>\n<xsl:template match=\"email\">\n<h1><xsl:value-of select=\"subject\"/></h1>\n<p>From: <xsl:value-of select=\"from/contact/contact_name\"/></p>\n<p>To:</p>\n<ul>\n<xsl:apply-templates select=\"to/contact\"/>\n</ul>\n<p><xsl:value-of select=\"body\"/></p>\n</xsl:template>\n<xsl:template match=\"contact\">\n<li><xsl:value-of select=\"contact_name\"/> - <xsl:value-of select=\"contact_ip/ip\"/></li>\n</xsl:template>\n</xsl:stylesheet>";

    // Преобразование XML в HTML с использованием XSLT
    convertXmlToHtml(xmlData, xsltData);

    return 0;
}
