#include <iostream>
#include <fstream>
#include <ctime>

constexpr unsigned int IMAGE_HEIGHT = 25;
constexpr unsigned int IMAGE_WIDTH = 25;

struct Color {
	short r;
	short g;
	short b;
};

void saveColoredImage();
void showColoredImage();

int main(int argc, char** argv) {
	std::srand(std::time(nullptr));

	saveColoredImage();
	showColoredImage();

	return 0;
}

void saveColoredImage() {
	std::ofstream save;

	// cria uma matriz dinâmica
	Color color[IMAGE_WIDTH][IMAGE_HEIGHT]{};

	// abre o arquivo para escrita em modeo binário
	save.open("image.color", std::ios_base::out | std::ios_base::app | std::ios_base::binary);

	// verifica se o arquivo foi aberto corretamente
	if (!save.is_open()) {
		std::cerr << "Failed to open the file.\n";
		return;
	}

	// preenche a matriz com cores
	for (int i = 0; i < IMAGE_WIDTH; i++) {
		std::cout << "#" << (i + 1) << ": ";
		for (int j = 0; j < IMAGE_HEIGHT; j++) {
			color[i][j].r = std::rand() % 255;
			color[i][j].g = std::rand() % 255;
			color[i][j].b = std::rand() % 255;
		}
	}
	// salva os dados no arquivo binário
	save.write((char*)color, sizeof(Color) * IMAGE_HEIGHT * IMAGE_WIDTH);

	// fecha o arquivo
	save.close();
}

void showColoredImage() {
	std::ifstream fread;

	// lendo os dados do arquivo binário
	fread.open("image.color", std::ios_base::in | std::ios_base::binary);

	// verifica se o arquivo foi aberto corretamente
	if (!fread.is_open()) {
		std::cerr << "Failed to open the file.\n";
		return;
	}

	Color color[IMAGE_WIDTH][IMAGE_HEIGHT]{};


	fread.read((char*)color, sizeof(Color) * IMAGE_HEIGHT * IMAGE_HEIGHT);
	fread.close();

	char colort[12] = "\033[48;5;cccm";

	for (int i = 0; i < IMAGE_WIDTH; i++) {
		for (int j = 0; j < IMAGE_HEIGHT; j++) {
			colort[7] = color[i][j].r;
			colort[8] = color[i][j].g;
			colort[9] = color[i][j].b;

			std::cout << colort << ' ';
		}
		std::cout << "\033[m\n";
	}
}