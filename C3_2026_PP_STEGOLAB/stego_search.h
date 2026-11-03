#pragma once
#include <opencv2/opencv.hpp>

// Buscar exhaustivamente todas las posiciones candidatas.
// Retornar true si se encuentra un bloque valido; posicion = indice inicial.
// Si hay mas de uno, devolver la posicion valida mas pequena.
bool buscarSecuencial(const cv::Mat& imagen, long long& posicion);

// Misma salida que buscarSecuencial, utilizando std::thread.
// numHilos debe ser mayor o igual que 1.
bool buscarParalelo(const cv::Mat& imagen, int numHilos, long long& posicion);
