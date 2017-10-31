// snake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"	//Include list��stack��iostream��cstdlib��memory head files

/**
 * Author:Saurik
 * www.ithot.top
 * Using C++11
 * Coding With Visual Studio 2012
 * Please do not remove this line if you tranfer those files.
 * Last release time: 17-05-2013
**/

namespace MMP
{
	typedef unsigned int usi;
	typedef unsigned long usl;
	typedef unsigned short uss;
};

#define MAX_BG 25
#define �� 0
#define �� 1
#define �� 2
#define �� 3

mutex LK;
mutex FSK;
extern void StartT(MMP::uss*, BOOL*, MMP::usi);

class SnackBD {
protected:
	MMP::usi x;				//λ�ô����Ͻǿ�ʼ										-------------------------------------------------
	MMP::usi y;				//xyΪ�������Լ����ϵ��µı���						|x=1,y=1	x=2,y=1
public:												//								|x=1,y=2
	virtual MMP::usi GetX() { return this->x; };	//								|
	virtual MMP::usi GetY() { return this->y; };//									|
	SnackBD(MMP::usi xi, MMP::usi yi) { this->x = xi; this->y = yi; };//			|
	void operator = (SnackBD v_Buf) { this->x = v_Buf.GetX(); this->y = v_Buf.GetY(); };
	virtual MMP::usi Up() { this->y--; return 1; };
	virtual MMP::usi Down() { this->y++; return 1; };
	virtual MMP::usi Right() { this->x++; return 1; };
	virtual MMP::usi Left() { this->x--; return 1; };
	virtual void Set(MMP::usi xx, MMP::usi yy) { this->x = xx; this->y = yy; };
	BOOL operator == (SnackBD &v_Buf) { if (this->GetX() == v_Buf.GetX() && this->GetY() == v_Buf.GetY())return TRUE; return FALSE; };
};

BOOL FirstIns(shared_ptr<list<SnackBD> > XXX)						//��ʼ�� �ߵ�����
{
	XXX->push_front(SnackBD (1,1));
	XXX->push_front(SnackBD(2, 1));
	XXX->push_front(SnackBD(3, 1));
	return TRUE;
};

template<class T> BOOL Chk_G(T n_chk, list<T> Ori)//						�жϺ���
{
	if (n_chk.GetX() == 0 || n_chk.GetY() == 0 || n_chk.GetX() == MAX_BG || n_chk.GetY() == MAX_BG)return FALSE;
	list<T>::iterator a = Ori.begin();
	while (a != Ori.end())
	{
		if (n_chk==*a) return FALSE;				//�˳���Ϸ����
		a++;
	}
	return TRUE;
};

BOOL PcsUp(shared_ptr<list<SnackBD> > XXX)			//����
{
	list<SnackBD>::iterator KKK = XXX->begin();
	SnackBD p_Buf = XXX->front();
	p_Buf.Up();											//���ú���
	list<SnackBD> y_Buf = *XXX;							//������ʱ����
	if (!Chk_G<SnackBD>(p_Buf, y_Buf)) return FALSE;	//�жϺ���
	SnackBD o_Buf = XXX->front();
	KKK->Up();
	KKK++;
	while (KKK != XXX->end())
	{
		SnackBD LLLBBB = *KKK;							//���£���ÿ���ڶΣ������ݣ��滻Ϊ��һ���ڶε�����
		*KKK = o_Buf;
		o_Buf = LLLBBB;
		KKK++;
	}
	return TRUE;										//�����⣬��������
};

BOOL PcsDown(shared_ptr<list<SnackBD> > XXX)			//����
{
	list<SnackBD>::iterator KKK = XXX->begin();
	SnackBD p_Buf = XXX->front();
	p_Buf.Down();
	list<SnackBD> y_Buf = *XXX;
	if (!Chk_G<SnackBD>(p_Buf, y_Buf)) return FALSE;
	SnackBD o_Buf = XXX->front();
	KKK->Down();
	KKK++;
	while (KKK != XXX->end())
	{
		SnackBD LLLBBB = *KKK;
		*KKK = o_Buf;
		o_Buf = LLLBBB;
		KKK++;
	}
	return TRUE;
};

