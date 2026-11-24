#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "stego_protocol.h"

using namespace std;
using namespace cv;

int main()
{
    cout << "=== CODIFICADOR STEG (LSB) ===\n";

    string ruta;
    cout << "Ruta de la imagen: ";
    getline(cin, ruta);
    ruta = "C:/Users/emito/Desktop/Ideas y Wallpapers/HCE_ConceptArt_Announce2025_001_1920x1080_Clean.jpg"; // Ruta predeterminada
    Mat imagen = imread(ruta, IMREAD_COLOR);
    if (imagen.empty())
    {
        cout << "ERROR: no se pudo abrir la imagen.\n";
        return 1;
    }

    long long capacidadBits = (long long)imagen.rows * imagen.cols * 3;
    long long bytesUtiles = (capacidadBits / 8) - 8;

    cout << "\nImagen: " << imagen.rows << "x" << imagen.cols << " | Capacidad: " << capacidadBits << " bits (" << bytesUtiles << " bytes utiles)\n";

    string mensaje;
    cout << "\nMensaje a ocultar: ";
    getline(cin, mensaje);

    if (mensaje.empty())
    {
        cout << "ERROR: mensaje vacio.\n";
        return 1;
    }

    long long longitud = mensaje.size();
    long long bitsNecesarios = (8 + longitud) * 8; // 4 bytes STEG + 4 longitud + mensaje

    if (bitsNecesarios > capacidadBits)
    {
        cout << "ERROR: el mensaje no cabe en la imagen.\n";
        return 1;
    }

    int opcion;
    cout << "\nModo de posicion:\n";
    cout << " 1. STEG al inicio (posicion 0)\n";
    cout << " 2. STEG en posicion aleatoria\n";
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore(); // Limpia el salto de linea pendiente

    long long posInicio = 0;
    if (opcion == 2)
    {
        srand((unsigned int)time(NULL));
        long long maxStart = capacidadBits - bitsNecesarios;
        posInicio = (long long)rand() % (maxStart + 1);
        cout << "Posicion aleatoria elegida.\n";
    }
    else if (opcion != 1)
    {
        cout << "Opcion invalida.\n";
        return 1;
    }

    Mat modificada = imagen.clone();
    long long pos = posInicio;

    // 1. Escribir firma "STEG" (4 bytes)
    const char firma[] = "STEG";
    for (int i = 0; i < 4; i++)
    {
        ocultarByte(modificada, pos, firma[i]);
    }

    // 2. Escribir longitud del mensaje en 4 bytes (big-endian)
    unsigned int tamano = (unsigned int)longitud;
    for (int i = 3; i >= 0; i--)
    {
        unsigned char b = (tamano >> (i * 8)) & 0xFF;
        ocultarByte(modificada, pos, b);
    }

    // 3. Escribir el mensaje
    for (long long i = 0; i < longitud; i++)
    {
        ocultarByte(modificada, pos, mensaje[i]);
    }

    cout << "\n=== RESUMEN ===\n";
    mostrarUbicacion(posInicio, imagen.cols, "STEG");
    mostrarUbicacion(posInicio + 32, imagen.cols, "Longitud");
    mostrarUbicacion(posInicio + 64, imagen.cols, "Mensaje");
    cout << "Bits totales usados: " << bitsNecesarios << "\n";

    string salida;
    cout << "\nArchivo de salida (default: Foto_STEG.png): ";
    getline(cin, salida);

    if (salida.empty())
    {
        salida = "Foto_STEG.png";
    }
    if (salida.size() < 4 || salida.substr(salida.size() - 4) != ".png")
    {
        salida += ".png";
    }

    if (!imwrite(salida, modificada))
    {
        cout << "ERROR: no se pudo guardar.\n";
        return 1;
    }

    cout << "Guardado en: " << salida << "\n";
    return 0;
}

// Escribe 1 bit en el LSB del canal correspondiente (B, G, R)
void escribirBit(Mat& imagen, long long posicion, int bit)
{
    long long pixel = posicion / 3;
    int canal = posicion % 3;
    int fila = pixel / imagen.cols;
    int columna = pixel % imagen.cols;

    Vec3b& color = imagen.at<Vec3b>(fila, columna);
    color[canal] = (color[canal] & 0xFE) | (bit & 1);
}

// Escribe 1 byte completo (8 bits, del bit 7 al 0)
void ocultarByte(Mat& imagen, long long& posicion, unsigned char dato)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (dato >> i) & 1;
        escribirBit(imagen, posicion, bit);
        posicion++;
    }
}

// Muestra en consola en qué píxel y canal cae un bit dado
void mostrarUbicacion(long long bitPos, int cols, const char* etiqueta)
{
    long long pixel = bitPos / 3;
    int canal = bitPos % 3;
    int fila = pixel / cols;
    int columna = pixel % cols;

    const char* nombresCanal[] = { "B", "G", "R" };
    cout << etiqueta << ": bit " << bitPos << " | pixel (" << fila << "," << columna << ")" << " | canal " << nombresCanal[canal] << "\n";
}


//EJEMPLO

/*
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int main()
{
    cv::Mat img = cv::imread("C:/Users/emito/Desktop/Ideas y Wallpapers/HCE_ConceptArt_Announce2025_001_1920x1080_Clean.jpg");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}

*/