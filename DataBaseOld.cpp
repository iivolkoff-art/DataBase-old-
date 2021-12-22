#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <stack>

using namespace std;

class Person
{
public:
	string name, position;
	int grup = 0, day = 0, month = 0, year = 0;
};


ifstream data_input;
ofstream data_output;
Person a[20];


void Clear();
int create(int n, int index);
void Print(int index);
int Read();
void QS(Person* a, int first, int index);

int main()
{

	setlocale(LC_ALL, "Russian");
	bool exit = false;
	int index = 0;
	int left = 0;
	int first = 0;
	int person = 0;
	index = Read();
	int x;
	do
	{
		cout << "1 - Создание." << endl;
		cout << "2 - Просмотр." << endl;
		cout << "3 - Редактирование." << endl;
		cout << "4 - Отсортировать людей по стажу работы внутри отдельно взятого отдела." << endl;
		cout << "5 - Очистка." << endl;


		cin >> x;
		switch (x)
		{


		case 1:
			int n;
			cout << "Введите кол-во работников:";
			cin >> n;
			index = create(n, index);
			break;


		case 2:
			if (index == 0)
			{
				cout << "ФАЙЛ ПУСТ!\n";
			}
			else
			{
				Print(index);
			}
			break;


		case 3:
			do
			{
				if (index == 0)
				{
					cout << "Нет рабочих\n";
					break;
				}
				Print(index);

				cout << "Для редактирования доступно " << index << " рабочих \nВыберите номер рабочего:\t";
				int num;
				cin >> num;

				int y;
				cout << "Параметр для изменения:\n1 - Фамилия;\n2 - Дата начала работы;\n3 - Номер отдела;\n 4- Должность \n5 - Без изменений\n";
				cin >> y;
				switch (y)
				{
				case 1:
					cout << "Введите фамилию " << num << "рабочего:";
					cin >> a[num - 1].name;
					break;

				case 2:
					cout << "Введите день начала работы " << num << "рабочего:";
					cin >> a[num - 1].day;
					cout << "Введите месяц начала работы " << num << "рабочего:";
					cin >> a[num - 1].month;
					cout << "Введите день начала работы " << num << "рабочего:";
					cin >> a[num - 1].year;
					break;

				case 3:
					cout << "Введите номер отдела " << num << "рабочего:";
					cin >> a[num - 1].grup;
					break;

				case 4:
					cout << "Введите должность " << num << "рабочего:";
					cin >> a[num - 1].position;
					break;

				default:
					break;
				}

				cout << "Продолжить? y/n\t";
				char s;
				cin >> s;
				if (s == 'n')
				{
					break;
				}
			} while (true);
			Clear();
			data_output.open("file.txt");
			for (int i = 0; i < index; i++)
			{

				data_output << a[i].name << " " << a[i].day << "." << a[i].month << "." << a[i].year << " " << a[i].position;
				data_output << endl;
			}
			data_output.close();
			break;

		case 4:

			Print(index);
			cout << "Введити интересующую вас отдел:";
			int grupa;

			cin >> grupa;
			for (int i = 0; i < index; i++)
			{
				if (grupa == a[i].grup)
				{
					QS(a, 0, index);

					cout << "\nФамилия - " << a[i].name << " " << "\nНомер отдела - " << a[i].grup << " " << "\nДата начала работы - " << a[i].day << "." << a[i].month << "." << a[i].year << "\nДолжность - " << a[i].position << endl;
				}
			}
			break;

		case 5:
			index = 0;
			Clear();
			break;

		default:
			break;
		}
	} while (!exit);
}

int Read()
{
	string temp_line;
	data_input.open("file.txt");
	int count_of_lines = 0;
	while (getline(data_input, temp_line))
	{
		count_of_lines++;
	}

	data_input.close();
	data_input.open("file.txt");
	int i = 0;
	for (i; i < count_of_lines; i++)
	{
		data_input >> a[i].name;
		data_input >> a[i].day;
		data_input >> a[i].month;
		data_input >> a[i].year;
		data_input >> a[i].grup;
		data_input >> a[i].position;
	}

	data_input.close();

	return i;
}

void Print(int index)
{

	for (int i = 0; i < index; i++)
	{
		cout << "\nРаботник № " << i + 1 << "\nФамилия - " << a[i].name << "\nНомер отдела - " << a[i].grup << "\nДата начала работы - " << a[i].day << "." << a[i].month << "." << a[i].year << "\nДолжность - " << a[i].position << endl;
	}
	cout << endl;
}

void Clear()
{
	data_output.open("file.txt", ofstream::out | ofstream::trunc);
	data_output.close();
}

void QS(Person* a, int first, int index)
{

	int i = first, j = index - 1, x = a[(first + index) / 2].year;

	do
	{
		while (a[i].year < x) i++;

		while (a[j].year > x) j--;

		if (i <= j)
		{

			if (a[i].year > a[j].year) swap(a[i].year, a[j].year);

			i++;
			j--;

		}

	} while (i <= j);

	if (first < j)
	{
		QS(a, first, j);
	}
	if (i < index)
	{
		QS(a, i, index);
	}
}

int create(int n, int startIndex)
{
	data_output.open("file.txt", ios::app);
	for (int i = startIndex; i < startIndex + n; i++)
	{
		cout << "Введите фамилию " << i + 1 << " рабочего:";
		cin >> a[i].name;

		cout << "Введите день начала работы " << i + 1 << " рабочего:";
		cin >> a[i].day;


		cout << "Введите месяц начала работы " << i + 1 << " рабочего:";
		cin >> a[i].month;


		cout << "Введите год начала работы " << i + 1 << " рабочего:";
		cin >> a[i].year;

		cout << "Введите номер отдела " << i + 1 << " рабочего:";
		cin >> a[i].grup;

		cout << "Введите должность " << i + 1 << " рабочего:";
		cin >> a[i].position;


		data_output << a[i].name << " " << a[i].day << " " << a[i].month << " " << a[i].year << " " << a[i].grup << " " << a[i].position << " ";

		data_output << endl;
	}
	data_output.close();
	return startIndex + n;
}
