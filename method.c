QMetaObject::invokeMethod(mCSqlDatabase_, [=]() {
    // Связываем сигнал data() и слот prokData()
    QObject::connect(mCSqlDatabase_, &CSqlDatabase::data, mCSqlDatabase_, &CSqlDatabase::prokData);

    // Отправляем сигнал data()
    emit mCSqlDatabase_->data();

    // Далее выполняем открытие базы данных
    mCSqlDatabase_->openDataBase(*mCSettings_);
}, Qt::QueuedConnection);
QThread* dbThread = new QThread;

// Перемещаем mCSqlDatabase_ в новый поток
mCSqlDatabase_->moveToThread(dbThread);

// Связываем сигнал data и слот prokData внутри нового потока
connect(this, &Isaos::data, mCSqlDatabase_, &CSqlDatabase::prokData);

// Запускаем новый поток
dbThread->start();

// Теперь вызываем openDataBase в новом потоке
QMetaObject::invokeMethod(mCSqlDatabase_, [=]() {
    mCSqlDatabase_->openDataBase(*mCSettings_);
}, Qt::QueuedConnection);
void Isaos::startNewThread() {
    // Передаем указатель на текущий объект Isaos в лямбда-функцию
    QMetaObject::invokeMethod(mCSqlDatabase_, [=, this]() {
        // Открываем базу данных в текущем потоке
        mCSqlDatabase_->openDataBase(*mCSettings_);
    }, Qt::QueuedConnection);

    // Запускаем слот prokData в новом потоке
    QtConcurrent::run(mCSqlDatabase_, &CSqlDatabase::prokData);
}
