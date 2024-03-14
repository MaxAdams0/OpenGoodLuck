#include <iostream>

int main()
{
	std::cout << "========== RGB 2 HSV CONVERTER ==========" << "\n";
	double R, G, B;
	std::cout << "R: "; std::cin >> R;
	std::cout << "G: "; std::cin >> G;
	std::cout << "B: "; std::cin >> B;
	R = R / 255 * 100.0 / 100.0;
	G = G / 255 * 100.0 / 100.0;
	B = B / 255 * 100.0 / 100.0;

	std::cout << R << ", " << G << ", " << B << ", 1.0" << "\n";
	system("pause");
}