BOOL PcsLeft(shared_ptr<list<SnackBD> > XXX)			//����
{
	list<SnackBD>::iterator KKK = XXX->begin();
	SnackBD p_Buf = XXX->front();
	p_Buf.Left();
	list<SnackBD> y_Buf = *XXX;
	if (!Chk_G<SnackBD>(p_Buf, y_Buf)) return FALSE;
	SnackBD o_Buf = XXX->front();
	KKK->Left();
	KKK++;
	while (KKK != XXX->end())
	{
		SnackBD LLLBBB = *KKK;
		*KKK = o_Buf;
		o_Buf = LLLBBB;
		KKK++;
	}
	return TRUE;
};

BOOL PcsRight(shared_ptr<list<SnackBD> > XXX)			//����
{
	list<SnackBD>::iterator KKK = XXX->begin();
	SnackBD p_Buf = XXX->front();
	p_Buf.Right();
	list<SnackBD> y_Buf = *XXX;
	if (!Chk_G<SnackBD>(p_Buf, y_Buf)) return FALSE;
	SnackBD o_Buf = XXX->front();
	KKK->Right();
	KKK++;
	while (KKK != XXX->end())
	{
		SnackBD LLLBBB = *KKK;
		*KKK = o_Buf;
		o_Buf = LLLBBB;
		KKK++;
	}
	return TRUE;
};

BOOL ControlPcs(shared_ptr<list<SnackBD> > XXX, MMP::uss QQQ)
{																//�ܿ��ƺ���
	switch (QQQ)
	{
	case ��:
		return PcsLeft(XXX);									//���ݷ����������
	case ��:
		return PcsRight(XXX);
	case ��:
		return PcsUp(XXX);
	case ��:
		return PcsDown(XXX);
	default:
		return FALSE;
	}
};

inline stringstream PrintSnack(shared_ptr<list<SnackBD> > XXX,SnackBD Food)
{																				//��ͼ��������Ҫ������
	register string BK;
	for (int l = 1; l <= MAX_BG; l++)
	{
		BK += "��";
	}
	stringstream Object;
	Object << BK<< endl;														//���ݶ�������ռ��ͼ
	for (MMP::usi b = 1; b < MAX_BG - 1; b++)
	{
		vector <MMP::usi> DoFer;
		DoFer.clear();
		if (Food.GetY() == b) DoFer.push_back(Food.GetX());
		list<SnackBD>::iterator a = XXX->begin();
		while (a!=XXX->end())
		{
			if (a->GetY() == b)DoFer.push_back(a->GetX());
			a++;
		};
		if (DoFer.empty())
		{
			Object << "��"<<"                                              "<<"��"<<endl;
		}
		else
		{
			sort(DoFer.begin(), DoFer.end());
			MMP::usi SSSS = DoFer.size();
			MMP::usi PPPP = 1;
			Object << "��";
			for (MMP::usi m = 0;m<SSSS;m++)
			{
				string l_Buf("");
				MMP::usi frst = DoFer.at(m);
				for (MMP::usi k = PPPP; k < frst; k++)
				{
					l_Buf += "  ";
				};
				PPPP = frst + 1;
				Object << l_Buf << "��";
			};
			for (MMP::usi r = PPPP; r < MAX_BG - 1; r++)
			{
				Object << "  ";
			}
			Object << "��" << endl;
		};
	};
	Object << BK << endl;														//ʹ���ַ������洢���ݣ������ַ�������ÿһ�������Ϊһ���ַ�������
	return Object;
};
SnackBD GoFood(shared_ptr<list<SnackBD> > XXX, MMP::usi LuCoDe);
SnackBD GoFood(shared_ptr<list<SnackBD> > XXX)
{
	if (XXX->size() >= MAX_BG*MAX_BG) throw "Logic Error";
	MMP::usi LuCode = 0;
	srand(time(0));																		//����ʳ��
	SnackBD FOODS(1 + rand() % (MAX_BG - 2), 1 + rand() % (MAX_BG - 2));
	for (list<SnackBD>::iterator iii = XXX->begin(); iii != XXX->end(); iii++)
	{																					//�ж��ǲ�����������
		if (*iii == FOODS)
		{
			LuCode++;
			FOODS = GoFood(XXX, LuCode);
		};
	};
	return FOODS;
};

