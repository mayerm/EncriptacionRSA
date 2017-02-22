
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <array>

using std::cin;
using std::cout;
using std::array;
using std::string;

bool esPrimo(long int pr);
long int getD(const long int& x, const long int& phi);

template <typename T, size_t N>
void genClaves(const T& phi, const T& p, const T& q, array<T, N>& dKeys, array<T, N>& eKeys);

template <typename T, size_t N>
void encriptar(array<T, N> asciiChars, const T& eKey, const T& n, array<T, N>& encryptedChars);

template <typename T, size_t N>
void desencriptar(const T& dKey, const T& n, array<T, N>& asciiChars, const array<T, N>& encryptedChars);

bool esPrimo(long int pr)
{
	long int j = sqrt(pr);
	for (size_t i = 2; i <= j; i++)	
		if (pr % i == 0)
			return false;	
	return true;
}
int main()
{
	cout << "\nIngrese un numero primo\n";
	long int p, q;
	cin >> p;
	if (!esPrimo(p))
	{
		cout << "\nHa ingresado un número no primo\n";
		return 0;
	}
	cout << "\nIngrese otro numero primo\n";
	cin >> q;
	if (p == q){
		cout << "\nLos numeros no pueden ser iguales\n";
		return 0;
	}
	if (!esPrimo(q))
	{
		cout << "\nHa ingresado un número no primo\n";
		return 0;
	}
	cout << "\nIngrese el mensaje que desea encriptar\n";
	string msg;
	cin >> msg;
	array<long int, 100> asciiChars;
	if (msg.length() >= 100)
	{
		cout << "\nEl mensaje ingresado es muy largo.\n";
		return 0;
	}
	for (size_t i = 0; i < msg.length(); i++)
		asciiChars.at(i) = msg.at(i);
	asciiChars.at(msg.length()) = -1;
	long int n = p * q;
	long int phi = (p - 1) * (q - 1);
	array<long int, 100> dKeys, 
						 eKeys,						 
						 encryptedChars;
	genClaves(phi, p, q, dKeys, eKeys);
	encriptar(asciiChars, eKeys.at(0), n, encryptedChars);
	desencriptar(dKeys.at(0), n, asciiChars, encryptedChars);
	return 0;
}

template <typename T, size_t N>
void genClaves(const T& phi, const T& p, const T& q, array<T, N>& dKeys, array<T, N>& eKeys)
{
	int k = 0,
		aux = 0;
	for (size_t i = 2; i < phi; i++)
	{
		if (phi % i != 0){
			if (esPrimo(i) && i != p && i != q)
			{
				eKeys.at(k) = i;
				aux = getD(eKeys.at(k), phi);
				if (aux > 0)
				{
					dKeys.at(k) = aux;
					k++;
				}
				if (k == 99)
					break;
			}
		}
	}
}
long int getD(const long int& x, const long int& phi)
{
	long int k = 1;
	bool isInteger = false;
	do {
		k += phi;
		if (k % x == 0){
			isInteger = true;
			k /= x;
		}
	} while (!isInteger);
	return k;
}


template <typename T, size_t N>
void encriptar(array<T, N> asciiChars, const T& eKey, const T& n, array<T, N>& encryptedChars)
{
	long int k;
	int i = 0;
	while (asciiChars.at(i) != -1)
	{
		k = 1;
		for (size_t j = 0; j < eKey; j++)
		{
			k *= asciiChars.at(i) - 96;
			k %= n;
		}
		encryptedChars.at(i) = k + 96;
		i++;
	}
	cout << "\nEl mensaje encriptado es: ";
	for (size_t i = 0; asciiChars.at(i) != -1; i++){
		cout << (char)encryptedChars.at(i);
		asciiChars.at(i) = 0;
	}
}
template <typename T, size_t N>
void desencriptar(const T& dKey, const T& n, array<T, N>& asciiChars, const array<T, N>& encryptedChars)
{
	long int k;
	int i = 0;
	while (asciiChars.at(i) != -1){
		k = 1;
		for (size_t j = 0; j < dKey; j++)
		{
			k *= encryptedChars.at(i) - 96;
			k %= n;
		}		
		asciiChars.at(i) = k + 96;
		i++;
	}
	cout << "\nEl mensaje desencriptado es: ";
	for (i = 0; asciiChars.at(i) != -1; i++)
		cout << (char) asciiChars.at(i);
}
