#ifndef ___PROJECT_H___
#define ___PROJECT_H___

/* ���̺귯�� �������*/
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>
#include<conio.h>
#include<cstring>
#include<vector>
#include<cstdlib>
using namespace std;

/*�����Լ�, �� ��*/
void ScreenClear(int second=1);
namespace MAXSIZE
{
	enum
	{
		ID = 20, PASSWORD = 20, NAME = 16, AGE = 200,
		PHONE_NUMBER = 15, BUFFER = 999, ROOM_NAME = 30, ROOM_CAPACITY = 1000
	};
}
bool CinCheck(istream &cin); //�������� true

/*��ü ���� Ŭ����*/
class AllContral
{
private:
	static bool program;
public:
	void show();
	static void SetProgram(bool program);
};

/*ȸ������ Ŭ����*/
class MemberJoining
{
public:
	void show();
};

/*ȸ��Ż�� Ŭ����*/
class MemberIeave
{
public:
	void show();
};

/*ID Ŭ����*/
class ID
{
protected:
	string id;
	string password;
	ID(string id, string password);
};

/*ȸ�� Ŭ����*/
class Member : public ID
{
private:
	string name;
	int sex;
	int age;
	string phone_number;
public:
	Member(string id = "", string password = "", string name = "", int sex = 0, int age = 0, string phone_number = "");
	string GetId();
	string GetPassword();
	string GetName();
	int GetSex();
	int GetAge();
	string GetPhoneNumber();
	void GetData(string &id, string &password, string &name, int& sex, int& age, string& phone_number);
	void SetId(string id);
	void SetPassword(string password);
	void SetData(string id, string password, string name, int sex, int age, string phone_number);
	friend bool operator>>(ifstream &fin, Member &member);
	friend void operator<<(ofstream &fout, Member &member);
};

/*������ Ŭ����*/
class ReadingRoom
{
private:
	string name;
	int seat_capacity;	//�¼� ��
	int use;			//����� 1, ��� X 0
public:
	ReadingRoom(string name = "", int seat_capacity = 0, int use = 0);
	friend bool operator>>(ifstream &fin, ReadingRoom &reading_room);
	friend void operator<<(ofstream &fout, ReadingRoom &reading_room);
	void SetName(string name);
	void SetSeatCapacity(int seat_capacity);
	void SetUse(int use);
	string GetName();
	int GetSeatCapacity();
	int GetUse();
};

/*�¼� ���� Ŭ����*/
class SeatInformation
{
private:
	Member member;
	string reding_room_name;
	int seatnumber;		//�¼���ȣ 1~
	int extension_num;	//����Ƚ��
	tm start_time;
	tm end_time;
	tm extension_time;	//���尡�ɽð�
public:
	SeatInformation(Member& member, string reding_room_name, int seatnumber, int extension_num, tm start_time, tm end_time, tm extenstion_time);
	void SetExtensionNum(int extension_num);
	void SetStartTime(tm& start_time);
	void SetEndTime(tm& end_time);
	void SetExtensionTime(tm& extension_time);
	Member& GetMember();
	string GetRedingRoomName();
	int GetSeatNumber();
	int GetExtensionNum();
	tm& GetStartTime();
	tm& GetEndTime();
	tm& GetExtensionTime();
};

/*������ �ð� ����*/
class LimitTime
{
public:
	int hour; //0~23
	int min;  //0~59
	int sec;  //0~59
	LimitTime(int hour, int min, int sec);
};

/*�α��� Ŭ����*/
class ReadingRoomContral;
class Login
{
private:
	Member user;
public:
	void show(ReadingRoomContral& readingroomcontral);
	Member& GetUser();
	int LoginCheak(string &id, string& password);
};

/*������ ���� Ŭ����*/
class ReadingRoomContral
{
private:
	vector<ReadingRoom> room_vector;		//������ ��ü ����
	vector<SeatInformation> seat_vector;	//�¼����� ��ü ����
public:
	LimitTime append_time;				//����ð�
	LimitTime append_extenstion_time;	 //�߰�����ð�
	LimitTime close_time;				 //���ð�

	ReadingRoomContral();							//������ : ������������ �����͸� ������ ���ͷ� 
	void FileSet();									//������ ������ �����͸� ������ ���Ϸ�
	void Member_Show(Member& user);					//ȸ������ Show()�Լ�
	void SeatScreen(ReadingRoom& reading_room);		//�¼�ȭ�� ���
	void ChoiceReadingRoom();						//������ ����ȭ�� ���
	void Reservation(Member& user, string reading_room_name, int seatnumber);	//�����Լ�
	void AutoReturn();						//�ڵ� �ݳ��Լ�
	void Extension(int seat_vector_index);	//�����Լ�
	void ReadingRoomAppend(ReadingRoom &readingroom);	//������ �߰�
	bool ReadingRoomUseSet(int room_vector_index);		//������ Ȱ��,��Ȱ�� ���� (Ȱ��->��Ȱ��, ��Ȱ��->Ȱ��)
	ReadingRoom& GetRoomVetorElement(int room_vector_index);
};

/*������ Ŭ����*/
class Manager
{
public:
	void Show(ReadingRoomContral &readingroomcontral);
};
#endif