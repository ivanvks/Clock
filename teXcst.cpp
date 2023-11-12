#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Создаем главное окно
    QWidget window;
    window.setWindowTitle("Пример с иконкой, текстом и кнопкой");

    // Создаем иконку
    QLabel iconLabel;
    QPixmap iconPixmap(":/path/to/your/icon.png"); // Укажите путь к своей иконке
    iconLabel.setPixmap(iconPixmap);

    // Создаем текст
    QLabel textLabel("Ваш текст");

    // Создаем кнопку
    QPushButton button("Нажми меня");

    // Создаем компоновку
    QHBoxLayout layout;
    layout.addWidget(&iconLabel);
    layout.addWidget(&textLabel);
    layout.addWidget(&button);

    // Устанавливаем компоновку в главное окно
    window.setLayout(&layout);

    // Отображаем окно
    window.show();

    return a.exec();
}
