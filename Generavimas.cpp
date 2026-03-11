#include "Generavimas.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <random>

void generuotiFaila()
{
	std::cout << "Įrašykite failo pavadinimą" << std::endl;
	std::string pav;

	while (true)
	{
		std::cin >> pav;
		std::ofstream write(pav);
		if (!write.is_open())
		{
			std::cerr << "Nepavyko sukurti failo. Bandykite iš naujo." << std::endl;
			continue;
		}

		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int> dist(1, 10);

		std::cout << "Įveskite studentų kiekį:" << std::endl;
		int kiekis;

		while (true)
		{
			std::cin >> kiekis;
			if (!std::cin)
			{
				std::cerr << "Neteisinga įvestis. Bandykite iš naujo." << std::endl;
				continue;
			}
		}

		for (int i = 0; i <= kiekis; i++)
		{
			write << "Vardas" << i << std::setw(10) << "Pavarde" << i;
			int ndkiek = dist(gen);
			for (int j = 0; j < ndkiek; j++)
			{
				write << std::setw(10) << dist(gen); //nd pazymiai
			}
			write << std::setw(10) << dist(gen) << std::endl; //egzo rezultatai
		}
	}
}