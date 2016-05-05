#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>
#include <QtGlobal>
#include <stdexcept>
#include <QDateTime>

#include <string>
using std::string;
using std::logic_error;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // interface items
    QWidget * m_central;
    QVBoxLayout * m_vbox;
    QTextEdit * m_text;
    QPushButton * m_adviceButton;
    QPushButton * m_weatherButton;
    QPushButton * m_reminderButton;
    QPushButton * m_quitButton;

    // methods
    void initUI();          // set up user interface
    void connectSlots();    // connect the SIGNALS to the SLOTS

    void loadAdvice();      // load from data file ...
    void loadWeather();     // ... into a string list
    void loadReminder();

    QStringList *concatLines(QStringList list,QString fileName); // find lines that end in '\' and concat them together.
                                               // thows an error if last line has '\' at end.

    // Lists of data
    QStringList * m_adviceList;
    QStringList * m_weatherList;
    QStringList * m_reminderList;

private slots:
    void promptQuit();
    void getAdvice();       // display advice to the screen
    void getWeather();      // display weather to the screen
    void getReminder();     // display a reminder to the screen


};

int random(int max);    // get a random number
QDateTime randDate();

#endif // MAINWINDOW_H
