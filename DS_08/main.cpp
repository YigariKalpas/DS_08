#include<iostream>
#include<chrono>
#include<random>
#include"vector_m.h"	
#include"binary_tree.h"

using namespace std; 

//basic elements vector , in this program we are trying not to change this element expect during the initiallizaion period

vector_m<int> Target_Array;

vector_m<int> Bubble_m(const vector_m<int> & Array, long long& times){
	vector_m<int> temp_arr(Array);
	for (int i = 0; i < Array.Get_Size(); i++) {
		bool flag = 1;
		for (int j = Array.Get_Size() - 1 ; j > i; j--) {
			if (temp_arr[j] > temp_arr[j - 1]) {
				flag = 0; //simple update to cut few situations
				//quick swap of this two elements
				temp_arr.element_swap(j, j - 1);
				times++;
			}
		}
		if (flag)
			break;
	}
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

vector_m<int> Choose_m(const vector_m<int>& Array,long long &times) {
	vector_m<int> temp_arr(Array);
	for (int i = 0; i < Array.Get_Size(); i++) {
		int max_num = temp_arr[i];
		int best_position = i;
		for (int j = i; j < Array.Get_Size(); j++) {
			if (max_num < temp_arr[j]) {
				max_num = temp_arr[j];
				best_position = j;
			}
		}
		temp_arr.element_swap(i, best_position);
		times++;
	}
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

vector_m<int> Insert_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	for (int i = 1; i < Array.Get_Size(); i++) {
		int key = temp_arr[i]; 
		int j = i - 1;
		while (j >= 0 && key > temp_arr[j]) {
			temp_arr[j + 1] = temp_arr[j];
			times++;
			j--;
		}
		temp_arr[j + 1] = key;
	}
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

vector_m<int> Booline_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	if (Array.Get_Size() < 2) 
		return temp_arr ; // return an & element is not allowed, the return value of this function is hovered while it will be regarded as a template object and after the body where calls this function will error delete the array and let the secondly call of this function visit a nullptr datamemory
	int shell_divid = Array.Get_Size() / 2; //as the distance of each elements
	while (shell_divid) {
		for (int i = 0; i < Array.Get_Size(); i++) {
			int g = i + shell_divid;
			while (g < Array.Get_Size()) {
				int key = temp_arr[g];
				int p = g - shell_divid;
				while (p >= 0 && temp_arr[p] < key) {
					temp_arr[p + shell_divid] = temp_arr[p];
					times++;
					p -= shell_divid;
				}
				temp_arr[p + shell_divid] = key;
				g += shell_divid;
			}
		}
		shell_divid /= 2;
	}
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

/// <summary>
/// 
/// </summary>
/// <param name="Array"></param>
/// <param name="front_point"></param>
/// <param name="back_point"> as the open interval right boundary </param> 
void Fastsort_m(vector_m<int>& Array,int front_point,int back_point) {
	if (front_point >= back_point - 1)
		return;
	vector_m<int> temp_arr(Array);
	int pivot = Array[front_point];
	int comp = 0;
	int comp_back = back_point;
	for (int i = front_point; i < back_point; i++) {
		if (Array[i] > pivot) {
			temp_arr[comp++] = Array[i];
		}
		if(Array[i] < pivot) {
			temp_arr[--comp_back] = Array[i];
		}
	}
	while (comp < comp_back) {
		temp_arr[comp++] = pivot;
	}
	for (int i = front_point; i < back_point; i++) {
		Array[i] = temp_arr[i];
	}
	Fastsort_m(Array, 0, comp);
	Fastsort_m(Array, comp+1,back_point);
}

int Paritition1(vector_m<int>& A, int low, int high,long long &times) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] <= pivot) {
			--high;
		}
		A[low] = A[high];
		while (low < high && A[low] >= pivot) {
			++low;
		}
		A[high] = A[low];
		times++;
	}
	A[low] = pivot;
	return low;
}

/// <summary>
/// can use the queue to update this function and defuse the use of calling_return
/// </summary>
/// <param name="A"></param>
/// <param name="low"></param>
/// <param name="high"></param>
/// <param name="times"></param>
void QuickSort(vector_m<int>& A, int low, int high, long long& times) //entrance of the fast sort
{
	if (low < high) {
		int pivot = Paritition1(A, low, high,times);
		QuickSort(A, low, pivot - 1, times);
		QuickSort(A, pivot + 1, high, times);
	}
	return;
}

