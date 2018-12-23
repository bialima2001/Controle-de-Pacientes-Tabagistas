#ifndef PACIENTE_H
#define PACIENTE_H

#include <QObject>
#include <QVector>

class Paciente
{
public:
    Paciente();


    QString getNome() const;
    void setNome(const QString &value);

    QString getEndereco() const;
    void setEndereco(const QString &value);

    QString getNum_cartao() const;
    void setNum_cartao(const QString &value);

    QString getData_nas() const;
    void setData_nas(const QString &value);

    float getCigarros() const;
    void setCigarros(float value);

    bool getRecuperacao() const;
    void setRecuperacao(bool value);

    QString getTratamento() const;
    void setTratamento();

private:

    QString nome;
    QString endereco;
    QString num_cartao;
    QString data_nas;
    float cigarros;
    QString tratamento;
    bool recuperacao;

};

#endif // PACIENTE_H