SnackBD GoFood(shared_ptr<list<SnackBD> > XXX,MMP::usi LuCoDe)									//�Ե���ѭ�����������ڱ�֤ʳ�ﲻ����������
{
	if (XXX->size() >= (MAX_BG*MAX_BG - MAX_BG)) throw "Logic Error";
	MMP::usi LuCode = LuCoDe;
	srand(time(0)+LuCoDe);
	SnackBD FOODS(1 + rand() % (MAX_BG - 2), 1 + rand() % (MAX_BG - 2));
	for (list<SnackBD>::iterator iii = XXX->begin(); iii != XXX->end(); iii++)
	{
		if (*iii == FOODS)
		{
			LuCode++;
			FOODS = GoFood(XXX, LuCode);
		};
	};
	return FOODS;
};

SnackBD AddHead(SnackBD OriHead, MMP::uss Direction)
{
	switch (Direction)													//����õ�ʳ��Ͱ�ʳ�����ͷ���棬ע��Ҫ�뷽����ͬ����������
	{
	case ��:
		OriHead.Left();
		return OriHead;
	case ��:															//����ͷ�󣬷�����ͷ����
		OriHead.Right();
		return OriHead;
	case ��:
		OriHead.Up();
		return OriHead;
	case ��:
		OriHead.Down();
		return OriHead;
	default:
		return OriHead;
	}
};


static MMP::uss OOXX = TRUE;


void StartT(MMP::uss* u_key,BOOL* t_chk, MMP::usi SleepT)
{
	srand(time(0));																//��Ҫ�߳�
	shared_ptr<list<SnackBD> > FFF(new list<SnackBD>[4096]);
	if (!FFF->empty()) throw "Unknown Error"; else FirstIns(FFF);
	SnackBD TheFood = GoFood(FFF);
QQPP:
	while (*t_chk)
	{
		FSK.lock();
		system("cls");
		LK.try_lock();
		if (!ControlPcs (FFF, *u_key)) *t_chk = FALSE;
		if (FFF->front() == TheFood) { FFF->push_front(AddHead(FFF->front(), *u_key)); TheFood = GoFood(FFF); };
		stringstream LLL = PrintSnack(FFF, TheFood);
		while (!LLL.eof())
		{
			string EEE;
			getline(LLL, EEE);
			cout << EEE << endl;
		};
		LK.unlock();
		FSK.unlock();
		Sleep(SleepT);
	};
	system("cls");
	cout << "\xcf\xdf\xb3\xcc\xcd\xa3\xd6\xb9\xa3\xac\xca\xc7\xb7\xf1\xd6\xd8\xd0\xc2\xbd\xf8\xd0\xd0\xd3\xce\xcf\xb7\xa3\xbf\x79\x2f\x6e\x3f" << endl;
	char q = getch();
	if (q == 'y') { *t_chk = TRUE; FFF->clear(); FirstIns(FFF); TheFood = GoFood(FFF); goto QQPP; }
	else
	LK.try_lock();
	FFF->clear();
	printf("Exit command found......\nPlease Wait.\n");
	OOXX = FALSE;
	LK.unlock();
	ExitProcess(0x1e);				//�������ر���ǿ�ƽ���ȫ���̡߳�
	return;
};

void ControlT(MMP::uss* u_key, BOOL* t_chk, BOOL* Status_Chk)				//�����̣߳����첽���ƣ��������ᵼ�¿����ӳ�
{
AAAA:
	while (*t_chk)
	{
		if (kbhit())
		{
			FSK.lock();
			char cbyte = getch();
			if (cbyte == 'q') { *t_chk = FALSE; while (OOXX) { srand(time(0)); Sleep(rand() % 2000 + 3000); if (*t_chk == TRUE)goto AAAA; }; LK.try_lock(); system("cls"); cout << "�ȴ�ȫ���ڴ���Դ������...\n�����Ӱ����������ֱ����ȫ�ɹ�����ʾ��" << endl; LK.unlock(); *Status_Chk = FALSE; return; }
			else if (cbyte == 'w') { *u_key = ��; }
			else if (cbyte == 's') { *u_key = ��; }
			else if (cbyte == 'a') { *u_key = ��; }
			else if (cbyte == 'd') { *u_key = ��; }							//�������жϣ�д��ָ����ָ���ڴ���С�
			FSK.unlock();
		}
		Sleep(50);
	}
	*Status_Chk = FALSE;
}
void WelMain(MMP::usi*);

