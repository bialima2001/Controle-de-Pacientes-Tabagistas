#include "paciente.h"

Paciente::Paciente()
{

}


bool Paciente::getRecuperacao() const
{
    return recuperacao;
}

void Paciente::setRecuperacao(bool value)
{
    recuperacao = value;
}

QString Paciente::getTratamento() const
{
    return tratamento;
}

void Paciente::setTratamento()
{
    if(getCigarros() <= 4 && getCigarros() >0){
        tratamento = "Adesivo de Nicotina de 7 mg";
    }else if(getCigarros() < 15 && getCigarros()>4){
        tratamento = "Adesivo de Nicotina de 14 mg";
    }else if(getCigarros()  >= 15 && getCigarros() < 25){
        tratamento = "Adesivo de Nicotina de 21 mg";
    }else if(getCigarros() >= 25){
        tratamento = "Adesivo de Nicotina de 21 mg, comprimido Bup de 150 mg";
    }
}

float Paciente::getCigarros() const
{
    return cigarros;
}

void Paciente::setCigarros(float value)
{
    cigarros = value;
    setTratamento();
}

QString Paciente::getData_nas() const
{
    return data_nas;
}

void Paciente::setData_nas(const QString &value)
{
    data_nas = value;
}

QString Paciente::getNum_cartao() const
{
    return num_cartao;
}

void Paciente::setNum_cartao(const QString &value)
{
    num_cartao = value;
}

QString Paciente::getEndereco() const
{
    return endereco;
}

void Paciente::setEndereco(const QString &value)
{
    endereco = value;
}

QString Paciente::getNome() const
{
    return nome;
}

void Paciente::setNome(const QString &value)
{
    nome = value;
}
