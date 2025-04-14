#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

#define N 100  // Número máximo de palabras

struct Traduccion {
    wstring esp, ita, fra, ale, eng;
    bool lleno = false;
};

Traduccion trad[N];

void guardarEnArchivo() {
    wofstream archivo("Palabras/Palabrasarchivadasdoc.txt");
    archivo.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!archivo) {
        wcout << L"\nNo se pudo abrir el archivo para escritura." << endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (trad[i].lleno) {
            archivo << trad[i].esp << L'\t' << trad[i].ita << L'\t'
                << trad[i].fra << L'\t' << trad[i].ale << L'\t'
                << trad[i].eng << endl;
        }
    }

    archivo.close();
    wcout << L"\nArchivo actualizado correctamente." << endl;
}

void cargarDesdeArchivo() {
    wifstream archivo("Palabras/Palabrasarchivadasdoc.txt");
    archivo.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!archivo) {
        wcout << L"\nNo se pudo abrir el archivo." << endl;
        return;
    }

    int i = 0;
    while (i < N && archivo.good()) {
        wstring linea;
        getline(archivo, linea);
        if (linea.empty()) continue;

        wstringstream ss(linea);
        getline(ss, trad[i].esp, L'\t');
        getline(ss, trad[i].ita, L'\t');
        getline(ss, trad[i].fra, L'\t');
        getline(ss, trad[i].ale, L'\t');
        getline(ss, trad[i].eng);

        trad[i].lleno = true;
        i++;
    }

    archivo.close();
    wcout << L"\nDatos cargados exitosamente." << endl;
}

void mostrarTabla() {
    wcout << L"\n--- Tabla de Traducciones ---" << endl;
    wcout << setw(20) << L"ESP" << setw(20) << L"ITAL" << setw(20) << L"FRANC"
        << setw(20) << L"ALM" << setw(20) << L"INGL" << endl;
    wcout << L"--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        if (trad[i].lleno) {
            wcout << setw(20) << trad[i].esp << setw(20) << trad[i].ita
                << setw(20) << trad[i].fra << setw(20) << trad[i].ale
                << setw(20) << trad[i].eng << endl;
        }
    }
}

void buscarTraduccion() {
    wstring palabra;
    wcout << L"Ingrese la palabra en ESP que desea traducir: ";
    getline(wcin, palabra);

    for (int i = 0; i < N; i++) {
        if (trad[i].lleno && trad[i].esp == palabra) {
            wcout << L"\nTraducción para: " << palabra << endl;
            wcout << L"ITAL: " << trad[i].ita << endl;
            wcout << L"FRAN: " << trad[i].fra << endl;
            wcout << L"ALEM: " << trad[i].ale << endl;
            wcout << L"INGL: " << trad[i].eng << endl;
            return;
        }
    }
    wcout << L"La palabra no fue encontrada." << endl;
}

void agregarPalabra() {
    for (int i = 0; i < N; i++) {
        if (!trad[i].lleno) {
            wcout << L"\nIngrese la nueva palabra en ESP: ";
            getline(wcin, trad[i].esp);
            wcout << L"Ingrese la traducción en ITAL: ";
            getline(wcin, trad[i].ita);
            wcout << L"Ingrese la traducción en FRANC: ";
            getline(wcin, trad[i].fra);
            wcout << L"Ingrese la traducción en ALEM: ";
            getline(wcin, trad[i].ale);
            wcout << L"Ingrese la traducción en INGL: ";
            getline(wcin, trad[i].eng);

            trad[i].lleno = true;
            guardarEnArchivo();
            wcout << L"\nPalabra agregada exitosamente." << endl;
            return;
        }
    }
    wcout << L"No hay más espacio para agregar palabras." << endl;
}

void eliminarPalabra() {
    wstring palabra;
    wcout << L"Ingrese la palabra en ESP que desea eliminar: ";
    getline(wcin, palabra);

    bool encontrada = false;
    for (int i = 0; i < N; i++) {
        if (trad[i].lleno && trad[i].esp == palabra) {
            trad[i].lleno = false;
            encontrada = true;
            break;
        }
    }

    if (encontrada) {
        guardarEnArchivo();
        wcout << L"\nPalabra eliminada correctamente." << endl;
    }
    else {
        wcout << L"\nPalabra no encontrada." << endl;
    }
}

void mostrarMenu() {
    int opcion;
    do {
        wcout << L"\n--- Menu ---\n";
        wcout << L"1. Buscar traduccion\n";
        wcout << L"2. Mostrar todas las traducciones\n";
        wcout << L"3. Agregar nueva palabra\n";
        wcout << L"4. Eliminar una palabra\n";
        wcout << L"5. Salir\n";
        wcout << L"Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: buscarTraduccion(); break;
        case 2: mostrarTabla(); break;
        case 3: agregarPalabra(); break;
        case 4: eliminarPalabra(); break;
        case 5: wcout << L"Saliendo..." << endl; break;
        default: wcout << L"Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cargarDesdeArchivo();  // Se carga el archivo automáticamente al iniciar

    mostrarMenu();
    return 0;
}
