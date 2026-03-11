#include "Generavimas.h"

#include <iostream>
#include <iomanip>
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
			break;
		}

		int ndkiek = dist(gen);
		write << std::left << std::setw(15) << "Vardas" << std::right << std::setw(15) << "Pavarde";

		for (int i = 0; i <= ndkiek; i++)
		{
			write << std::right << std::setw(15) << ("ND" + std::to_string(i));
		}

		write << std::right << std::setw(15) << "Egz." << std::endl;

		for (int i = 0; i <= kiekis; i++)
		{
			write << std::left << std::setw(15) << ("Vardas" + std::to_string(i)) << std::right << std::setw(15) << ("Pavarde" + std::to_string(i));
			for (int j = 0; j < ndkiek; j++)
			{
				write << std::right << std::setw(15) << dist(gen); //nd pazymiai
			}
			write << std::right << std::setw(15) << dist(gen) << std::endl; //egzo rezultatai
		}
		break;
	}
}
