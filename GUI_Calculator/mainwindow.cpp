#include "mainwindow.h"
#include <QPushButton>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentText("0"), currentOperator("")
{
    QWidget *central = new QWidget();
    QString labels[4][4] = 
    {
        {"7", "8", "9", "+"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "*"},
        {"0", "=", ".", "/"}
    };

    label = new QLabel("0", this);  // Display the initial text "0"
    auto *main_layout = new QVBoxLayout();
    auto *grid_layout = new QGridLayout();

    // Create the buttons and connect them
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            QString buttonText = labels[row][col];
            QPushButton *button = new QPushButton(buttonText, this);
            grid_layout->addWidget(button, row, col);

            // Connect number buttons
            if (buttonText.toInt() != 0 || buttonText == "0") {
                connect(button, &QPushButton::clicked, this, [=]() { numberPressed(buttonText); });
            }
            // Connect operator buttons
            else if (buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
                connect(button, &QPushButton::clicked, this, [=]() { operatorPressed(buttonText); });
            }
            // Connect equals button
            else if (buttonText == "=") {
                connect(button, &QPushButton::clicked, this, &MainWindow::equalsPressed);
            }
            // Connect dot (.) button (for decimal point)
            else if (buttonText == ".") {
                connect(button, &QPushButton::clicked, this, [=]() { numberPressed("."); });
            }
        }
    }

    main_layout->addWidget(label);
    main_layout->addLayout(grid_layout);
    central->setLayout(main_layout);
    setCentralWidget(central);
}

MainWindow::~MainWindow() {}

void MainWindow::numberPressed(const QString &number)
{
    if (currentText == "0" && number != ".") {
        currentText = number;  // Replace "0" with the first pressed number
    } else {
        currentText += number;  // Append the number pressed
    }
    label->setText(currentText);
}

void MainWindow::operatorPressed(const QString &op)
{
    if (currentOperator.isEmpty()) {
        currentOperator = op;  // Store the operator
        currentText += " " + op + " ";  // Display operator with spaces for clarity
        label->setText(currentText);
    }
}

void MainWindow::equalsPressed()
{
    // Handle calculation
    QStringList parts = currentText.split(" ");
    if (parts.size() == 3) {
        double operand1 = parts[0].toDouble();
        double operand2 = parts[2].toDouble();

        double result = 0;
        if (currentOperator == "+") {
            result = operand1 + operand2;
        } else if (currentOperator == "-") {
            result = operand1 - operand2;
        } else if (currentOperator == "*") {
            result = operand1 * operand2;
        } else if (currentOperator == "/") {
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                result = 0;  // Handle division by zero
            }
        }

        currentText = QString::number(result);
        label->setText(currentText);
        currentOperator.clear();  // Clear the operator after calculation
    }
}

void MainWindow::clear()
{
    currentText = "0";  // Reset the display text
    currentOperator.clear();
    label->setText(currentText);
}

