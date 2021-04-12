#include "Widget.h"
#include "ui_Widget.h"
#include <qtrpt.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    const QStringList titles { "ID", "Nombre", "Edad", "Salario" };
    ui->tableWidget->setColumnCount(titles.size());
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->idSpinBox->setMinimum(0);
    ui->idSpinBox->setMaximum(INT_MAX);
    ui->edadSpinBox->setMinimum(0);
    ui->edadSpinBox->setMaximum(INT_MAX);
    ui->salarioDoubleSpinBox->setMinimum(0.0);
    ui->salarioDoubleSpinBox->setMaximum(999999999.0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_agregarButton_clicked()
{
    const QString id = QString::number(ui->idSpinBox->value());
    const QString nombre = ui->nombreLineEdit->text();
    const QString edad = QString::number(ui->edadSpinBox->value());
    const QString salario = QString::number(ui->salarioDoubleSpinBox->value());
    const int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, ID, new QTableWidgetItem(id));
    ui->tableWidget->setItem(rowCount, NOMBRE, new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(rowCount, EDAD, new QTableWidgetItem(edad));
    ui->tableWidget->setItem(rowCount, SALARIO, new QTableWidgetItem(salario));
    ui->idSpinBox->clear();
    ui->nombreLineEdit->clear();
    ui->edadSpinBox->clear();
    ui->salarioDoubleSpinBox->clear();
    ui->idSpinBox->setFocus();
}

void Widget::on_eliminarButton_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void Widget::on_imprimirButton_clicked()
{
    QtRPT *report = new QtRPT(this);
    report->loadReport(":/reporte.xml");
    report->recordCount.append(ui->tableWidget->rowCount());

    connect(report, &QtRPT::setValue, [&](const int recNo,
            const QString paramName, QVariant &paramValue,
            const int reportPage) {
        (void) reportPage;
        if (paramName == "id") {
            paramValue = ui->tableWidget->item(recNo, ID)->text();
        }
        if (paramName == "nombre") {
            paramValue = ui->tableWidget->item(recNo, NOMBRE)->text();
        }
        if (paramName == "edad") {
            paramValue = ui->tableWidget->item(recNo, EDAD)->text();
        }
        if (paramName == "salario") {
            paramValue = ui->tableWidget->item(recNo, SALARIO)->text();
        }
    });

    report->printExec();
}
