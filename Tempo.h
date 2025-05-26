//
// Created by migue on 12/05/2025.
//

#ifndef TEMPO_H
#define TEMPO_H

class Tempo {
    int dia;
    int mes;
    int ano;

public:
    Tempo(int dia, int mes, int ano) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }

    string toString() {
        return to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);
    }

     bool isEqual(Tempo tempo) {
        if (tempo.dia != this->dia) {return false;}
        if (tempo.mes != this->mes) {return false;}
        if (tempo.ano != this->ano) {return false;}
        return true;
    }
    static bool isMenorOuIgual(const Tempo& a, const Tempo& b) {
        if (a.ano != b.ano) return a.ano < b.ano;
        if (a.mes != b.mes) return a.mes < b.mes;
        return a.dia <= b.dia;
    }

    static bool isMaiorOuIgual(const Tempo& a, const Tempo& b) {
        if (a.ano != b.ano) return a.ano > b.ano;
        if (a.mes != b.mes) return a.mes > b.mes;
        return a.dia >= b.dia;
    }
    // 12/05/2025  // 15/05/2025
    // 20/05/2025  // 25/05/2025
    static bool isBetween(const Tempo& inicioA, const Tempo& fimA,
                       const Tempo& inicioB, const Tempo& fimB) {
        return isMenorOuIgual(inicioA, fimB) && isMaiorOuIgual(fimA, inicioB);
    }

    static int diasAte(const Tempo& ta, const Tempo& tb) {
        tm a = {0,0,0, tb.dia, tb.mes - 1, tb.ano - 1900};
        tm b = {0,0,0, ta.dia, ta.mes - 1, ta.ano - 1900};
        time_t x = mktime(&a);
        time_t y = mktime(&b);
        double diff = difftime(y, x) / (60 * 60 * 24);
        return (int) diff;
    }

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }
    void setDia(int dia) { this->dia = dia; }
    void setMes(int mes) { this->mes = mes; }
    void setAno(int ano) { this->ano = ano; }
};

#endif //TEMPO_H
