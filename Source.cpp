#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum measurement { ��, �, ��, ��, �� };

string t_measurement[] = { "�� ",
						   "��",
						   "��",
						   "��",
						   "��" };

struct towar
{
	string n_towar;
	int vart�st;
	int kilkist;
	measurement units;
	int masa;
};

void Create(towar& s, const int kilkist, ofstream& file_s, int i);
void Print(towar& s, const int kilkist, ifstream& file_l, int i);

void vulychenya(towar& s, int& kil_towar, int pozution, ifstream& file_l, ofstream& file_s);
void Coppy(towar& s, const int kil_towar, ofstream& file_s, ifstream& file_l);
void dobavut(towar& s, const int kilkist, const char* fname, const char* gname, const char* lname, const int pos);

void SortBIN(towar& str, towar& str_a, towar& str_b, const int kilkist, const char* fname, fstream& f, bool b);
int BinSearch(towar& s, const int kilkist, const string nazva_t, const char* fname, ifstream& file_l);

void BinSearch_vartist(towar& s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, const char* fname, ifstream& file_l);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_towar;
	cout << "������ ��������� ������� ������: "; cin >> kil_towar;
	cout << endl;
	int kil = kil_towar;

	towar s;
	towar str;
	towar str_a;
	towar str_b;

	char fname[101];
	cout << "������ ����� ��������� �����: "; cin >> fname; cout << endl;

	char gname[101];
	cout << "������ ����� ��������� ����� ��� ������ ��������: "; cin >> gname; cout << endl;

	char lname[101];
	cout << "������ ����� ��������� ����� ��� ������ ��������: "; cin >> lname; cout << endl;

	ifstream file_l;
	ofstream file_s;
	fstream f;

	int i, g, pos, zmina, found, index;
	int l1 = 0, l2 = 0;
	int vartisr1, vartisr2;
	string nazwa_towar;
	char filename[100];

	int menutowar;
	do {
		cout << "������� ��:" << endl << endl;

		cout << " [1] - ��������� ������ ������" << endl;
		cout << " [2] - ���� ���������� ��� �����" << endl;

		cout << " [3] - ���������� ������" << endl;
		cout << " [4] - ��������� ������" << endl;
		cout << " [5] - ����������� ���������� ��� �����" << endl;
		cout << " [6] - ���������� ������" << endl;
		cout << " [7] - ����� ������ �� ������ � ���� ���������� ��� �����" << endl;
		cout << " [8] - ���� ���������� ��� ������ �� �������� �������� �������" << endl;
		cout << " [9] - ����� ����� � ����" << endl;
		cout << " [10] - ���������� ����� �� �����" << endl << endl;

		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;

		cout << "������ ����� ����: "; cin >> menutowar;
		switch (menutowar)
		{
		case 1:
			kil_towar = kil;
			file_s.open(fname, ios::binary);
			Create(s, kil_towar, file_s, 0);
			cout << endl;
			file_s.close();
			break;
		case 2:
			file_l.open(fname, ios::binary);
			Print(s, kil_towar, file_l, 0);
			file_l.close();
			break;
		case 3:
			cout << endl;
			cout << "������ ����� ������� ������ �� �� ������ �������� �� ������: "; cin >> g;
			cout << endl;
			kil_towar += g;
			i = kil_towar - g;
			file_s.open(fname, ios::binary | ios::app);
			Create(s, kil_towar, file_s, i);
			file_s.close();
			break;
		case 4:
			cout << endl;
			cout << "������ ����� ������� ������ ��� ��������� ���� � ������: "; cin >> pos;
			cout << endl;

			file_s.open(gname, ios::binary);
			file_l.open(fname, ios::binary);
			Coppy(s, kil_towar, file_s, file_l);
			file_s.close();
			file_l.close();

			file_s.open(fname, ios::binary);
			file_l.open(gname, ios::binary);
			vulychenya(s, kil_towar, pos, file_l, file_s);
			file_s.close();
			file_l.close();

			break;
		case 5:
			cout << endl;
			cout << "������ ����� ������� ������ ��� ����������� ���� ���������� � ������: "; cin >> pos;
			cout << endl;
			dobavut(s, kil_towar, fname, gname, lname, pos);
			break;
		case 6:
			cout << endl;
			cout << "���������� �� ���� ������(����� 1) ��� �� ��������� �������(����� 0): " << endl;
			cout << "������� ������ �����(1 ��� 0): "; cin >> zmina;
			cout << endl;
			SortBIN(str, str_a, str_b, kil_towar, fname, f, zmina);
			break;
		case 7:
			cout << endl;
			cin.get();
			cin.sync();
			cout << "������ ����� ������: "; getline(cin, nazwa_towar);
			cout << endl;

			if ((found = BinSearch(s, kil_towar, nazwa_towar, fname, file_l)) != -1)
			{
				cout << "�������� �������� � ������ �� ������� " << found + 1 << endl << endl;

				file_l.open(fname, ios::binary);
				file_l.seekg(found * sizeof(towar), ios::beg);
				Print(s, found + 1, file_l, found);
				file_l.close();
			}
			else
				cout << "�������� �������� � ������ �� ��������" << endl << endl;
			break;
		case 8:
			cout << "ĳ������ �������: " << endl << endl;
			cout << "������ �������� �������: ";
			cin >> vartisr1;
			cout << "������ ����������� �������: ";
			cin >> vartisr2;
			l1 = -1;
			l2 = -2;
			BinSearch_vartist(s, kil_towar, vartisr1, vartisr2, l1, l2, fname, file_l);
			file_l.open(fname, ios::binary);
			file_l.seekg(l1 * sizeof(towar), ios::beg);
			Print(s, l2 + 1, file_l, l1);
			file_l.close();
			break;
		case 0:
			cout << endl;
			cout << "���������� ������ ��������" << endl << endl;
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
			cout << endl;
		}
	} while (menutowar != 0);
	exit(0);
}

