#pragma once
#include <opencv2/opencv.hpp>

// Contrato: indice = posicion de componente B/G/R, comenzando en cero.
// Orden de recorrido: filas, columnas, B-G-R. Un bit por componente.
// Retornar false cuando la posicion no sea valida.
bool leerBitLSB(const cv::Mat& imagen, long long posicion, int& bit);

// Reconstruir 8 bits consecutivos (MSB primero).
bool leerByte(const cv::Mat& imagen, long long posicion, unsigned char& valor);

// Comprobar la firma ASCII "STEG" (4 bytes = 32 bits).
bool verificarFirma(const cv::Mat& imagen, long long posicion);

// Leer longitud de 4 bytes sin signo en orden big-endian.
bool leerLongitud(const cv::Mat& imagen, long long posicion, unsigned int& longitud);

// Comprobar que cabecera y mensaje caben desde posicion.
bool validarBloque(const cv::Mat& imagen, long long posicion, unsigned int longitud);
