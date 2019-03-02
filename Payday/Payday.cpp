#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <sstream>

constexpr int MaxRundenPunkte = 4;
constexpr int Arraysize = 4;
constexpr int GuardDown = 1;

struct OutTuple
{
	std::array<unsigned int, Arraysize> Konten{};
	std::array<std::string, Arraysize> Namen;
};

void Aufschreiben(OutTuple& Tuple)
{
	for (unsigned int I = 0; I < Tuple.Konten.size(); I++)
	{
		unsigned int Punkte = MaxRundenPunkte + 1;
		unsigned int Ignorance = MaxRundenPunkte + 1;

		while (Punkte > MaxRundenPunkte)
		{
			std::cout << "Gib Int fuer da Punkte von " << Tuple.Namen[I] << ": " << std::flush;
			std::cin >> Punkte;
		}
		std::cout << "Gib Int fuer da Ignoranz " << Tuple.Namen[I] << ": " << std::flush;
		std::cin >> Ignorance;

		Tuple.Konten[I] += Ignorance + Punkte;
	}
}

std::array<std::string, Arraysize> Namensgebung()
{
	std::array<std::string, Arraysize> Namen;
	for (unsigned int I = 0; I < Namen.size(); I++)
	{
		std::cout << "Gib Name fuer Spieler" << I << ": " << std::flush;
		std::cin >> Namen[I];
	}
	return Namen;
}

std::ostream& operator<<(std::ostream& Stream, OutTuple Out)
{
	for (unsigned int I = 0; I < Arraysize; I++)
		Stream << Out.Namen[I] << ": " << Out.Konten[I] << std::endl;

	return Stream;
}

void OStream(OutTuple Tuple)
{
	std::string Dateiname;
	std::ofstream MyFile;

	std::cout << "Dateiname: " << std::flush;
	std::cin >> Dateiname;

	MyFile.open(Dateiname);
	MyFile << Tuple;
	MyFile.close();
}

OutTuple IStream()
{
	OutTuple Tuple;
	std::ifstream MyFile;
	std::string Dateiname;
	std::string Zwischenspeicher;

	std::cout << "Dateiname: " << std::flush;
	std::cin >> Dateiname;

	MyFile.open(Dateiname);

	unsigned int WhileIterator = 0;
	while (std::getline(MyFile, Zwischenspeicher))
	{
		if (Zwischenspeicher.size() == 0)
			break;

		size_t I = Zwischenspeicher.size();
		for (; I > 0; I--)
			if (Zwischenspeicher[I] == ':')
				break;
		
		std::unique_ptr<char> Tmp(new char[Zwischenspeicher.size()+1]);
		
		unsigned int K = 0;
		for (; K < I; K++)
		{
			Tmp.get()[K] = Zwischenspeicher[K];
		}
		Tmp.get()[K] = '\0';

		Tuple.Namen[WhileIterator] = Tmp.get();

		Tuple.Konten[WhileIterator] = std::stoi(Zwischenspeicher.c_str() + I + 1);

		WhileIterator++;
	}

	MyFile.close();
	return Tuple;
}

int main()
{
	int X;

	OutTuple Tuple{};

	while (true)
	{
		std::cout << "Gib Zahl ein: " << std::flush;
		std::cin >> X;
		switch (X)
		{
		case 0:
			for (auto& Konto : Tuple.Konten) Konto = 0;
			for (auto& Name : Tuple.Namen) Name = "";
			break;
		case 1:
			Aufschreiben(Tuple);
			break;
		case 2:
			Tuple = IStream();
			break;
		case 3:
			OStream(Tuple);
			break;
		case 4:
			std::cout << Tuple << std::endl;
			break;
		case 5:
			Tuple.Namen = Namensgebung();
			break;
		case 6:
			return 0;
		default:
			std::cout << "0. Zuruecksetzen." << std::endl
				<< "1. Erstelle/Veraendere Punktekonto." << std::endl
				<< "2. Punktekonto einlesen." << std::endl
				<< "3. Punktekonto schreiben." << std::endl
				<< "4. Punktekonto anzeigen." << std::endl
				<< "5. Namen erstellen.(Als erstes empfohlen)" << std::endl
				<< "6. Programm beenden." << std::endl;
			break;
		}
	}
}
