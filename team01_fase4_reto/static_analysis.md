# Reporte de Análisis Estático: team_payload.exe

## 1. Objetivo del Análisis
El objetivo de esta fase es examinar el binario `team_payload.exe` sin ejecutar su código, con el fin de identificar indicadores de compromiso (IoCs), cadenas de texto sospechosas y funciones de la API de Windows que sugieran un comportamiento malicioso o de evasión.

## 2. Información del Binario
* **Nombre del archivo:** team_payload.exe
* **Formato:** Portable Executable (PE) x32.
* **Herramientas utilizadas:** Ghidra.

## 3. Hallazgos en Cadenas de Texto (Strings)
Se realizó una búsqueda exhaustiva de cadenas legibles dentro del binario utilizando el buscador de Ghidra.

* **Resultado:** No se encontraron referencias directas a la cadena "calculadora".
* **Interpretación:** La ausencia de esta cadena, a pesar de ser el objetivo del programa, confirma que el mensaje se encuentra **ofuscado o cifrado** dentro de los datos del binario (técnica de evasión de análisis estático).
* **Cadenas detectadas:** Se identificaron mensajes de depuración como "[+] Iniciando simulacion..." y "[+] Memoria RWX reservada en:", lo que confirma que el programa interactúa directamente con la memoria dinámica.

> **[INSERTAR AQUÍ: Captura de Ghidra buscando 'calculadora' en la ventana Defined Strings]**

## 4. Análisis de la Tabla de Importaciones (Imports)
El análisis de las librerías vinculadas dinámicamente revela el uso de funciones críticas para la manipulación de memoria:

| Función | Librería | Propósito Sospechoso |
| :--- | :--- | :--- |
| VirtualAlloc | kernel32.dll | Reserva de memoria dinámica fuera de las secciones estándar. |
| VirtualProtect | kernel32.dll | Cambio de permisos en tiempo de ejecución (posible escalación a RWX). |

**Conclusión del análisis de Imports:** El binario tiene la capacidad técnica de inyectar o ejecutar código en regiones de memoria recién creadas, un comportamiento característico de stagers o droppers.

> **[INSERTAR AQUÍ: Captura de Ghidra en Symbol Tree -> Imports mostrando VirtualAlloc]**

## 5. Resumen de Riesgos
1.  **Ofuscación de Datos:** El payload principal no es visible mediante inspección estática.
2.  **Manipulación de Memoria:** El uso de VirtualAlloc indica que el binario cargará contenido adicional en la RAM durante su ejecución.