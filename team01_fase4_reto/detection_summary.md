# Resumen de Detección e Indicadores (IoCs)

## 1. Indicadores de Host
* **Archivo:** `team_payload.exe`
* **Comportamiento sospechoso:** Uso de `VirtualAlloc` para crear secciones de memoria privada (PRV).
* **Técnica MITRE ATT&CK:** T1055 (Process Injection / Dynamic Allocation).

## 2. Estrategia de Detección
Para detectar esta amenaza en un entorno corporativo, se recomienda:
1. **Monitoreo de EDR:** Alertar sobre procesos que llamen a `VirtualAlloc` con protecciones RWX.
2. **Reglas YARA:** Escanear la memoria de procesos en busca del patrón de descifrado identificado.

## 3. Veredicto
**Categoría:** Malware de Inyección / Loader.
**Nivel de Riesgo:** Alto (debido a su capacidad de ocultar strings y código ejecutable en memoria).