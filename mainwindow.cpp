#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSalvar,SIGNAL(triggered()), this, SLOT(salvar()));
    connect(ui->actionCarregar,SIGNAL(triggered()), this, SLOT(carregar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTable(Paciente *x, int quantLinhas)
{
    QTableWidgetItem *rec;
    ui->tbl_turma->setItem(quantLinhas,0,new QTableWidgetItem(x->getNome()));
    ui->tbl_turma->setItem(quantLinhas,1,new QTableWidgetItem(x->getData_nas()));
    ui->tbl_turma->setItem(quantLinhas,2,new QTableWidgetItem(x->getNum_cartao()));
    ui->tbl_turma->setItem(quantLinhas,3,new QTableWidgetItem(x->getEndereco()));
    ui->tbl_turma->setItem(quantLinhas,4,new QTableWidgetItem(QString::number(x->getCigarros())));
    ui->tbl_turma->setItem(quantLinhas,5,new QTableWidgetItem(x->getTratamento()));
    if(x->getRecuperacao()){
        rec = new QTableWidgetItem("obteve sucesso");
        rec->setTextColor("green");
        ui->tbl_turma->setItem(quantLinhas,6, rec);
    }else{
        rec = new QTableWidgetItem("em andamento");
        rec->setTextColor("red");
        ui->tbl_turma->setItem(quantLinhas,6, rec);
    }
}

void MainWindow::setPacienteWrite(Paciente *x)
{
    x->setNome(ui->le_name->text());
    x->setEndereco(ui->le_endereco->text());
    x->setData_nas(ui->dateEdit->text());
    x->setNum_cartao(ui->le_cartao->text());
    x->setCigarros(ui->sb_cigarros->text().toInt());
    x->setRecuperacao(ui->checkBox->isChecked());
}

void MainWindow::limparWidget()
{
    ui->le_name->clear();
    ui->le_endereco->clear();
    ui->le_cartao->clear();
    ui->sb_cigarros->clear();
    if(ui->checkBox->isChecked()){
        ui->checkBox->click();
    }
}

void MainWindow::atualizarEstatisticas()
{
    ui->total_pac->setNum(turma_pacientes.totalDePacientes());
    ui->lbl_MedCigDia->setText(QString::number(turma_pacientes.mediaDeCigarros(),'f',2));
    ui->lbl_abandono->setNum(turma_pacientes.totalDeAbandonoCigarro());
}

void MainWindow::on_pushButton_clicked()
{
    int quantColunas = ui->tbl_turma->rowCount();

    if(ui->le_name->text()!=0 && ui->le_endereco->text()!=0 && ui->dateEdit->text()!=0 && ui->sb_cigarros->text()!=0 && ui->le_cartao->text() !=0){

        novo_paciente = new Paciente();
        setPacienteWrite(novo_paciente);
        ui->tbl_turma->insertRow(quantColunas);
        setTable(novo_paciente, quantColunas);

        turma_pacientes.inserirPaciente(*novo_paciente);
        limparWidget();
        delete novo_paciente;
        atualizarEstatisticas();

    }
}


void MainWindow::on_btn_ordenaName_clicked()
{
    novo_paciente = new Paciente;
    turma_pacientes.ordenarPorNome();
    ui->tbl_turma->clearContents();
    for(int i = 0; i<turma_pacientes.totalDePacientes(); i++){
        novo_paciente = turma_pacientes.retornoPaciente(i);
        setTable(novo_paciente, i);
    }
}

bool MainWindow::salvar_TurmaPac(QString name, Turma x)
{
    QFile file(name);
    novo_paciente = new Paciente;
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QTextStream out(&file);

    for(int i=0;i<x.totalDePacientes();i++){
        novo_paciente = turma_pacientes.retornoPaciente(i);
        out << novo_paciente->getNome()<<","<<novo_paciente->getData_nas()<<",";
        out <<novo_paciente->getNum_cartao()<<","<<novo_paciente->getEndereco()<<",";
        out <<novo_paciente->getCigarros()<<","<<novo_paciente->getRecuperacao()<<"\n";
    }

    file.close();
    delete novo_paciente;
    return true;

}

bool MainWindow::carregar_TurmaPac(QString name, Turma &x)
{
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }else{
        QTextStream in(&file);
        QString linha;
        novo_paciente = new Paciente;
        while(!in.atEnd()){
            linha = in.readLine();
            QStringList dados = linha.split(",");
            setarPaciente(dados, novo_paciente);
            x.inserirPaciente(*novo_paciente);
        }
    }
    file.close();
    delete novo_paciente;
    return true;
}


void MainWindow::on_ordenarPorCigarros_clicked()
{
    novo_paciente = new Paciente;
    turma_pacientes.ordenarPorCigarros();
    ui->tbl_turma->clearContents();
    for(int i = 0; i<turma_pacientes.totalDePacientes(); i++){
        novo_paciente = turma_pacientes.retornoPaciente(i);
        setTable(novo_paciente, i);
    }
}


void MainWindow::salvar()
{

    QString nome = QFileDialog::getSaveFileName(this,"Turma de Pacientes","","Texto Puro(*.txt);;Arquivos Separado por Vírgulas(*.csv)");
    if( salvar_TurmaPac(nome, turma_pacientes) ){
        QMessageBox::information(this, "Salvar Turma","Salvo com sucesso!");
    }else{
        QMessageBox::information(this, "Salvar turma","Infelizmente, não foi possível salvar os dados!");
    }

}

void MainWindow::carregar(){
    novo_paciente = new Paciente;
    QString nome = QFileDialog::getOpenFileName(this,"Turma de Pacientes", "", "Texto Puro(*.txt);;Arquivos Separados por Vírgulas(*.csv)");
    if(carregar_TurmaPac(nome, turma_pacientes)){
        ui->tbl_turma->clearContents();
        for(int i=0; i<turma_pacientes.totalDePacientes(); i++ ){
            if(i>=ui->tbl_turma->rowCount()){
                ui->tbl_turma->insertRow(i);
            }
            novo_paciente = turma_pacientes.retornoPaciente(i);
            setTable(novo_paciente, i);
        }
    }else{
        QMessageBox::information(this, "Carregar turma de pacientes","Infelizmente, não foi possível carregar os dados!");
    }
    atualizarEstatisticas();
}

void MainWindow::setarPaciente(QStringList paciente, Paciente *x)
{
    x->setNome(paciente[0]);
    x->setData_nas(paciente[1]);
    x->setNum_cartao(paciente[2]);
    x->setEndereco(paciente[3]);
    x->setCigarros(paciente[4].toInt());
    if(paciente[7]==0){
        x->setRecuperacao(false);
    } else{
        x->setRecuperacao(true);
    }
}

void MainWindow::on_tbl_turma_cellDoubleClicked(int row, int column)
{
    QString nome;
    if(column == 0){
        nome = QInputDialog::getText(this, "Editar", "Qual é o nome do pacinete?", QLineEdit::Normal);
    }else if(column == 1){
        nome = QInputDialog::getText(this, "Editar", "Qual é a data de nascimento do pacinete?", QLineEdit::Normal);
    }else if(column == 2){
        nome = QInputDialog::getText(this, "Editar", "Qual é o número do cartão do SUS do pacinete?", QLineEdit::Normal);
    }else if(column == 3){
        nome = QInputDialog::getText(this, "Editar", "Qual é o endereço do pacinete?", QLineEdit::Normal);
    }else if(column == 4){
        nome = QInputDialog::getText(this, "Editar", "Quantos cigarros o paciente fuma por dia?", QLineEdit::Normal);
    }else if(column == 6){
        nome = QInputDialog::getText(this, "Editar", "Deseja alterar a situação da recuperação do paciente? Digite Sim ou Não:", QLineEdit::Normal);
    }else{
        QMessageBox::information(this, "Editar", "Você não tem permissão para alterar a medicação!");   
    }
    turma_pacientes.mudarNaTurma(row, column, nome);
    for(int i=0; i<turma_pacientes.totalDePacientes(); i++){
        setTable(turma_pacientes.retornoPaciente(i), i);
    }
}
