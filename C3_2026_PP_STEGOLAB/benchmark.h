#pragma once
#include <opencv2/opencv.hpp>

// Medir SOLO la busqueda (sin imread, cout ni escritura de archivos).
// Repetir numRepeticiones veces y devolver la mediana en milisegundos.
// Retornar false si algun resultado de busqueda es inconsistente.
bool medirSecuencial(const cv::Mat& imagen, int numRepeticiones,double& medianaMs, long long& posicion);
bool medirParalelo(const cv::Mat& imagen, int numHilos,int numRepeticiones, double& medianaMs,long long& posicion);
double calcularSpeedup(double tiempoSecuencial, double tiempoParalelo);
double calcularEficiencia(double speedup, int numHilos);

