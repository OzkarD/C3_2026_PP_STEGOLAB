#pragma once
#include <opencv2/opencv.hpp>

// Extraer mensaje desde una firma previamente localizada y validada.
// salida debe disponer de capacidad bytes. longitudSalida = bytes recuperados.
// No se exige terminador '\0': el mensaje puede contener bytes UTF-8.
bool extraerMensaje(const cv::Mat& imagen, long long posicion,unsigned char salida[], unsigned int capacidad,unsigned int& longitudSalida);

