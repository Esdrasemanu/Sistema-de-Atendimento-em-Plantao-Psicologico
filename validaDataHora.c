#include "validaDataHora.h"

// MANTIDO do código antigo
int validarData(const char* data) {
    int d, m, a;
    if (!data || strlen(data) != 10) return 0;
    if (sscanf(data, "%2d/%2d/%4d", &d, &m, &a) != 3) return 0;
    if (d < 1 || d > 31 || m < 1 || m > 12 || a < 1900) return 0;
    // Meses normais (30 dias)
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    // Validação de fevereiro e ano bissexto
    if (m == 2) {
        int bissexto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
        if (d > 29 || (d == 29 && !bissexto)) return 0;
    }
    return 1;
}

// MANTIDO do código antigo
int validarHora(const char* hora) {
    int h, m;
    if (!hora || strlen(hora) != 5) return 0;
    if (sscanf(hora, "%2d:%2d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23 || m < 0 || m > 59) return 0;
    return 1;
}

// NOVA função - valida data futura
int validarDataFutura(const char* data) {
    // Primeiro valida o formato básico
    if (!validarData(data)) {
        return 0;
    }
    
    // Extrai dia, mês e ano
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    
    // Verifica se a data não é passada
    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);
    
    struct tm data_verificar = {0};
    data_verificar.tm_mday = dia;
    data_verificar.tm_mon = mes - 1;
    data_verificar.tm_year = ano - 1900;
    // Define para meio-dia para evitar problemas de timezone
    data_verificar.tm_hour = 12;
    
    time_t timestamp_verificar = mktime(&data_verificar);
    
    return timestamp_verificar >= agora;
}

// NOVA função - valida intervalos de 15 minutos
int validarHoraIntervalo(const char* hora) {
    // Primeiro valida o formato básico
    if (!validarHora(hora)) {
        return 0;
    }
    
    int horas, minutos;
    sscanf(hora, "%d:%d", &horas, &minutos);
    
    // Valida intervalos de 15 minutos
    if (minutos % 15 != 0) {
        return 0;
    }
    
    return 1;
}

// NOVA função - valida data/hora futura
int ehDataHoraFutura(const char* data, const char* hora) {
    if (!validarDataFutura(data) || !validarHoraIntervalo(hora)) {
        return 0;
    }
    
    int dia, mes, ano, horas, minutos;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    sscanf(hora, "%d:%d", &horas, &minutos);
    
    time_t agora = time(NULL);
    struct tm data_hora_verificar = {0};
    data_hora_verificar.tm_mday = dia;
    data_hora_verificar.tm_mon = mes - 1;
    data_hora_verificar.tm_year = ano - 1900;
    data_hora_verificar.tm_hour = horas;
    data_hora_verificar.tm_min = minutos;
    
    time_t timestamp_verificar = mktime(&data_hora_verificar);
    
    return timestamp_verificar > agora;
}