void Create(towar& s, const int kilkist, ofstream& file_s, int i)
{
	int towar_l;
	for (; i < kilkist; i++)
	{
		cout << endl;
		cout << "����� � " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  �����: "; getline(cin, s.n_towar);
		cout << "  �������(� ���.): "; cin >> s.vart�st;
		cout << "  �������: "; cin >> s.kilkist;
		cout << "  ������� ����������(0 - ̳�����, 1 - ����, 2 - �������, 3 - ʳ������, 4 - �����): "; cin >> towar_l;
		s.units = (measurement)towar_l;
		cout << "  �������� ��: "; cin >> s.masa; cout << "  " << t_measurement[towar_l] << endl;

		if (!file_s.write((char*)&s, sizeof(towar)))
		{
			cerr << "Error writing file." << endl;
		}
	}
}

void Print(towar& s, const int kilkist, ifstream& file_l, int i)
{
	cout << "====================================================================="
		<< endl;
	cout << "| �  | �����        | �������(� ���.) | ʳ������ | �������� ��    |"
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;

	for (; i < kilkist; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s.n_towar
			<< "| " << setw(16) << left << s.vart�st << " "
			<< "| " << setw(5) << left << s.kilkist << "     "
			<< "| " << setw(2) << left << s.masa << setw(1) << left << " " << setw(11) << left << t_measurement[s.units] << " |" << endl;
	}
	cout << "=====================================================================" << endl;
}

void vulychenya(towar& s, int& kil_towar, int pozution, ifstream& file_l, ofstream& file_s)
{
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		if (i + 1 != pozution)
			file_s.write((char*)&s, sizeof(towar));
		else
			kil_towar--;
	}
}

void Coppy(towar& s, const int kil_towar, ofstream& file_s, ifstream& file_l)
{
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		file_s.write((char*)&s, sizeof(towar));
	}
}

