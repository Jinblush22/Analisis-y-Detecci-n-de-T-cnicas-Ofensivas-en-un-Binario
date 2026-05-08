#include <windows.h>
#include <iostream>
#include <vector>

void decryptMessage(char* data, size_t dataLen, char key) {
	for (size_t i = 0; i < dataLen; i++) {
		data[i] ^= key;
	}
}

int main() {
	char encryptedMsg[] = { 0x01, 0x23, 0x2e, 0x21, 0x37, 0x2e, 0x23, 0x26, 0x2d, 0x30, 0x23, 0x00 };
	char key = 0x42;
	decryptMessage(encryptedMsg, sizeof(encryptedMsg) - 1, key);

	std::cout << "[+] Inciando simulacion..." << std::endl;

	LPVOID remoteBuffer = VirtualAlloc(NULL, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (remoteBuffer != NULL) {
		std::cout << "[+] Memoria RWX reservada en: " << remoteBuffer << std::endl;

		const char* dummyPayload = "Simulacion de Payload";
		memcpy(remoteBuffer, dummyPayload, strlen(dummyPayload));
	}

	std::cout << "[+] Proceso completado. Presiona Enter para salir." << std::endl;
	std::cin.get();

	if (remoteBuffer) VirtualFree(remoteBuffer, 0, MEM_RELEASE);

	return 0;
}