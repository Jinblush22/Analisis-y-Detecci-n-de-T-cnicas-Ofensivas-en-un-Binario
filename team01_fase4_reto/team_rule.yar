rule Team_Payload_Detection {
    meta:
        description = "Regla para detectar el cargador de payload con cifrado XOR y reserva de memoria RWX"
        author = "Grupo 1"
        date = "2026-05-06"
        context = "T4 - Programación Avanzada para Ciberseguridad"

    strings:
        // 1. El mensaje cifrado que tienes en el array encryptedMsg
        // { 0x01, 0x23, 0x2e, 0x21, 0x37, 0x2e, 0x23, 0x26, 0x2d, 0x30, 0x23 }
        $encrypted_data = { 01 23 2E 21 37 2E 23 26 2D 30 23 }

        // 2. Las cadenas de texto que imprimes en consola
        $s1 = "[+] Inciando simulacion..."
        $s2 = "[+] Memoria RWX reservada en:"
        $s3 = "Simulacion de Payload"

        // 3. Para la función VirtualAlloc con permisos PAGE_EXECUTE_READWRITE (0x40)
        // Esto busca la configuración de memoria que pusiste en tu script
        $rwx_allocation = { 00 04 00 00 40 00 00 00 } 

    condition:
        // Ver que sea un ejecutable (MZ) y que contenga los mensajes o la data cifrada
        uint16(0) == 0x5A4D and ($encrypted_data or 2 of ($s*))
}