int main()
{
	SetConsoleTitle(L"\x69\x53\x6e\x61\x6b\x65\x20\x42\x79\x20\x53\x61\x75\x72\x69\x6b\x20\x2d\x55\x73\x69\x6e\x67\x20\x43\x50\x50\x31\x34");
	BOOL *LLLLL = new BOOL [16]; *LLLLL = TRUE;
	BOOL *ZZZZ = new BOOL[16]; *ZZZZ = TRUE;
	MMP::uss *MMMMM = new MMP::uss [4];*MMMMM = ��;
	MMP::usi *SleepT = new MMP::usi [36];
	*SleepT = 1000;
	thread LLL(WelMain, SleepT);
	if (LLL.joinable()) LLL.join();
	thread SSS(StartT, MMMMM, LLLLL, *SleepT);
	thread GGG(ControlT, MMMMM, LLLLL, ZZZZ);
	SSS.detach();
	GGG.detach();
	while (ZZZZ)
	{
		srand(time(0));
		Sleep(5000 + rand()%8000);
	}
	delete ZZZZ; delete MMMMM; delete LLLLL;
	system("cls");
	cout << "\xc4\xda\xb4\xe6\xd7\xca\xd4\xb4\xc7\xe5\xc0\xed\xcd\xea\xb3\xc9\xa3\xac\xb1\xe4\xc1\xbf\x20\xc7\xe5\xc0\xed\xcd\xea\xc8\xab\xb3\xc9\xb9\xa6\xa3\xac\xcf\xd6\xd4\xda\xbf\xc9\xd2\xd4\xcd\xcb\xb3\xf6\xc1\xcb\xa1\xa3" << endl;
	system("pause");
    return 0;
}

void OutPut(string LLLLOOOO)							//Ԥ����˫�������
{
	//��ȡĬ�ϱ�׼��ʾ���������
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//�����µĻ�����
	HANDLE hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//�����µĻ�����Ϊ���ʾ����
	SetConsoleActiveScreenBuffer(hOutBuf);
	//���������������Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);
	//˫���崦����ʾ
	DWORD bytes = 0;
	char PPPKKK[8888];
	cout << LLLLOOOO;
	ReadConsoleOutputCharacterA(hOutput, PPPKKK, 4096, coord, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, PPPKKK, 4096, coord, &bytes);
};


void WelMain(MMP::usi *SleepT)
{
	/*
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = GetForegroundWindow();//���ھ��
	nid.uID = NULL;//ͼ��
	//nid.hIcon = ::LoadIcon(NULL, MAKEINTRESOURCE(NULL));//����ͼ��
	nid.uCallbackMessage = NULL;//��Ϣ�����������Ҫ�����������
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	_tcscpy(nid.szTip, _T("Snake"));
	Shell_NotifyIcon(NIM_ADD, &nid);
	*/
	BOOL Direct = FALSE;
	while (!Direct)
	{
		system("cls");
		cout << "\xbb\xb6\xd3\xad\xc0\xb4\xb5\xbd\xcc\xb0\xb3\xd4\xc9\xdf\xa3\xac\xb0\xe6\xb1\xbe\x31\x2e\x30\xa3\xac\xd7\xf7\xd5\xdf\x53\x61\x75\x72\x69\x6b" << endl;
		cout << "\xce\xd2\xc3\xc7\xb5\xc4\xcd\xf8\xd5\xbe\xca\xc7\xa3\xba\x68\x74\x74\x70\x3a\x2f\x2f\x77\x77\x77\x2e\x33\x67\x65\x6e\x67\x2e\x63\x6e\x2f" << endl;
		cout << "\xd7\xf7\xd5\xdf\xd3\xca\xcf\xe4\xa3\xba\x6b\x69\x6e\x67\x40\x69\x74\x68\x6f\x74\x2e\x74\x6f\x70" << endl;
		cout << "\xcf\xd6\xd4\xda\xc7\xeb\xca\xe4\xc8\xeb\xcb\xa2\xd0\xc2\xba\xc1\xc3\xeb\xca\xfd\xa3\xa8\x31\xc3\xeb\xb5\xc8\xd3\xda\x31\x30\x30\x30\xba\xc1\xc3\xeb\xa3\xa9\xd2\xd4\xb5\xf7\xd5\xfb\xd3\xce\xcf\xb7\xc4\xd1\xb6\xc8" << endl;
		MMP::usi DDDQQQ = 500;
		cin >> DDDQQQ;
		if (DDDQQQ > 10000 || DDDQQQ < 100)
		{
			cout << "\xc7\xeb\xca\xe4\xc8\xeb\x31\x30\x30\xb5\xbd\x31\x30\x30\x30\x30\xd6\xae\xbc\xe4\xb5\xc4\xca\xfd\xd6\xb5" << endl;
			system("pause");
		}
		else
		{
			*SleepT = DDDQQQ;
			Direct = TRUE;
			SetWindowTextA(GetConsoleWindow(), "iSnake -Using CPP14");
		}
	}
	return;
};



