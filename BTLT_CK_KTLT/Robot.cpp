#include<iostream>
#include<fstream>
#include<iomanip>	
#include<string>
#include<thread>
#include<chrono>
#include<Windows.h>
#define MAX 30
using namespace std;
int a[MAX][MAX];
struct Robot {
	//properties
	int x;
	int y;
	int total_values;
	//contructor
	Robot() {}
	Robot(int _x, int _y, int _total_values) {
		x = _x;
		y = _y;
		total_values = _total_values;
	}
	//operator overloading
	// nhập thông tin robot
	friend istream& operator>>(istream &is, Robot &R) {
		cout << "Nhap toa do theo hang: ";
		is >> R.x;
		cout << "Nhap toa do theo cot : ";
		is >> R.y;
		return is;
	}
	// xuất thông tin robot
	friend ostream& operator<<(ostream& os, Robot R) {
		cout << "Cac thong so cua robot ban vua nhap: " << endl;
		cout << "Toa do hang: ";
		os << R.x << endl;
		cout << "Toa do cot: ";
		os << R.y << endl;
		cout << "Gia  tri cua robot tai toa do (" << R.x << ", " << R.y << ") la ";
		os << R.total_values << endl;
		return os;
	}
};
// input được lấy từ file để truyền vô hàm nhờ thao tác đọc file
void Nhap(int a[][MAX], int rows, int cols, ifstream &ifs) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			ifs >> a[i][j];
		}
	}
}
// hàm in ra sơ đồ mê cung
void print_map(int a[][MAX], int rows, int cols) {
	cout << "So Do Mo Phong Me Cung" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	int do_dai_phan_tu_co_gia_tri_lon_nhat = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int do_dai_phan_tu = to_string(a[i][j]).length() + 1;
			if (do_dai_phan_tu_co_gia_tri_lon_nhat < do_dai_phan_tu) {
				do_dai_phan_tu_co_gia_tri_lon_nhat = do_dai_phan_tu;
			}
		}
	}
	for (int i = 0; i < rows; ++i) {
		cout << "+";
		for (int j = 0; j < cols; ++j) {
			cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
		}
		cout << endl;
		for (int j = 0; j < cols; ++j) {
			cout << "| " << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int j = 0; j < cols; ++j) {
		cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
	}
	cout << endl;
}
void set_Color(int code) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}
//hàm in sơ đồ mô phỏng đường đi của 1 robot
void print_Map_1Robot(int a[][MAX], int rows, int cols, int* DuongDi, int count_gia_tri) {
	int do_dai_phan_tu_co_gia_tri_lon_nhat = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int do_dai_phan_tu = to_string(a[i][j]).length() + 1;
			if (do_dai_phan_tu_co_gia_tri_lon_nhat < do_dai_phan_tu) {
				do_dai_phan_tu_co_gia_tri_lon_nhat = do_dai_phan_tu;
			}
		}
	}
	bool isFound[MAX][MAX] = { false };
	for (int k = 0; k < count_gia_tri; ++k) {
		cout << "\033[2J\033[1;1H";
		for (int x = 0; x < rows; ++x) {
			for (int y = 0; y < cols; ++y) {
				if (a[x][y] == DuongDi[k]) {
					cout << "Robot dang di toi o co toa do (" << x << ", " << y << ")" << endl;
				}
			}
		}
		cout << "Ban do mo phong duong di cua robot" << endl;
		for (int i = 0; i < rows; ++i) {
			cout << "+";
			for (int j = 0; j < cols; ++j) {
				cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
			}
			cout << endl;
			for (int j = 0; j < cols; ++j) {
				if (a[i][j] == DuongDi[k]) {
					isFound[i][j] = true;
				}
				if (isFound[i][j]) {
					cout << "| ";
					set_Color(12); // mã màu 12 tương ứng là màu đỏ
					cout << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j];
					set_Color(7); // đưa về màu mặc định của console
					cout << " ";
				}
				else {
					cout << "| " << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j] << " ";
				}
			}
			cout << "|" << endl;
		}
		cout << "+";
		for (int j = 0; j < cols; ++j) {
			cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
		}
		cout << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
	}
}
//hàm in sơ đồ mô phỏng đường đi của 2 robot
void print_Map_2Robot(int a[][MAX], int rows, int cols, int* DuongDiA, int* DuongDiB, int count_gia_triA, int count_gia_triB) {
	int do_dai_phan_tu_co_gia_tri_lon_nhat = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int do_dai_phan_tu = to_string(a[i][j]).length() + 1;
			if (do_dai_phan_tu_co_gia_tri_lon_nhat < do_dai_phan_tu) {
				do_dai_phan_tu_co_gia_tri_lon_nhat = do_dai_phan_tu;
			}
		}
	}
	bool isFound1[MAX][MAX] = { false };
	bool isFound2[MAX][MAX] = { false };
	for (int k = 0; k < max(count_gia_triA, count_gia_triB); ++k) {
		cout << "\033[2J\033[1;1H";
		for (int x = 0; x < rows; ++x) {
			for (int y = 0; y < cols; ++y) {
				if (k < count_gia_triA && a[x][y] == DuongDiA[k]) {
					cout << "Robot A dang di toi o co toa do (" << x << ", " << y << ")" << endl;
				}
				if (k < count_gia_triB && a[x][y] == DuongDiB[k]) {
					cout << "Robot B dang di toi o co toa do (" << x << ", " << y << ")" << endl;
				}
			}
		}
		cout << "Ban do mo phong duong di cua 2 robot" << endl;
		for (int i = 0; i < rows; ++i) {
			cout << "+";
			for (int j = 0; j < cols; ++j) {
				cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
			}
			cout << endl;
			for (int j = 0; j < cols; ++j) {
				if (k < count_gia_triA && a[i][j] == DuongDiA[k]) {
					isFound1[i][j] = true;
				}
				if (k < count_gia_triB && a[i][j] == DuongDiB[k]) {
					isFound2[i][j] = true;
				}
				if (isFound1[i][j] && isFound2[i][j]) {
					cout << "| ";
					set_Color(14); // mã màu 14 tương ứng là màu vàng
					// ô đánh dấu màu vàng là ô mà tại đó vị trí 2 robot đi trùng nhau
					cout << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j];
					set_Color(7); // đưa về màu mặc định của console
					cout << " ";

				}
				else if (isFound1[i][j]) {
					cout << "| ";
					set_Color(12); // mã màu 12 tương ứng là màu đỏ
					// Mã màu đỏ tượng trưng cho đường đi của robot A
					cout << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j];
					set_Color(7); // đưa về màu mặc định của console
					cout << " ";
				}
				else if (isFound2[i][j]) {
					cout << "| ";
					set_Color(5); // mã màu 9 tương ứng là màu tím
					// mã màu tím tượng trưng cho đường đi của robot B
					cout << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j];
					set_Color(7); // đưa về màu mặc định của console
					cout << " ";
				}
				else {
					cout << "| " << setw(do_dai_phan_tu_co_gia_tri_lon_nhat) << a[i][j] << " ";
				}
			}
			cout << "|" << endl;
		}
		cout << "+";
		for (int j = 0; j < cols; ++j) {
			cout << string(do_dai_phan_tu_co_gia_tri_lon_nhat + 2, '-') << "+";
		}
		cout << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
	}
}
//kiểm tra tọa độ của các ô robot đi
bool kiem_tra_toa_do(int x, int y, int rows, int cols) {
	if (x >= 0 && x < rows && y >= 0 && y < cols) {
		return 1;
	}
	else {
		return 0;
	}
}
// kĩ thuật mảng đánh dấu
// ý tưởng là các ô sẽ mang giá trị true khi các ô đó chưa được robot đi qua
void danh_dau_cac_o(bool** arr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = 1;
		}
	}
}
// hàm kiểm tra vị trí của robot
// ý tưởng: khi robot đã đi qua ô đó thì đánh dấu lại là 0 còn nếu chưa đi thì vẫn là 1
void kiem_tra_vi_tri(Robot robotA, bool** arr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i == robotA.x && j == robotA.y) {
				arr[i][j] = 0;
			}
		}
	}
}
// hàm so sánh tổng điểm của 2 robot
void Tong_Diem_Robot(int scoreA, int scoreB) {
	if (scoreA > scoreB) {
		cout << "Robot A Thang!" << endl;
	}
	else if (scoreA < scoreB) {
		cout << "Robot B Thang!" << endl;
	}
	else {
		cout << "Hoa!" << endl;
	}
}
//hàm đệ quy tìm đường đi và tính tổng các giá trị của các ô robot đã đi qua
int Duong_Di_Va_Tong_Diem_1Robot(int a[][MAX], Robot robot, int rows, int cols, bool** arr,int *&DuongDi, int &count_gia_tri) {
	// kiểm tra vị trí hiện tại ngay tọa độ x và y của robot
	kiem_tra_vi_tri(robot, arr, rows, cols);
	// kiểm tra 4 ô trên, dưới, trái, phải
	/* ý tưởng:
	kiểm tra xem nếu trong 4 vị trí trên có 1 vị trí robot có thể đi được thì phủ định của điều kiện trên chính là không còn ô nào mà robot có thể đi
	*/
	++count_gia_tri;
	if (!((kiem_tra_toa_do(robot.x + 1, robot.y, rows, cols) == 1 && arr[robot.x + 1][robot.y] == 1) 
		|| (kiem_tra_toa_do(robot.x - 1, robot.y, rows, cols)== 1 && arr[robot.x - 1][robot.y] == 1)
		|| (kiem_tra_toa_do(robot.x, robot.y + 1, rows, cols) == 1 && arr[robot.x][robot.y + 1] == 1)
		|| (kiem_tra_toa_do(robot.x, robot.y - 1, rows, cols) == 1 && arr[robot.x][robot.y - 1] == 1))) {
		return robot.total_values;
	}
	else {
		Robot next_position{};
		int max_values = 0;
		// top: ô bên trên vị trí hiện tại
		if (kiem_tra_toa_do(robot.x  - 1, robot.y, rows, cols) == 1 && arr[robot.x - 1][robot.y] == 1) {
			if (a[robot.x - 1][robot.y] > max_values) {
				max_values = a[robot.x - 1][robot.y];
				next_position = { robot.x - 1, robot.y, robot.total_values + max_values };
			}
		}
		// bottom: ô bên dưới vị trí hiện tại
		if (kiem_tra_toa_do(robot.x + 1, robot.y, rows, cols) == 1 && arr[robot.x + 1][robot.y] == 1) {
			if (a[robot.x + 1][robot.y] > max_values) {
				max_values = a[robot.x + 1][robot.y];
				next_position = { robot.x + 1, robot.y, robot.total_values + max_values };
			}
		}
		// right: Vị trí bên phải vị trí hiện tại
		if (kiem_tra_toa_do(robot.x, robot.y + 1, rows, cols) == 1 && arr[robot.x][robot.y + 1] == 1) {
			if (a[robot.x][robot.y + 1] > max_values) {
				max_values = a[robot.x][robot.y + 1];
				next_position = { robot.x, robot.y + 1, robot.total_values + max_values };
			}
		}
		// left: Vị trí bên trái vị trí hiện tại
		if (kiem_tra_toa_do(robot.x, robot.y - 1, rows, cols) == 1 && arr[robot.x][robot.y - 1] == 1) {
			if (a[robot.x][robot.y - 1] > max_values) {
				max_values = a[robot.x][robot.y - 1];
				next_position = { robot.x, robot.y - 1, robot.total_values + max_values };
			}
		}
		DuongDi[count_gia_tri] = max_values;
		return Duong_Di_Va_Tong_Diem_1Robot(a, next_position, rows, cols, arr, DuongDi, count_gia_tri);
	}
}
// hàm đệ quy tìm đường đi và tính tổng các giá trị của các ô mà 2 robot không được đi trùng nhau
int Duong_Di_2Robot(int a[][MAX], Robot robotA, Robot robotB, int rows, int cols, bool** arr,int* &DuongDiA, int* &DuongDiB, int &countA, int &countB, int& tongDiemA, int& tongDiemB) {
	kiem_tra_vi_tri(robotA, arr, rows, cols);
	kiem_tra_vi_tri(robotB, arr, rows, cols);
	++countA;
	++countB;
	if (!((kiem_tra_toa_do(robotA.x + 1, robotA.y, rows, cols) == 1 && arr[robotA.x + 1][robotA.y] == 1)
		|| (kiem_tra_toa_do(robotA.x - 1, robotA.y, rows, cols) == 1 && arr[robotA.x - 1][robotA.y] == 1)
		|| (kiem_tra_toa_do(robotA.x, robotA.y + 1, rows, cols) == 1 && arr[robotA.x][robotA.y + 1] == 1)
		|| (kiem_tra_toa_do(robotA.x, robotA.y - 1, rows, cols) == 1 && arr[robotA.x][robotA.y - 1] == 1))
		&&
		!((kiem_tra_toa_do(robotB.x + 1, robotB.y, rows, cols) == 1 && arr[robotB.x + 1][robotB.y] == 1)
			|| (kiem_tra_toa_do(robotB.x - 1, robotB.y, rows, cols) == 1 && arr[robotB.x - 1][robotB.y] == 1)
			|| (kiem_tra_toa_do(robotB.x, robotB.y + 1, rows, cols) == 1 && arr[robotB.x][robotB.y + 1] == 1)
			|| (kiem_tra_toa_do(robotB.x, robotB.y - 1, rows, cols) == 1 && arr[robotB.x][robotB.y - 1] == 1))) {
		return tongDiemA + tongDiemB;	
	}
	else {
		Robot next_positionA{};
		Robot next_positionB{};
		int max_valuesA = 0, max_valuesB = 0;
		// Kiểm tra các vị trí cho robotA
		if (kiem_tra_toa_do(robotA.x - 1, robotA.y, rows, cols) == 1 && arr[robotA.x - 1][robotA.y] == 1 && (robotA.x - 1 != robotB.x || robotA.y != robotB.y)) {
			if (a[robotA.x - 1][robotA.y] > max_valuesA) {
				max_valuesA = a[robotA.x - 1][robotA.y];
				next_positionA = { robotA.x - 1, robotA.y, robotA.total_values + max_valuesA };
			}
		}
		if (kiem_tra_toa_do(robotA.x + 1, robotA.y, rows, cols) == 1 && arr[robotA.x + 1][robotA.y] == 1 && (robotA.x + 1 != robotB.x || robotA.y != robotB.y)) {
			if (a[robotA.x + 1][robotA.y] > max_valuesA) {
				max_valuesA = a[robotA.x + 1][robotA.y];
				next_positionA = { robotA.x + 1, robotA.y, robotA.total_values + max_valuesA };
			}
		}
		if (kiem_tra_toa_do(robotA.x, robotA.y - 1, rows, cols) == 1 && arr[robotA.x][robotA.y - 1] == 1 && (robotA.x != robotB.x || robotA.y - 1 != robotB.y)) {
			if (a[robotA.x][robotA.y - 1] > max_valuesA) {
				max_valuesA = a[robotA.x][robotA.y - 1];
				next_positionA = { robotA.x, robotA.y - 1, robotA.total_values + max_valuesA };
			}
		}
		if (kiem_tra_toa_do(robotA.x, robotA.y + 1, rows, cols) == 1 && arr[robotA.x][robotA.y + 1] == 1 && (robotA.x != robotB.x || robotA.y + 1 != robotB.y)) {
			if (a[robotA.x][robotA.y + 1] > max_valuesA) {
				max_valuesA = a[robotA.x][robotA.y + 1];
				next_positionA = { robotA.x, robotA.y + 1, robotA.total_values + max_valuesA };
			}
		}
		DuongDiA[countA] = max_valuesA;
		tongDiemA += max_valuesA;
		kiem_tra_vi_tri(next_positionA, arr, rows, cols);// vì robotA đi trước nên khi robotA đi đến vị trí nào thì phải đánh dấu vị trí đó trước
		// vì nếu không đánh dấu lại vị trí của robot đi trước thì khi kiểm tra bằng cách gọi lại hàm đệ quy thì hai robot vẫn có thể đi cùng 1 ô
		// Kiểm tra các vị trí cho robotB
		if (kiem_tra_toa_do(robotB.x - 1, robotB.y, rows, cols) == 1 && arr[robotB.x - 1][robotB.y] == 1  && (robotB.x - 1 != robotA.x || robotB.y != robotA.y)) {
			if (a[robotB.x - 1][robotB.y] > max_valuesB) {
				max_valuesB = a[robotB.x - 1][robotB.y];
				next_positionB = { robotB.x - 1, robotB.y, robotB.total_values + max_valuesB };
			}
		}
		if (kiem_tra_toa_do(robotB.x + 1, robotB.y, rows, cols) == 1 && arr[robotB.x + 1][robotB.y] == 1 && (robotB.x + 1 != robotA.x || robotB.y != robotA.y)) {
			if (a[robotB.x + 1][robotB.y] > max_valuesB) {
				max_valuesB = a[robotB.x + 1][robotB.y];
				next_positionB = { robotB.x + 1, robotB.y, robotB.total_values + max_valuesB };
			}
		}
		if (kiem_tra_toa_do(robotB.x, robotB.y - 1, rows, cols) == 1 && arr[robotB.x][robotB.y - 1] == 1 && (robotB.x != robotA.x || robotB.y - 1 != robotA.y)) {
			if (a[robotB.x][robotB.y - 1] > max_valuesB) {
				max_valuesB = a[robotB.x][robotB.y - 1];
				next_positionB = { robotB.x, robotB.y - 1, robotB.total_values + max_valuesB };
			}
		}
		if (kiem_tra_toa_do(robotB.x, robotB.y + 1, rows, cols) == 1 && arr[robotB.x][robotB.y + 1] == 1 && (robotB.x != robotA.x || robotB.y + 1 != robotA.y)) {
			if (a[robotB.x][robotB.y + 1] > max_valuesB) {
				max_valuesB = a[robotB.x][robotB.y + 1];
				next_positionB = { robotB.x, robotB.y + 1, robotB.total_values + max_valuesB };
			}
		}
		DuongDiB[countB] = max_valuesB;
		tongDiemB += max_valuesB;
		return Duong_Di_2Robot(a, next_positionA, next_positionB, rows, cols, arr,DuongDiA, DuongDiB, countA, countB, tongDiemA, tongDiemB);
	}
}
// hàm hiển thị các thông số về hành trình của robot
// số ô robot đã đi cũng như giá trị của tọa độ đó 
void Thong_So_Hanh_Trinh_Cua_Robot(int *DuongDi, int count_gia_tri, bool** arr, int rows, int cols) {
	for (int i = 0; i < count_gia_tri - 1; ++i) {
		cout << DuongDi[i];
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << "\033[31m" << " -> " << "\033[0m" ;
		this_thread::sleep_for(chrono::milliseconds(100));
	} 
	cout << DuongDi[count_gia_tri - 1] << endl;
	cout << "So o ma robot da di chuyen: " << count_gia_tri << endl;
}
// hàm kiểm tra thông tin nhập vô của robot từ người dùng
bool Kiem_tra_thong_tin_Robot(Robot robot, int rows, int cols, int a[][MAX]) {
	// Nếu tọa độ x bé hơn 0 hoặc là lớn hơn số hàng của mê cung tức là tọa độ hàng của robot không hề nằm trong mê cung
	//Nếu tọa độ y bé hơn 0 hoặc là lớn hơn số cột của mê cung tức là tọa độ cột  của robot không hề nằm trong mê cung
	if ((robot.x < 0 || robot.x >= rows) || (robot.y < 0 || robot.y >= cols) ) return 0;
	else return 1;
}
// hàm kiểm tra các tọa độ trùng nhau của 2 robot
void Toa_Do_Trung_Nhau_Cua_2_Robot(int rows, int cols, bool** arrA, bool** arrB) {
	cout << "Toa do trung nhau cua 2 con robot lan luot la: " << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (arrA[i][j] == 0 && arrB[i][j] == 0) {
				cout << "(" << i << ", " << j << ") ";
			}
		}
	}
	cout << endl;
}
void Ghi_Toa_Do_Trung_Nhau_Cua_2_Robot_Vao_File(int rows, int cols, bool** arrA, bool** arrB, ofstream &ofs) {
	ofs << "Toa do trung nhau cua 2 con robot lan luot la: " << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (arrA[i][j] == 0 && arrB[i][j] == 0) {
				ofs << "(" << i << ", " << j << ") ";
			}
		}
	}
}

