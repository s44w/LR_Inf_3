#include <iostream>
#include <string>
#include <vector>

using namespace std;

int input_check()
{
	/*
	Функция, проверяет, являются ли введенные пользователем данные числом

	Если фукнция stod не срабатывает ИЛИ to_string обрезает ввод, то выводит ошибку

	Возвращает:
		number: double -  число, переведенное из input: string, которое ввел пользователь
	*/
	string input;
	bool ok = true;
	int number = 0;

	while (ok)
	{
		getline(cin, input);
		try
		{
			number = stoi(input);
			if (to_string(number).length() != input.length())
			{
				throw (1);
			}
			return number;
		}
		catch (invalid_argument)
		{
			cerr << "Error (1)! Write an integer number!" << endl;
		}
		catch (int i)
		{
			cerr << "Error (2)! Write a number!" << endl;
		}
	}
}


vector < vector <int> > array_input(int hei, int len)
{
	/*
	Функция, позволяет пользователю вводить элементы матрицы
	Аргументы:
		hei: int - количество строк
		len: int - количество столбов
	Выводит:
		data: vector < vector <int> > - готовая матрица
	*/
	vector < vector <int> > data(hei, vector<int> (len));
	for (int i = 0; i < hei; ++i)
	{
		for (int j = 0; j < len; ++j)
		{ 
			cout << '\n' << "Input the element #(" << i << " , " << j << "): ";
			data[i][j] = input_check();
		}
	}
	return data;
}

void output(vector <vector <int> > data)
{
	/*
	Функция, выводит элементы матрицы 
	*/
	cout << '\n' << '\n' << "Your matrix is: " << endl;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[0].size(); ++j)
		{
			cout << data[i][j] << '\t';
		}
		cout << '\n';
	}
}

char erase_insert()
{
	bool ok = true;
	string str;
	while (ok)
	{
		getline(cin,str);
		if (str == "insert") return 'i';
		if (str == "erase") return 'e';
		else cout << "Error! Try again" << endl;
	}
}

char row_column()
{
	bool ok = true;
	string str;
	while (ok)
	{
		getline(cin, str);
		if (str == "row")    return 'r';
		if (str == "column")   return 'c';
		else cout << "Error! Try again" << endl;
	}
}

vector <vector <int> > Erase(vector < vector <int> > data, char button, int num)
{
	/*
	Функция, удаляет столбец или строку матрицы
	Аргументы: 
		data: vector < vector <int> > - стартовая матрица 
		button: char - символ, получаемый из функции erase_insert
		num: int - выбранная часть
	Возвращает: 
		data: vector < vector <int> > - измененная матрица
	*/
	int len = data.size();

	if (button == 'r') //удаляем строку
	{
		data.erase(data.begin() + num);
	}
	else   //удаляем столбец
	{
		for (int i = 0; i < len; ++i)
			data[i].erase(data[i].begin() + num);
	}
	return data;
}

vector <vector <int> >  row_insert(vector < vector <int> > data, int num)
{
	int hei = data[0].size(), len = data.size();
	vector <int> row;

	cout << "Input new elements: " << endl;
	for (int i = 0; i < hei; ++i)   row.push_back(input_check());
	
	data.insert(data.begin() + num, row);

	return data;
}

vector <vector <int> > column_insert(vector < vector <int> > data, int num)
{
	int hei = data[0].size(), len = data.size();
	cout << "Input new elements: " << endl;

	for (int i = 0; i < len; ++i)	
			data[i].insert(data[i].begin() + num, input_check());

	return data;
}


int number_condition(int cond)
{
	/*
	Функция, проверяет, входит ли число в промежуток от 0 до int cond
	*/
	int numb = -1;
	while (numb < 0 || numb > cond)
	{
		numb = input_check();
		if (numb < 0 || numb > cond) cout << "Error! Follow the condition!" << endl;
	}
	return numb;
}


int number_choose(string type, int i)
{
	cout << "Choose a number that less than " << type << "(" << i << ") of your matrix" << endl;
	int num = number_condition(i);
	return num;
}



vector < vector <int> > array_choose(vector < vector <int> > data, char butt_ErIn, char butt_RC)
{
	/*
	Функция, позволяет пользователю выбрать, что делать с матрицей
	Аргументы: 
		data: vector < vector <int> > - изначальная матрица
		butt_ErIn: char - символ, отвечает за выбор действия erase/insert 
		butt_RC: char - символ, отвечает за выбор части row/column
	Выводит: 
		data: vector < vector <int> > - преобразованная матрица
	*/
	int chosen_n = -1;
	switch (butt_ErIn + butt_RC)
	{
	case ('i'+'r'):  //нужно вставить строку

		chosen_n = number_choose("row", data.size());
		data = row_insert(data, chosen_n);
		break;
	case('i'+'c'):  //нужно вставить столбец

		chosen_n = number_choose("column", data[0].size());
		data = column_insert(data, chosen_n);
		break;
	case('e'+ 'r'):   //нужно удалить строку

		chosen_n = number_choose("row", data.size()-1);
		data = Erase(data, 'r', chosen_n);
		break;
	case ('e'+'c'):   //нужно удалить столбец
		
		chosen_n = number_choose("column", data[0].size()-1);
		data = Erase(data, 'c', chosen_n);
		break;
	}
	return data;
}

bool YN_function()
{
	/*
	Функция узнает, вводит пользователь Y или N.
	В зависимости от этого возвращает:
		'1', если введено 'Y'
		'0', если введено 'N'
	*/
	string button;
	bool end = false;
	while (end == 0)
	{
		getline(cin, button);
		if (button[0] == 'Y' && button.length() == 1) return  true;
		if (button[0] == 'N' && button.length() == 1)  return false;
		if (end == 0) cout << "Write 'Y' or 'N'!" << endl;
	}
}

bool finish = true;
int hei = 0, len = 0;
int main()
{
	vector < vector <int> > data;
	while (finish)
	{
		if (data.size() == 0 || data[0].size() == 0) {
			cout << "Input number of rows and columns in your matrix" << endl;
			cout << "Rows: ";
			while (hei < 2) {
				hei = input_check();
				if (hei < 2) cout << "Input a number >1" << endl;
			}

			cout << '\n' << "Columns: ";
			while (len < 2) {
				len = input_check();
				if (len < 2) cout << "Input a number >1" << endl;
			}

			cout << '\n' << '\n' << "Input elements of your matrix: (" << hei * len << ")" << endl;
			data = array_input(hei, len);

			output(data);
		}
		cout << '\n' << "What do you want to do? Input 'insert' or 'erase'" << endl;
		char butt_EraseInsert = erase_insert();

		cout << '\n' << "With what part of matrix? Input 'row' or 'column'" << endl;
		char butt_RowColumn = row_column();

		cout << '\n';
		data = array_choose(data, butt_EraseInsert, butt_RowColumn);
		output(data);

		cout << '\n' << "Do you want to continue? Input 'Y' or 'N'" << endl;
		finish = YN_function();
	}
}