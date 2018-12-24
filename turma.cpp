#include "turma.h"

Turma::Turma()
{

}


void Turma::inserirPaciente(Paciente x)
{
    turma.push_back(x);
}

float Turma::mediaDeCigarros()
{
    return std::accumulate(turma.begin(), turma.end(),0.0, [](float acumulador, Paciente x){return acumulador+=x.getCigarros();})/turma.size();
}

int Turma::totalDePacientes()
{
    return turma.size();
}

int Turma::totalDeAbandonoCigarro()
{
    int acumulador = 0;
    for(int i=0; i<turma.size(); i++){
        if(turma[i].getRecuperacao()){
            acumulador++;
        }
    }
    return acumulador;
}

void Turma::ordenarPorNome()
{
    std::sort(turma.begin(), turma.end(), [](Paciente a, Paciente b){return a.getNome()<b.getNome();});
}

void Turma::ordenarPorCigarros()
{
    std::sort(turma.begin(), turma.end(), [](Paciente a, Paciente b){return a.getCigarros()<b.getCigarros();});
}

Paciente* Turma::retornoPaciente(int i)
{
    return &turma[i];
}

void Turma::mudarNaTurma(int i, int j, QString x)
{
    if(j==0){
        turma[i].setNome(x);
    }else if(j==1){
        turma[i].setData_nas(x);
    }else if(j==2){
        turma[i].setNum_cartao(x);
    }else if(j==3){
        turma[i].setEndereco(x);
    }else if(j==4){
        turma[i].setCigarros(x.toInt());
        turma[i].setTratamento();
    }else if(j==6){
        if(x=="sim" or x=="Sim" or x=="SIM"){
            if(turma[i].getRecuperacao()){
                turma[i].setRecuperacao(false);
            }else{
                turma[i].setRecuperacao(true);
            }
        }
}