//the api called for the basic func
vector_m<int> Fast_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	QuickSort(temp_arr, 0, temp_arr.Get_Size()-1,times);
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

heap_m<int> Heap_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	heap_m<int> answer_heap;
	for (int i = 0; i < Array.Get_Size(); i++) {
		answer_heap.add_node(Array[i],answer_heap.head,times);
	}
	
#if debug_mode 
	answer_heap.show_heap();
#endif
	return answer_heap;
}

void reset_base(vector_m<int>& Array, int front ,int back) {

}

vector_m<int> Reset_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	reset_base(temp_arr, 0, Array.Get_Size());
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

vector_m<int> Basic_m(const vector_m<int>& Array, long long& times) {
	vector_m<int> temp_arr(Array);
	bool flag = 1;
	int count = 1;
	while (flag) {
		flag = 0;
		vector_m<vector_m<int>> base_bucket(10);
		for (int i = 0; i < Array.Get_Size(); i++) {
			if ((temp_arr[i] / count)!=0)
				flag = 1; //while the biggest number doesn't bigger than the count, need to break and get the answer
			base_bucket[(temp_arr[i] / count) % 10].push_back(temp_arr[i]);
		}
		int point = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < base_bucket[i].Get_Size(); j++) {
				temp_arr[point++] = base_bucket[i][j];
				times++;
			}
		}
		count *= 10;
	}
	for (int i = 0; i < Array.Get_Size() / 2; i++) {
		temp_arr.element_swap(i, Array.Get_Size() - i - 1);
	}
#if debug_mode 
	temp_arr.vector_show();
#endif
	return temp_arr;
}

/// <summary>
/// get the command from the cmd
/// </summary>
void Loop() {
	int menu_num = 9;
	long long swap_times = 0;
	cout << "\n请输入菜单中数字\n";
	cin >> menu_num;
	if (menu_num <= 0 || menu_num >= 10) {
		cout << "Input error\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		Loop();
	}
	if (menu_num == 9)
		return;
	auto start_time = chrono::high_resolution_clock::now();
	switch (menu_num) {
	case 1:
		Bubble_m(Target_Array, swap_times);
		break;
	case 2:
		Choose_m(Target_Array, swap_times);
		break;
	case 3:
		Insert_m(Target_Array, swap_times);
		break;
	case 4:
		Booline_m(Target_Array, swap_times);
		break;
	case 5:
		Fast_m(Target_Array, swap_times);
		break;
	case 6:
		Heap_m(Target_Array, swap_times);
		break;
	case 7:
		Reset_m(Target_Array, swap_times);
		break;
	case 8:
		Basic_m(Target_Array, swap_times);
		break;
	case 9:
		return;
	default:
		break;
	} //choose which algorithm to use 
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	cout <<"使用了"<<menu_num << "对应算法，此时用时为 : " << duration.count() << "微秒   " << endl;
	cout << "执行了" << swap_times << "次交换数据操作" << endl;
	Loop();
}

void Menu() {
	cout << "**             排序算法比较           **\n";
	cout << "**              1-冒泡排序            **\n";
	cout << "**              2-选择排序            **\n";
	cout << "**              3-直接插入            **\n";
	cout << "**              4-希尔排序            **\n";
	cout << "**              5-快速排序            **\n";
	cout << "**              6-堆排序              **\n";
	cout << "**              7-归并排序            **\n";
	cout << "**              8-基数排序            **\n";
	cout << "**              9-退出程序            **\n";
}

int main() {
	srand(time(0));
	Menu();
	try {
		Target_Array.reserve(100000); //在所有情况下给出最大的十万空间减少后续重分配vector内存造成时间开销
#if debug_mode
		cout << "Successful\n";
#endif
	}
	catch(const bad_alloc& e){
		cout << e.what();
		return -1;
	}
	int size = 0;
	cout << "请输入目标数组大小" << endl;
	cin >> size;
	if (size > 100000) {
		cout << "Oversize" << endl;
		return -2;
	}
	else {
		bool i = 0;
#if developer
		cout << "输入1以发生降序序列,0为正常序列\n";
		cin >> i;
		if (i) {
			for (int i = 0; i < size; i++) {
				Target_Array.push_back(100000 - i);
			}
		}

#endif
		if (!i) {
			for (int i = 0; i < size; i++) {
				Target_Array.push_back(rand() % 100000); //生成0-99999范围随机数
			}
		}
	}
	Loop();
	return 0;
}