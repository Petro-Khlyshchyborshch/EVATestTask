#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Чек");
    ui->tableWidgetProdactTable->setColumnCount(3);
    ui->tableWidgetProdactTable->setHorizontalHeaderLabels({"Назва товару", "Кількість", "Ціна"});
    QHeaderView *header = ui->tableWidgetProdactTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    ui->pushButtonCloseReceipt->setEnabled(false);

    connect(ui->lineEditReceiptAmount, &QLineEdit::textChanged, this, &MainWindow::updateTotalAmount);
    connect(ui->lineEditDiscountAmount, &QLineEdit::textChanged, this, &MainWindow::updateTotalAmount);
    connect(ui->lineEditClientCash, &QLineEdit::textChanged, this, &MainWindow::updateChange);



    connect(ui->pushButton0, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton1, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton3, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton4, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton5, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton6, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton7, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton8, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    connect(ui->pushButton9, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);

    connect(ui->pushButtonDot, &QPushButton::clicked, this, &MainWindow::onDotButtonClicked);
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    connect(ui->pushButtonCloseReceipt, &QPushButton::clicked, this, &MainWindow::closeReceipt);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::addItem(const QString &name, int quantity, double price)
{
    int row = ui->tableWidgetProdactTable->rowCount();
    ui->tableWidgetProdactTable->insertRow(row);

    ui->tableWidgetProdactTable->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidgetProdactTable->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
    ui->tableWidgetProdactTable->setItem(row, 2, new QTableWidgetItem(QString::number(price, 'f', 2)));
}

void MainWindow::updateReceiptAmount()
{
    double totalAmount = 0.0;


    for (int row = 0; row < ui->tableWidgetProdactTable->rowCount(); ++row)
    {
        QTableWidgetItem *quantityItem = ui->tableWidgetProdactTable->item(row, 1);
        QTableWidgetItem *priceItem = ui->tableWidgetProdactTable->item(row, 2);

        if (quantityItem && priceItem)
        {
            int quantity = quantityItem->text().toInt();
            double price = priceItem->text().toDouble();


            totalAmount += quantity * price;
        }
    }


    ui->lineEditReceiptAmount->setText(QString::number(totalAmount, 'f', 2));
}




void MainWindow::on_tableWidgetProdactTable_cellChanged(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);


    updateReceiptAmount();
}


void MainWindow::updateTotalAmount()
{
    bool okReceipt, okDiscount;

    double receiptAmount = ui->lineEditReceiptAmount->text().toDouble(&okReceipt);
    double discountAmount = ui->lineEditDiscountAmount->text().toDouble(&okDiscount);


    if (!okReceipt)
    {
        ui->lineEditReceiptAmount->setStyleSheet("background-color: red;");
    } else
    {
        ui->lineEditReceiptAmount->setStyleSheet("background-color: white;");
    }

    if (!okDiscount)
    {
        ui->lineEditDiscountAmount->setStyleSheet("background-color: red;");
    } else
    {
        ui->lineEditDiscountAmount->setStyleSheet("background-color: white;");
    }

    if (okReceipt && okDiscount)
    {
        double totalAmount = receiptAmount - discountAmount;
        ui->lineEditTotalAmount->setText(QString::number(totalAmount, 'f', 2));
        ui->lineEditTotalAmount->setStyleSheet("background-color: white;");  // Скидаємо підсвітку
    }
}

void MainWindow::updateChange()
{
    bool okClientCash;

    double clientCash = ui->lineEditClientCash->text().toDouble(&okClientCash);

    if (!okClientCash)
    {
        ui->lineEditClientCash->setStyleSheet("background-color: red;");
    } else
    {
        ui->lineEditClientCash->setStyleSheet("background-color: white;");
    }

    if (okClientCash && !ui->lineEditTotalAmount->text().isEmpty())
    {
        double totalAmount = ui->lineEditTotalAmount->text().toDouble();
        double change = clientCash - totalAmount;
        ui->lineEditChange->setText(QString::number(change, 'f', 2));

        if (change < 0)
        {
            ui->pushButtonCloseReceipt->setEnabled(false);
            ui->lineEditChange->setStyleSheet("background-color: red;");
        } else
        {
            ui->pushButtonCloseReceipt->setEnabled(true);
            ui->lineEditChange->setStyleSheet("background-color: green;");
        }
    }
}


void MainWindow::onDigitButtonClicked()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString currentText = ui->lineEditClientCash->text();
        // Додаємо цифру до поточного тексту
        currentText.append(button->text());
        ui->lineEditClientCash->setText(currentText);
    }
}

void MainWindow::onDotButtonClicked()
{
    QString currentText = ui->lineEditClientCash->text();
    if (currentText.isEmpty())
    {
        currentText.append("0");
        currentText.append('.');
    } else if (!currentText.contains('.'))
    {
        // Якщо в тексті немає крапки, додаємо її
        currentText.append('.');
    }
     ui->lineEditClientCash->setText(currentText);
}

void MainWindow::onClearButtonClicked()
{
    ui->lineEditClientCash->clear();
    ui->lineEditChange->clear();
    ui->pushButtonCloseReceipt->setEnabled(false);
    ui->lineEditChange->setStyleSheet("background-color: red;");
    ui->lineEditClientCash->setStyleSheet("background-color: red;");
}

void MainWindow::closeReceipt()
{
    QMessageBox::information(this, "Успішно", "Чек успішно закрито!");
}