/** ����CUDA���ٲ��֣���Ҫ�ȴ���CUDA����
 * ע�������CUDA����ר�õ�
 * ������д���Կ������
 * --- CUDA ���̼߳���ʵ�ִ��� By Saurik



inline void checkCudaErrors(cudaError err)//��������
{
if (cudaSuccess != err)
{
fprintf(stderr, "CUDA Runtime API error: %s.\n", cudaGetErrorString(err));
return;
}
}

__global__ void add(int *a,int *b,int *c)//����˺���
{
int tid = blockIdx.x*blockDim.x+threadIdx.x;
for (size_t k = 0; k < 50000; k++)
{
c[tid] = a[tid] + b[tid];
}
}

extern "C" int runtest(int *host_a, int *host_b, int *host_c)
{
int *dev_a, *dev_b, *dev_c;

checkCudaErrors(cudaMalloc((void**)&dev_a, sizeof(int)* datasize));//�����Կ��ڴ�
checkCudaErrors(cudaMalloc((void**)&dev_b, sizeof(int)* datasize));
checkCudaErrors(cudaMalloc((void**)&dev_c, sizeof(int)* datasize));

checkCudaErrors(cudaMemcpy(dev_a, host_a, sizeof(int)* datasize, cudaMemcpyHostToDevice));//�����������������ڴ�鸴�Ƶ��Կ��ڴ���
checkCudaErrors(cudaMemcpy(dev_b, host_b, sizeof(int)* datasize, cudaMemcpyHostToDevice));

add << <datasize / 100, 100 >> >(dev_a, dev_b, dev_c);//�����Կ���������
checkCudaErrors(cudaMemcpy(host_c, dev_c, sizeof(int)* datasize, cudaMemcpyDeviceToHost));//���Կ����������ݿ�����

cudaFree(dev_a);//�����Կ��ڴ�
cudaFree(dev_b);
cudaFree(dev_c);
return 0;
}

extern "C" int runtest(int *host_a, int *host_b, int *host_c);//�Կ�������

int main()
{
int a[datasize], b[datasize], c[datasize];
for (size_t i = 0; i < datasize; i++)
{
a[i] = i;
b[i] = i*i;
}


 * ��һ���ǵ����Կ��������ݵģ����Խ�������Ϊ�Կ�����
 * �����г���
 * ̰���ߵĴ󲿷ּ��㶼����ͨ���Կ�
 * By Saurik 2017 07 04


long now1 = clock();//�洢ͼ����ʼʱ��
runtest(a,b,c);//�����Կ�����
printf("GPU����ʱ��Ϊ��%dms\n", int(((double)(clock() - now1)) / CLOCKS_PER_SEC * 1000));//���GPU����ʱ��

long now2 = clock();//�洢ͼ����ʼʱ��
for (size_t i = 0; i < datasize; i++)
{
for (size_t k = 0; k < 50000; k++)
{
c[i] = (a[i] + b[i]);
}
}
printf("CPU����ʱ��Ϊ��%dms\n", int(((double)(clock() - now2)) / CLOCKS_PER_SEC * 1000));//���GPU����ʱ��

for (size_t i = 0; i < 100; i++)//�鿴������
{
printf("%d+%d=%d\n", a[i], b[i], c[i]);
}
getchar();
return 0;
}
*/
