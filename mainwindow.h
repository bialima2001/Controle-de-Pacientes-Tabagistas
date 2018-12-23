#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "paciente.h"
#include <QVector>
#include "turma.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Paciente *novo_paciente;
    Turma turma_pacientes;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTable(Paciente *x, int quantLinhas);
    void setPacienteWrite (Paciente *x);
    void limparWidget();
    void atualizarEstatisticas();
    bool salvar_TurmaPac(QString name, Turma x);
    bool carregar_TurmaPac(QString name, Turma &x);
    bool salvarTurma(QString &arquivo, Turma &turma);
    void setarPaciente (QStringList paciente, Paciente *x);


private slots:
    void on_pushButton_clicked();
    void on_btn_ordenaName_clicked();
    void on_ordenarPorCigarros_clicked();
    void salvar();
    void carregar();

    void on_tbl_turma_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
