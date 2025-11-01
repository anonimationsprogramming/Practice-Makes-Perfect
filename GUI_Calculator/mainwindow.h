#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *label;  // Display label for calculator
    QString currentText;  // To hold the text on the label
    QString currentOperator;  // To store the current operator

    void numberPressed(const QString &number);
    void operatorPressed(const QString &op);
    void equalsPressed();
    void clear();
};

#endif // MAINWINDOW_H

