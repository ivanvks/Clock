QString CSqlDatabase::selectIn( const QString &msgType )
{
    QString subType;
    /// инициализируем запрос к базе данных
    QSqlQuery sqlQuery( mDataBase_ );

    sqlQuery.prepare("SELECT in_msg_buff.msg_subtype FROM in_msg_buff WHERE in_msg_buff.msg_type = '" + msgType + "' LIMIT 1");
    if (sqlQuery.exec()) {
        while (sqlQuery.next()) {
            subType = sqlQuery.value(0).toString();
        }
    } else {
        qDebug() << sqlQuery.lastError().text();
    }
    qDebug() << __PRETTY_FUNCTION__ << msgType << "Подтип  =>" << subType;
    /// сигнал подтипа 
   emit signalNEW(subType);

   return subType;
}
