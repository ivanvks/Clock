QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
db.setHostName("your_host");
db.setDatabaseName("your_database");
db.setUserName("your_username");
db.setPassword("your_password");

if (db.open()) {
    QSqlDriver *driver = db.driver();
    if (driver->subscribeToNotification("your_notification_channel")) {
        while (driver->subscribedToNotifications()) {
            if (driver->waitForNotification()) {
                QSqlNotification notif = driver->notification();
                // Обработка уведомления о событии
            }
        }
    }
}
