# Reporte Final de Análisis de Malware: team_payload.exe

**Fecha:** 6 de Mayo, 2026  
**Institución:** Universidad Autónoma de Nuevo León (UANL)  
**Facultad:** Facultad de Ciencias Físico Matemáticas (FCFM)  
**Materia:** Programación Avanzada para Ciberseguridad  

---

## 1. Resumen Ejecutivo
Se presenta el análisis técnico del binario `team_payload.exe`. El objetivo primordial fue identificar sus capacidades de evasión y extraer el contenido de un payload oculto. Mediante un análisis híbrido, se determinó que el archivo es un **Loader** que utiliza técnicas de inyección de memoria y cifrado XOR para ocultar indicadores de compromiso (IoCs).

## 2. Metodología de Análisis
Para el estudio del espécimen, se siguió el siguiente flujo de trabajo:
1.  **Análisis Estático:** Uso de Ghidra para inspeccionar la tabla de símbolos y búsqueda de strings.
2.  **Análisis Dinámico:** Uso de x32dbg para el monitoreo de la API de Windows y dump de memoria.
3.  **Identificación de Capacidades:** Uso de la base de conocimientos de CAPA y MITRE ATT&CK.

## 3. Resultados del Análisis Estático
El análisis inicial reveló que el binario está diseñado para ser "silencioso":
* **Strings:** No se detectaron cadenas legibles que indicaran la función final del programa (ej. "calculadora").
* **Importaciones:** Se identificó la importación de `VirtualAlloc` y `VirtualProtect` en `kernel32.dll`, lo que sugirió inmediatamente la manipulación de memoria en tiempo de ejecución.

## 4. Resultados del Análisis Dinámico
Durante la depuración en x32dbg, se lograron los siguientes hitos:
* **Intercepción:** Se detuvo la ejecución en la llamada a `VirtualAlloc`.
* **Asignación de Memoria:** El sistema asignó la dirección de memoria **0053F96C** (almacenada en el registro **EAX**).
* **Mapa de Memoria:** Se verificó la creación de una sección de memoria privada con protección inicial **RW** (Read/Write).
* **Descifrado:** Se observó un bucle XOR que procesó los datos cifrados del binario y los escribió en la memoria recién reservada, revelando el string final.

## 5. Matriz de Indicadores de Compromiso (IoCs)
| Tipo de Indicador | Valor / Descripción |
| :--- | :--- |
| **Nombre de Archivo** | team_payload.exe |
| **Técnica MITRE** | T1055 (Process Injection) / T1027 (Obfuscation) |
| **API Crítica** | VirtualAlloc |
| **Payload Extraído** | "calculadora" |

## 6. Conclusión
El binario `team_payload.exe` representa un ejemplo clásico de malware persistente en memoria. Al no escribir archivos adicionales en disco y cifrar sus strings, logra evadir escaneos antivirus tradicionales. La detección exitosa solo fue posible mediante el análisis de la memoria RAM y la intercepción de las funciones de bajo nivel del sistema operativo.