// hàm cấp phát bộ nhớ cho mảng 2 chiều kiểu bool
void Cap_phat_Mang_2_Chieu(bool**&arr, int rows, int cols) {
	arr = new bool* [rows];
	for (int i = 0; i < rows; ++i) {
		arr[i] = new bool[cols];
	}
}
// hàm giải phóng bộ nhớ cho mảng 2 chiều kiểu bool
void giai_phong_bo_nho(bool **arr, int rows) {
	for (int i = 0; i < rows; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
}
// hàm giải phóng bộ nhớ cho mảng 1 chiều kiểu int
void giaiphong_bonho(int* a) {
	delete[] a;
}
void remove_element(int *&DuongDi ,int &count_gia_tri) {
	int count_num = 0;
	for (int i = 0; i < count_gia_tri; ++i) {
		if (DuongDi[i] != 0) {
			DuongDi[count_num++] = DuongDi[i]; 
		}
	}
	count_gia_tri = count_num;
	int* newArr = new int[count_gia_tri];
	for (int i = 0; i < count_gia_tri; i++) {
		newArr[i] = DuongDi[i];
	}
	delete[] DuongDi;
	DuongDi = newArr;
}
// hàm in ra menu cho người chơi
int show_menu() {
	int choice;
	cout << "\033[34m" << "-----------------------------------" << "\033[0m" << endl;
	cout << "\033[34m" << "|\033[31m" << "    WELCOME YOU TO ROBOT GAME" << "\033[0m"  << "\033[34m    |\033[0m" << endl;
	cout << "\033[34m" << "|                                 |" << "\033[0m" << endl;
	cout << "\033[34m" << "|	       \033[35mi_i\033[0m                \033[34m|\033[0m" << endl;
	cout << "\033[34m" << "|	      \033[35m[O_O]\033[0m	          \033[34m|\033[0m" << endl;
	cout << "\033[34m" << "|            \033[35m/|___|\\ \033[0m             \033[34m|\033[0m" << endl;
	cout << "\033[34m" << "|            \033[35m |___|\033[0m               \033[34m|\033[0m" << endl;
	cout << "\033[34m" << "|             \033[35md   b\033[0m	          \033[34m|\033[0m" << endl;
	cout << "\033[34m" << "|                                 |" << "\033[0m" << endl;
	cout << "\033[34m" << "-----------------------------------" << "\033[0m" << endl;
	cout << "======================MENU-GAME======================" << endl;
	cout << "|                                                   |" << endl;
	cout << "|1. Che doi choi 1 robot                            |" << endl;
	cout << "|2. Che doi choi 2 robot di chuyen trung nhau       |" << endl;
	cout << "|3. Che doi choi 2 robot di chuyen khong trung nhau.|" << endl;
	cout << "|0. Thoat chuong trinh.                             |" << endl;
	cout << "|                                                   |" << endl;
	cout << "=====================================================" << endl;
	cout << "Nhap lua chon cua ban: "; cin >> choice;
	return choice;
}
void ghi_KetQua1Robot_vao_file(ofstream &ofs, int* DuongDi, int size, int Tong_diem) {
	ofs << "Tong Diem cua robot: " << Tong_diem << endl;
	ofs << "So o ma robot da di: " << size << endl;
	ofs << "Gia tri tai cac o ma robot da di: " << endl;
	for (int i = 0; i < size; ++i) {
		ofs << DuongDi[i] << " ";
	}
}
void ghi_KetQua2Robot_vao_file(ofstream& ofs, int* DuongDiA, int* DuongDiB, int sizeA, int sizeB, int Tong_diemA, int Tong_diemB) {
	ofs << "Tong Diem Robot A: " <<  Tong_diemA << endl;
	ofs << "So o ma robot A da di: " << sizeA << endl;
	ofs << "Gia tri tai cac o ma robot A da di : " << endl;
	for (int i = 0; i < sizeA; ++i) {
		ofs << DuongDiA[i] << " ";
	}
	ofs << endl;
	ofs << "Tong diem Robot B: " << Tong_diemB << endl;
	ofs << "So o ma robot B da di: " << sizeB << endl;
	ofs << "Gia tri tai cac o ma robot B da di : " << endl;
	for (int i = 0; i < sizeB; ++i) {
		ofs << DuongDiB[i] << " ";
	}
	ofs << endl;
}
void Ghi_File_Winner(int Tong_diemA, int Tong_diemB, ofstream &ofs) {
	if (Tong_diemA > Tong_diemB) {
		ofs << "Robot A Thang!" << endl;
	}
	else if (Tong_diemA < Tong_diemB) {
		ofs << "Robot B Thang!" << endl;
	}
	else {
		ofs << "Hoa!" << endl;
	}
}
int main() {
	int rows, cols, continue_playing = 1;
	ifstream ifs;
	ifs.open("Input.txt", ios_base::in);// mở file Input.txt để đọc
	if (!ifs.is_open()) {
		cout << "Khong doc duoc file" << endl;
	}
	ifs >> rows >> cols;
	if (rows <= 0 || cols <= 0) {
		cout << "So hang hoac so cot khong hop le." << endl;
		cout << "Vui long kiem tra lai file input." << endl;
		return 0;
	}
	Nhap(a, rows, cols, ifs);
	while (continue_playing) {
		int choice = show_menu();
		do {
			if (choice < 0 || choice > 3) {
				cout << "Lua chon cua ban khong hop le!" << endl;
				cout << "Yeu cau nhap lai. " << endl;
				this_thread::sleep_for(chrono::seconds(1));
				system("cls");
				choice = show_menu();
			}
		} while (choice < 0 || choice > 3);
		system("cls");
		if (choice == 0) {
			cout << "======================================" << endl;
			cout << "|                                    |" << endl;
			cout << "| Cam on ban da trai nghiem tro choi |" << endl;
			cout << "|                                    |" << endl;
			cout << "===============\033[105mGOOD BYE\033[0m===============";
			return 0;
		}
		else if (choice == 1) {
			Robot robotA;
			cout << "------------------------------" << endl;
			cout << "|                            |" << endl;
			cout << "|\033[33m" << "   Ban chon che do 1 robot" << "\033[0m  |" << endl;
			cout << "|                            |" << endl;
			cout << "------------------------------" << endl;
			print_map(a, rows, cols);
			do {
				cout << "LUU Y: CHI DUOC NHAP CHU SO CHO THONG SO CUA ROBOT!" << endl;
				cout << "Nhap thong so cua robot A " << endl;
				cin >> robotA;
				if (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0) {
					cout << "Thong so ban nhap khong hop le.\n";
					cout << "Vui long nhap lai\n";
				}
			} while (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0);
			system("cls");
			robotA = { robotA.x, robotA.y, a[robotA.x][robotA.y] };
			this_thread::sleep_for(chrono::seconds(1));
			cout << robotA;
			this_thread::sleep_for(chrono::seconds(1));
			bool** arrA = NULL;
			Cap_phat_Mang_2_Chieu(arrA, rows, cols);
			danh_dau_cac_o(arrA, rows, cols);
			// cấp phát một mảng để có thể lưu trữ các giá trị mà robot đã đi qua với số phần tử tối đa chính là số hàng * số cột 
			int* DuongDi = new int[rows * cols];
			int count_gia_tri = 0;
			DuongDi[count_gia_tri] = robotA.total_values;
			int tongDiemRobotA = Duong_Di_Va_Tong_Diem_1Robot(a, robotA, rows, cols, arrA, DuongDi, count_gia_tri);
			this_thread::sleep_for(chrono::seconds(1));
			print_Map_1Robot(a, rows, cols, DuongDi, count_gia_tri);
			print_map(a, rows, cols);
			cout << "Gia tri tai cac o ma robot di qua: " << endl;
			Thong_So_Hanh_Trinh_Cua_Robot(DuongDi, count_gia_tri, arrA, rows, cols);
			cout << "Tong diem robotA dat duoc: " << tongDiemRobotA << endl;
			ofstream ofs;
			ofs.open("output.txt", ios_base::out);
			if (!ofs.is_open()) {
				cout << "Khong the mo file de ghi" << endl;
			}
			ghi_KetQua1Robot_vao_file(ofs, DuongDi, count_gia_tri, tongDiemRobotA);
			ofs.close();
			cout << "Ket qua da duoc ghi vao file output.txt thanh cong" << endl;
			giaiphong_bonho(DuongDi);
			giai_phong_bo_nho(arrA, rows);
		}
		else if (choice == 2) {
			set_Color(2);
			cout << "------------------------------" << endl;
			cout << "|                            |" << endl;
			cout << "|   Ban chon che do 2 robot  |" << endl;
			cout << "|                            |" << endl;
			cout << "------------------------------" << endl;
			set_Color(7);
			cout << "Day la Che Do choi 2 robot di chuyen trung nhau." << endl;
			print_map(a, rows, cols);
			typedef int* Mangchuagiatri;
			Mangchuagiatri DuongDiA, DuongDiB;
			DuongDiA = new int[rows * cols];
			DuongDiB = new int[rows * cols];
			Robot robotA, robotB;
			do {
				cout << "LUU Y: CHI DUOC NHAP CHU SO CHO THONG SO CUA ROBOT VA MOT TRONG HAI TOA DO CUA ROBOT PHAI KHAC NHAU!" << endl;
				do {
					cout << "Nhap thong so cua robot A " << endl;
					cin >> robotA;
					if (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0) {
						cout << "Thong so ban nhap khong hop le.\n";
						cout << "Vui long nhap lai\n";
					}
				} while (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0);
				do {
					cout << "Nhap thong so cua robot B " << endl;
					cin >> robotB;
					if (Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0) {
						cout << "Thong so ban nhap khong hop le.\n";
						cout << "Vui long nhap lai\n";
					}
				} while (Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0);
				if (robotA.x == robotB.x && robotA.y == robotB.y) {
					cout << "Toa Do cua 2 robot ban nhap da giong nhau!" << endl;
					cout << "YEU CAU NHAP LAI TOA DO" << endl;
				}
			} while ((robotA.x == robotB.x && robotA.y == robotB.y) || (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0 || Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0));
			system("cls");
			robotA = { robotA.x, robotA.y, a[robotA.x][robotA.y] };
			robotB = { robotB.x, robotB.y, a[robotB.x][robotB.y] };
			int count_gia_tri_A = 0, count_gia_tri_B = 0;
			DuongDiA[count_gia_tri_A] = robotA.total_values;
			DuongDiB[count_gia_tri_B] = robotB.total_values;
			cout << "Robot A: " << endl;
			cout << robotA;
			this_thread::sleep_for(chrono::seconds(1));
			cout << "Robot B: " << endl;
			cout << robotB;
			typedef bool** boolPointer;
			boolPointer arrA = NULL, arrB = NULL;
			Cap_phat_Mang_2_Chieu(arrA, rows, cols);
			Cap_phat_Mang_2_Chieu(arrB, rows, cols);
			danh_dau_cac_o(arrA, rows, cols);
			danh_dau_cac_o(arrB, rows, cols);
			this_thread::sleep_for(chrono::seconds(1));
			cout << "Robot A bat dau tai toa do (" << robotA.x << ", " << robotA.y << ")" << endl;
			cout << "Robot B bat dau tai toa do (" << robotB.x << ", " << robotB.y << ")" << endl;
			this_thread::sleep_for(chrono::seconds(1));
			int TongDiemRobotA = Duong_Di_Va_Tong_Diem_1Robot(a, robotA, rows, cols, arrA, DuongDiA, count_gia_tri_A);
			int TongDiemRobotB = Duong_Di_Va_Tong_Diem_1Robot(a, robotB, rows, cols, arrB, DuongDiB, count_gia_tri_B);
			print_Map_2Robot(a, rows, cols, DuongDiA, DuongDiB, count_gia_tri_A, count_gia_tri_B);
			print_map(a, rows, cols);
			cout << "Hanh trinh cua robot A: " << endl;
			Thong_So_Hanh_Trinh_Cua_Robot(DuongDiA, count_gia_tri_A, arrA, rows, cols);
			cout << "Hanh trinh cua robot B: " << endl;
			Thong_So_Hanh_Trinh_Cua_Robot(DuongDiB, count_gia_tri_B, arrB, rows, cols);
			Toa_Do_Trung_Nhau_Cua_2_Robot(rows, cols, arrA, arrB);
			cout << "So Diem cua robotA: " << TongDiemRobotA << endl;
			cout << "So Diem cua robotB: " << TongDiemRobotB << endl;
			Tong_Diem_Robot(TongDiemRobotA, TongDiemRobotB);
			ofstream ofs;
			ofs.open("output.txt", ios_base::out);
			if (!ofs.is_open()) {
				cout << "Khong the mo file de ghi" << endl;
			}
			ghi_KetQua2Robot_vao_file(ofs, DuongDiA, DuongDiB, count_gia_tri_A, count_gia_tri_B, TongDiemRobotA, TongDiemRobotB);
			Ghi_File_Winner(TongDiemRobotA, TongDiemRobotB, ofs);
			Ghi_Toa_Do_Trung_Nhau_Cua_2_Robot_Vao_File(rows, cols, arrA, arrB, ofs);
			ofs.close();
			cout << "Ket qua da duoc dua vao file output.txt. " << endl;
			giai_phong_bo_nho(arrA, rows);
			giai_phong_bo_nho(arrB, rows);
			giaiphong_bonho(DuongDiA);
			giaiphong_bonho(DuongDiB);
		}
		else if (choice == 3) {
			cout << "------------------------------" << endl;
			cout << "|                            |" << endl;
			cout << "|   Ban chon che do 2 robot  |" << endl;
			cout << "|                            |" << endl;
			cout << "------------------------------" << endl;
			cout << "Day la Che Do choi 2 robot di chuyen doc lap." << endl;
			Robot robotA, robotB;
			print_map(a, rows, cols);
			do {
				cout << "LUU Y: CHI DUOC NHAP CHU SO CHO THONG SO CUA ROBOT!" << endl;
				do {
					cout << "Nhap thong so cua robot A " << endl;
					cin >> robotA;
					if (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0) {
						cout << "Thong so ban nhap khong hop le.\n";
						cout << "Vui long nhap lai\n";
					}
				} while (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0);
				do {
					cout << "Nhap thong so cua robot B " << endl;
					cin >> robotB;
					if (Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0) {
						cout << "Thong so ban nhap khong hop le.\n";
						cout << "Vui long nhap lai\n";
					}
				} while (Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0);
			} while (Kiem_tra_thong_tin_Robot(robotA, rows, cols, a) == 0 || Kiem_tra_thong_tin_Robot(robotB, rows, cols, a) == 0);
			system("cls");
			typedef int* Mangchuagiatri;
			Mangchuagiatri DuongDiA, DuongDiB;
			DuongDiA = new int[rows * cols];
			DuongDiB = new int[rows * cols];
			robotA = { robotA.x, robotA.y, a[robotA.x][robotA.y] };
			robotB = { robotB.x, robotB.y, a[robotB.x][robotB.y] };
			int count_gia_tri_A = 0, count_gia_tri_B = 0;
			DuongDiA[count_gia_tri_A] = robotA.total_values;
			DuongDiB[count_gia_tri_B] = robotB.total_values;
			int TongdiemRobotA = robotA.total_values;
			int TongdiemRobotB = robotB.total_values;
			cout << "Robot A: " << endl;
			cout << robotA;
			this_thread::sleep_for(chrono::seconds(1));
			cout << "Robot B: " << endl;
			cout << robotB;
			this_thread::sleep_for(chrono::seconds(1));
			bool** arr = NULL;
			Cap_phat_Mang_2_Chieu(arr, rows, cols);
			danh_dau_cac_o(arr, rows, cols);
			int tongDiem2Robot = Duong_Di_2Robot(a, robotA, robotB, rows, cols, arr, DuongDiA, DuongDiB, count_gia_tri_A, count_gia_tri_B, TongdiemRobotA, TongdiemRobotB);
			remove_element(DuongDiA, count_gia_tri_A);
			remove_element(DuongDiB, count_gia_tri_B);
			print_Map_2Robot(a, rows, cols, DuongDiA, DuongDiB, count_gia_tri_A, count_gia_tri_B);
			this_thread::sleep_for(chrono::seconds(1));
			print_map(a, rows, cols);
			cout << "Gia tri tai cac toa do ma robot A da di qua: " << endl;
			Thong_So_Hanh_Trinh_Cua_Robot(DuongDiA, count_gia_tri_A, arr, rows, cols);
			cout << "Gia tri tai cac toa do ma robot B da di qua: " << endl;
			Thong_So_Hanh_Trinh_Cua_Robot(DuongDiB, count_gia_tri_B, arr, rows, cols);
			cout << "Tong diem cua robot A: " << TongdiemRobotA << endl;
			cout << "Tong diem cua robot B: " << TongdiemRobotB << endl;
			ofstream ofs;
			ofs.open("output.txt", ios_base::out);
			if (!ofs.is_open()) {
				cout << "Khong the mo file de ghi" << endl;
			}
			ghi_KetQua2Robot_vao_file(ofs, DuongDiA, DuongDiB, count_gia_tri_A, count_gia_tri_B, TongdiemRobotA, TongdiemRobotB);
			ofs.close();
			cout << "Ket qua da duoc ghi vao file output.txt " << endl;
			giaiphong_bonho(DuongDiA);
			giaiphong_bonho(DuongDiB);
			giai_phong_bo_nho(arr, rows);
		}
		cout << "Ban co muon tiep tuc choi tiep khong? (1: CO / 0: KHONG)" << endl;
		cout << "Lua chon cua ban: "; cin >> continue_playing;
		system("cls");
		if (continue_playing == 0) {
			cout << "======================================" << endl;
			cout << "|                                    |" << endl;
			cout << "| Cam on ban da trai nghiem tro choi |" << endl;
			cout << "|                                    |" << endl;
			cout << "===============\033[105mGOOD BYE\033[0m===============";
			return 0;
		}
	}
	// thao tác đóng file
	ifs.close();
	return 0;
}