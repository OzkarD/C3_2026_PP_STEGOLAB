# STEGOLAB — Proyecto inicial

**Curso:** Programacion en Paralelo  
**Modalidad:** equipos de tres integrantes  
**Tecnologias:** C++ basico, OpenCV, `std::thread`, Visual Studio 2022

## Proposito

Este repositorio contiene **solamente la estructura y los prototipos** de los modulos.


## Contrato comun de datos

- Imagen PNG cargada en OpenCV como `CV_8UC3` (BGR, 8 bits por canal).
- Indice lineal de componente: primero B, luego G, luego R; recorrer por filas.
- Cada componente aporta el bit menos significativo (LSB).
- La firma `STEG` ocupa 4 bytes ASCII, MSB primero.
- Los siguientes 4 bytes indican la longitud del mensaje, entero sin signo big-endian.
- A continuacion aparecen exactamente `longitud` bytes de mensaje UTF-8.
- La firma puede comenzar en **cualquier componente** de la imagen.
- Los indices de posicion son de tipo `long long`; la longitud es `unsigned int`.
- Si existen varios candidatos validos, ambas busquedas deben devolver la **menor posicion**.
- Una firma coincidente requiere validar que la longitud y el bloque completo quepan.

## Reparto de tareas

| Alumno | Archivos principales | Responsabilidad |
|---|---|---|
| A | `stego_protocol.*`, `stego_decoder.*` | LSB, firma, longitud y extraccion |
| B | `stego_search.*` | Busqueda exhaustiva secuencial y con `std::thread` |
| C (integrador) | `main.cpp`, `benchmark.*` | Consola, mediciones, integracion y pruebas |

Todos deben desarrollar y probar codigo. Acordar interfaces antes de modificar prototipos.

## Como iniciar en Visual Studio 2022 - 2026

1. Crear un proyecto **Aplicacion de consola C++** vacio, plataforma **x64**.
2. Agregar los `.cpp` de `src/` y configurar `include/` en **Directorios de inclusion adicionales**.
5. Implementar gradualmente cada modulo y probar en **Release | x64**.


## Flujo Git propuesto

- `main`: version estable; no subir cambios directamente.
- `feature/protocolo-decoder`: Alumno A.
- `feature/busqueda`: Alumno B.
- `feature/integracion-benchmark`: Alumno C.
- Abrir un pull request por funcionalidad, solicitar revision y conservar evidencia de pruebas.

## Pruebas minimas

- Imagen sin firma: informar que no se encontro mensaje.
- Firma valida y mensaje corto: recuperar bytes exactos.
- Firma cerca del limite de un bloque de hilos: no perder candidatos.
- Longitud invalida o bloque incompleto: rechazar de manera segura.
- Busquedas secuencial y paralela: misma posicion y mismos bytes.
- Benchmarks: 1, 2, 4 y 8 hilos, 10 repeticiones, mediana, speedup y eficiencia.

## Defensa

Se recibiran cinco imagenes PNG ineditas con mensajes ocultos en posiciones desconocidas.
El equipo debera recuperar cada mensaje y mostrar la comparacion secuencial/paralela.
Consultar el documento de especificacion oficial para criterios completos.
