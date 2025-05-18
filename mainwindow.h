#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addItem(const QString &name, int quantity, double price);
    void updateReceiptAmount();

private slots:
    void on_tableWidgetProdactTable_cellChanged(int row, int column);
    void onDigitButtonClicked();
    void onDotButtonClicked();
    void onClearButtonClicked();
    void updateChange();
    void updateTotalAmount();
    void closeReceipt();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
