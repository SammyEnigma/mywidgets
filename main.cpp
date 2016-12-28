#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <initializer_list>
#include <iostream>

#include "singleapplication.h"


using namespace std;

double mean(int n, ...)
{
    va_list ap;
    double sum = 0;
    int count = n;

    va_start(ap, n);
    for (int i = 0; i < count; ++i) {
        sum += va_arg(ap, double);
    }
    va_end(ap);
    return sum / count;
}

void func(std::initializer_list<int> list)
{
    foreach (auto i, list) {
        qDebug() << i;
    }
    std::cout << "sdcds" << std::endl;
}

template <class T>
void print(const T &t)
{
    std::cout << t;
}

template <class T, class...args>
void print(const T &t, const args &...a)
{
    std::cout << t << std::endl;
    print(a...);
}

class MyArray
{
public:
    typedef int LengthType;

    LengthType GetLength;
};

template<class T>
void MyMethod(T myarr)
{
	typedef typename T::LengthType LengthType;
	LengthType length = myarr.GetLength;
	std::cout << length << std::endl;
}


int main(int argc, char *argv[])
{
#ifdef SINGLEAPPLICATION
	SingleApplication a(argc, argv);

	if (!a.isRunning()) {
		Widget w;
		w.show();

		return a.exec();
}
	else {
		QMessageBox::information(0, "tip", "running");
		return 0;
	}
#else
	QApplication a(argc, argv);

	Widget w;
	w.show();

	return a.exec();
#endif


// 	qDebug() << mean(4, 1.111, 4.234, 5.4355, 345.4355);
// 	func({ 1, 3, 4, 5 });
// 	print(1, 32, 32.234, "sdcds");
// 
// 	MyArray m;
// 	MyMethod<MyArray>(m);
// 
// 	qDebug() << (111 & -1) << (111 & -2) << (56 & -1) << (56 & -2);
// 
// 	return 0;
}
