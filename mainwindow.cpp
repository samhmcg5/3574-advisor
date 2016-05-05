#include "mainwindow.h"

QFile adviceFile("advice.dat");
QFile weatherFile("weather.dat");
QFile reminderFile("reminder.dat");


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // set up user interface
    initUI();
    // connect signals and slots
    connectSlots();

    // load data from *.dat files
    loadAdvice();
    loadWeather();
    loadReminder();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI() {
    // Create and add central widget
    m_central = new QWidget;
    setCentralWidget(m_central);

    // create and set layout manager
    m_vbox = new QVBoxLayout;
    m_central->setLayout(m_vbox);

    // create items to add to vbox
    m_text = new QTextEdit;
    m_text->setReadOnly(true);
    m_adviceButton = new QPushButton("Advice");
    m_weatherButton = new QPushButton("Weather");
    m_reminderButton = new QPushButton("Reminder");
    m_quitButton = new QPushButton("Quit");

    // Add items to layout
    m_vbox->addWidget(m_text);
    m_vbox->addWidget(m_adviceButton);
    m_vbox->addWidget(m_weatherButton);
    m_vbox->addWidget(m_reminderButton);
    m_vbox->addWidget(m_quitButton);
}

void MainWindow::connectSlots() {
    connect(m_quitButton,SIGNAL(clicked(bool)),this,SLOT(promptQuit()));
    connect(m_adviceButton,SIGNAL(clicked(bool)),this,SLOT(getAdvice()));
    connect(m_weatherButton,SIGNAL(clicked(bool)),this,SLOT(getWeather()));
    connect(m_reminderButton,SIGNAL(clicked(bool)),this,SLOT(getReminder()));


}

void MainWindow::promptQuit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Advisor","Are you sure you want to quit?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        close();
    else
        return;
}

void MainWindow::getAdvice() {
    // pull random
    QString text;
    text = m_adviceList->at(random(m_adviceList->length()));
    text.prepend("Advice: ");
    m_text->append(text);
}

void MainWindow::getWeather() {
    // pull random from list
    QString text;
    text = m_weatherList->at(random(m_weatherList->length()));
    text.prepend("Weather: ");
    m_text->append(text);
}

void MainWindow::getReminder() {
    // pull random from list
    if (m_reminderList->isEmpty()) {
        // show a text instead of a reminder
        m_text->append("There are no reminders to show.");
    }
    else {
        int rand = random(m_reminderList->length());
        QString rem = m_reminderList->at(rand);

         // show dialog
        QMessageBox reply;
        reply.setIcon(QMessageBox::Information);
        QCheckBox * check = new QCheckBox("Show this message again");
        check->setChecked(true);
        reply.setCheckBox(check);
        reply.setText(rem);
        reply.exec();

        if (!check->isChecked()) {
            m_reminderList->removeAt(rand);
        }
    }
}

void MainWindow::loadAdvice() {
    m_adviceList = new QStringList;
    QStringList initial;
    QString temp;

    if (!adviceFile.exists())
        throw std::logic_error("Advice.dat does not exist!");

    adviceFile.open(QIODevice::ReadOnly);
    QTextStream in(&adviceFile);

    do {
        temp= in.readLine();
        if (temp.length() > 0) {
            initial.append(temp);
        }
    } while (!temp.isNull());


    adviceFile.close();
    m_adviceList = concatLines(initial,"advice.dat");
    return;
}

void MainWindow::loadWeather() {
    m_weatherList = new QStringList;
    QStringList initial;
    QString temp;

    if (!weatherFile.exists())
        throw std::logic_error("Weather.dat does not exist!");

    weatherFile.open(QIODevice::ReadOnly);
    QTextStream in(&weatherFile);

    do {
        temp= in.readLine();
        if (temp.length() > 0) {
            initial.append(temp);
        }
    } while (!temp.isNull());


    weatherFile.close();
    m_weatherList = concatLines(initial,"weather.dat");
    return;
}

void MainWindow::loadReminder() {
    m_reminderList = new QStringList;
    QStringList initial;
    QString temp;

    if (!reminderFile.exists())
        throw std::logic_error("Reminder.dat does not exist!");

    reminderFile.open(QIODevice::ReadOnly);
    QTextStream in(&reminderFile);

    do {
        temp= in.readLine();
        if (temp.length() > 0) {
            initial.append(temp);
        }
    } while (!temp.isNull());


    reminderFile.close();

    m_reminderList = concatLines(initial, "reminder.dat");

    for (int i = 0; i < m_reminderList->length(); ++i)
    {
        temp = m_reminderList->takeAt(i);
        temp.append(", ");
        temp.append(randDate().toString("h:mm AP, dddd MM/dd/yyyy"));
        m_reminderList->prepend(temp);

    }
    return;
}

QStringList * MainWindow::concatLines(QStringList list,QString fileName) {
    QStringList * output = new QStringList;
    QString current;


    for (int i = 0; i<list.length(); i++) {

        current = list.at(i);

        if (current.endsWith('\\')) {
            if (i == list.length()-1) {
                m_text->append("ERROR, last line in file " + fileName+" contains trailing '\\' !");
                return output;
            }

            while (current.endsWith('\\') && i<list.length()-1) {
                ++i;
                current.append(list.at(i));
            }
            current.remove('\\');
            output->append(current);
        }

        else {
            output->append(current);
        }
    }

    return output;
}

int random(int max) {
    int rand = qrand();
    return rand % max;
}

QDateTime randDate() {
    QDateTime day = QDateTime::currentDateTime();
    day = day.addDays(random(364));
    day = day.addSecs(random(5000));
    return day;
}
