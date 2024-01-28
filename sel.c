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

QString CSqlDatabase::selectIn(const QString &msgType)
{
    QString subType;
    QString text;

    /// Инициализируем запрос к базе данных
    QSqlQuery sqlQuery(mDataBase_);

    // Первый запрос
    sqlQuery.prepare("SELECT in_msg_buff.msg_subtype FROM in_msg_buff WHERE in_msg_buff.msg_type = :msgType LIMIT 1");
    sqlQuery.bindValue(":msgType", msgType);
    if (sqlQuery.exec()) {
        while (sqlQuery.next()) {
            subType = sqlQuery.value(0).toString();
        }
    } else {
        qDebug() << sqlQuery.lastError().text();
    }

    qDebug() << __PRETTY_FUNCTION__ << msgType << "Подтип  =>" << subType;

    // Второй запрос
    if (subType == "20") { // Предполагается, что subType - это QString
        sqlQuery.prepare("SELECT "
                         "regexp_replace("
                         "convert("
                         "convert_from("
                         "substring(in_msg.msg_data FROM position(E'\\x00' IN in_msg.msg_data, 1) + 1 FOR position(E'\\x00' IN in_msg.msg_data FROM position(E'\\x00' IN in_msg.msg_data) + 1) - position(E'\\x00' IN in_msg.msg_data) - 1),"
                         "'KOI8-R'"
                         "),"
                         "'UTF-8'"
                         "),"
                         "'[^a-zA-Zа-яА-ЯёЁ0-9\\s(){}[\\\\]/.,\\\\=+\\-_*&^%$#@!~`<>:;\"|№()]',"
                         "'' ,"
                         "'g'"
                         ") AS extracted_text "
                         "FROM in_msg;");

        if (sqlQuery.exec()) {
            while (sqlQuery.next()) {
                text = sqlQuery.value(0).toString();
            }
        } else {
            qDebug() << sqlQuery.lastError().text();
        }

        emit signalNEW(subType);
        emit signalNEW(text);

        return subType;
    }

    return QString(); // Вернуть пустую строку QString, если условие не выполнено
}

/////////////////////////////////
QString CSqlDatabase::selectIn( const QString &msgType )
{
    QString subType;
    QString text;
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
   if (subType == "20")
{sqlQuery.prepare("SELECT
  "regexp_replace("
    "convert("
      "convert_from("
        "substring(in_msg.msg_data FROM position(E'\x00' IN in_msg.msg_data, 1) + 1 FOR position(E'\x00' IN in_msg.msg_data FROM position(E'\x00' IN in_msg.msg_data) + 1) - position(E'\x00' IN in_msg.msg_data) - 1),"
        "'KOI8-R'"
      "),"
      "'UTF-8'"
    "),"
    "'[^a-zA-Zа-яА-ЯёЁ0-9\s(){}[\\]/.,\\=+\\-_*&^%$#@!~`<>:;"|№()]',"
    "'',"
    "'g'"
  ") AS extracted_text"
"FROM in_msg;");
    if (sqlQuery.exec()) {
        while (sqlQuery.next()) {
            text = sqlQuery.value(0).toString();
        }
    } else {
        qDebug() << sqlQuery.lastError().text();
    }

   emit signalNEW(subType);
   emit signalNEW(text);

   return subType;
}
