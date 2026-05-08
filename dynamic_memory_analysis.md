# Reporte de Análisis Dinámico de Memoria: team_payload.exe

## 1. Objetivo del Análisis
Observar el comportamiento del proceso en tiempo de ejecución utilizando el depurador x32dbg para identificar la reserva de memoria dinámica, la modificación de permisos y la extracción del payload descifrado.

## 2. Intercepción de la API de Windows
Se configuró un punto de interrupción (breakpoint) en la función VirtualAlloc de kernel32.dll para detectar el momento exacto en que el programa solicita memoria al sistema operativo.

* **Estado:** El programa se detiene justo antes de realizar el salto (jmp) a la implementación real de la función.

> **[INSERTAR AQUÍ: Captura de x32dbg con la flecha de ejecución en el jmp a VirtualAlloc]**

## 3. Análisis de Registros y Valor de Retorno
Tras ejecutar la función (Step Over / F8), el registro **EAX** contiene la dirección base de la memoria recién asignada.

* **Dirección de memoria detectada:** (Aquí pon el valor de EAX que te salió, ej: 0053F96C).
* **Interpretación:** Este valor es el puntero a la nueva sección de memoria creada específicamente para el payload.

> **[INSERTAR AQUÍ: Captura de x32dbg mostrando el Panel de Registros con el valor de EAX resaltado]**

## 4. Inspección del Memory Map y Permisos
Al revisar la dirección obtenida en la pestaña **Memory Map**, se verificaron los permisos asignados a esa región.

* **Tipo de memoria:** PRV (Private).
* **Protección detectada:** Se observaron permisos **RW** (Read/Write) iniciales, necesarios para escribir el payload descifrado antes de su ejecución.

> **[INSERTAR AQUÍ: Captura de la pestaña Memory Map con la fila de la dirección de EAX resaltada]**

## 5. Extracción del Payload (Dump)
Mediante la función "Follow in Dump" sobre el registro EAX, se inspeccionó el contenido de la memoria después de que el programa avanzara en su ejecución.

* **Resultado:** Se logró visualizar en el dump el contenido descifrado.
* **Hallazgo:** El payload confirma la intención del programa de ejecutar acciones ocultas al análisis estático inicial.

> **[INSERTAR AQUÍ: Captura de la ventana Dump donde se alcancen a ver los bytes del payload]**