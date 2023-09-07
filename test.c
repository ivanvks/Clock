QSqlDriver *driver = mASUVDataBase_.driver();
    if (driver->hasFeature(QSqlDriver::EventNotifications)) {
        /// Подписываемся на уведомления PostgreSQL
        if (driver->subscribeToNotification("message_updated")) {
            qDebug() << "Подписка на уведомление PostgreSQL 'message_updated' выполнена успешно";
        } else {
            qDebug() << "Не удалось подписаться на уведомление PostgreSQL 'message_updated'";
        }
    } else {
        qDebug() << "Драйвер PostgreSQL не поддерживает уведомления";
    }
    /// Подключаем сигнал от базы данных о входящем сообщении  к слоту обработки уведомлений
    //QObject::connect(driver, SIGNAL(notification(QString, QSqlDriver::NotificationSource)),
    //  this, SLOT(handlePostgresNotification(QString, QSqlDriver::NotificationSource)));
    QObject::connect(mASUVDataBase_.driver(),
                     SIGNAL(notification(QString, QSqlDriver::NotificationSource, QVariant)),
                     this, SLOT(handlePostgresNotification(QString, QSqlDriver::NotificationSource, QVariant)));

    ///Подключем сигнал слота обработки сообщений к слоту загрузки данных из таблицы базы данных
    QObject::connect(this, SIGNAL(postgresNotificationReceived(QString)),
                     this, SLOT(selectFromInMSG(QString)));

void CSqlDatabase::handlePostgresNotification(const QString &notificationName, QSqlDriver::NotificationSource source, const QVariant &payload)
{
     qDebug() << "Поступило новое уведомление PostgreSQL от канала 'message_updated' ";
    if (source == QSqlDriver::SelfSource)
    {
        if (notificationName == "message_updated")
        {
            // qDebug() << "Поступило новое уведомление PostgreSQL от канала 'message_updated' ";
            // Извлекаем данные из базы данных и обрабатываем их
            QString msgSubtype = payload.toString();
            QVector<QByteArray> dataVector = selectFromInMSG(msgSubtype);
           emit postgresNotificationReceived(notificationName);

        }
    }
}
