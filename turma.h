#ifndef TURMA_H
#define TURMA_H

#include <QObject>
#include "paciente.h"
#include <QVector>
#include <algorithm>
#include <numeric>

class Turma
{
public:
    Turma();
    void inserirPaciente(Paciente x);
    float mediaDeCigarros();
    int totalDePacientes();
    int totalDeAbandonoCigarro();
    void ordenarPorNome();
    void ordenarPorCigarros ();
    Paciente* retornoPaciente (int i);
    void mudarNaTurma(int i, int j, QString x);

private:
    QVector <Paciente> turma;

};

#endif // TURMA_H