void dobavut(towar& s, const int kilkist, const char* fname, const char* gname, const char* lname, const int pos)
{
	fstream file_l_s;
	fstream file;
	fstream file_l;

	file.open(fname, ios::binary | ios::in);
	file_l.open(lname, ios::binary | ios::out);
	for (int i = 0; i < kilkist; i++)
	{
		file.read((char*)&s, sizeof(towar));
		file_l.write((char*)&s, sizeof(towar));
	}
	file.close();
	file_l.close();

	int towar_l;
	cout << endl;
	cout << "����� � " << pos << endl;

	cin.get();
	cin.sync();

	cout << "  �����: "; getline(cin, s.n_towar);
	cout << "  �������(� ���.): "; cin >> s.vart�st;
	cout << "  �������: "; cin >> s.kilkist;
	cout << "  ������� ����������(0 - ̳�����, 1 - ����, 2 - �������, 3 - ʳ������, 4 - �����): "; cin >> towar_l;
	s.units = (measurement)towar_l;
	cout << "  �������� ��: "; cin >> s.masa; cout << "  " << t_measurement[towar_l] << endl;

	file_l_s.open(gname, ios::binary | ios::out);
	if (!file_l_s.write((char*)&s, sizeof(towar)))
	{
		cerr << "Error writing file." << endl;
	}
	file_l_s.close();

	file_l.open(lname, ios::binary | ios::in);
	file.open(fname, ios::binary | ios::out);
	file_l_s.open(gname, ios::binary | ios::out | ios::in);
	for (int i = 0; i < kilkist; i++)
	{
		if (i != pos - 1)
			file_l.read((char*)&s, sizeof(towar));
		else
			file_l_s.read((char*)&s, sizeof(towar));

		file.write((char*)&s, sizeof(towar));
	}
	file.close();
	file_l.close();
	file_l_s.close();

}

void SortBIN(towar& str, towar& str_a, towar& str_b, const int kilkist, const char* fname, fstream& f, bool b)
{
	for (int i0 = 1; i0 < kilkist; i0++)
	{
		for (int i1 = 0; i1 < kilkist - i0; i1++)
		{
			f.open(fname, ios::binary | ios::in | ios::out);
			int l, m;
			l = i1;
			m = i1 + 2;
			while (l < m)
			{
				f.seekg(l * sizeof(towar), ios::beg);
				f.read((char*)&str, sizeof(towar));
				if (l == m - 2)
					str_a = str;
				else
					str_b = str;
				l++;
			}

			if (b)
			{
				if (str_a.n_towar > str_b.n_towar)
				{
					l = i1;
					while (l < m)
					{
						if (l == m - 2)
							str = str_b;
						else
							str = str_a;
						f.seekp(l * sizeof(towar), ios::beg);
						f.write((char*)&str, sizeof(towar));
						l++;
					}
				}
			}
			else
			{
				if (str_a.vart�st > str_b.vart�st)
				{
					l = i1;
					while (l < m)
					{
						if (l == m - 2)
							str = str_b;
						else
							str = str_a;
						f.seekp(l * sizeof(towar), ios::beg);
						f.write((char*)&str, sizeof(towar));
						l++;
					}
				}
			}
			f.close();
		}
	}
}

int BinSearch(towar& s, const int kilkist, const string nazva_t, const char* fname, ifstream& file_l)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		file_l.open(fname, ios::binary);
		file_l.seekg(m * sizeof(towar), ios::beg);
		file_l.read((char*)&s, sizeof(towar));
		file_l.close();
		if (s.n_towar == nazva_t)
			return m;
		if (s.n_towar > nazva_t)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
}

void BinSearch_vartist(towar& s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, const char* fname, ifstream& file_l)
{
	int g = 0;
	file_l.open(fname, ios::binary);
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		if (s.vart�st >= vartisr1 && s.vart�st <= vartisr2)
		{
			l2 = i;
			g++;
		}
		if (g == 1)
			l1 = l2;
	}
	file_l.close();
}
