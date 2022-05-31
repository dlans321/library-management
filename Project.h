#ifndef ___PROJECT_H___
#define ___PROJECT_H___

/* 라이브러리 헤더파일*/
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

/*전역함수, 그 외*/
void ScreenClear(int second=1);
namespace MAXSIZE
{
	enum
	{
		ID = 20, PASSWORD = 20, NAME = 16, AGE = 200,
		PHONE_NUMBER = 15, BUFFER = 999, ROOM_NAME = 30, ROOM_CAPACITY = 1000
	};
}
bool CinCheck(istream &cin); //오류나면 true

/*전체 제어 클래스*/
class AllContral
{
private:
	static bool program;
public:
	void show();
	static void SetProgram(bool program);
};

/*회원가입 클래스*/
class MemberJoining
{
public:
	void show();
};

/*회원탈퇴 클래스*/
class MemberIeave
{
public:
	void show();
};

/*ID 클래스*/
class ID
{
protected:
	string id;
	string password;
	ID(string id, string password);
};

/*회원 클래스*/
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

/*열람실 클래스*/
class ReadingRoom
{
private:
	string name;
	int seat_capacity;	//좌석 수
	int use;			//사용중 1, 사용 X 0
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

/*좌석 정보 클래스*/
class SeatInformation
{
private:
	Member member;
	string reding_room_name;
	int seatnumber;		//좌석번호 1~
	int extension_num;	//연장횟수
	tm start_time;
	tm end_time;
	tm extension_time;	//연장가능시간
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

/*도서관 시간 제한*/
class LimitTime
{
public:
	int hour; //0~23
	int min;  //0~59
	int sec;  //0~59
	LimitTime(int hour, int min, int sec);
};

/*로그인 클래스*/
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

/*열람실 제어 클래스*/
class ReadingRoomContral
{
private:
	vector<ReadingRoom> room_vector;		//열람실 객체 벡터
	vector<SeatInformation> seat_vector;	//좌석정보 객체 벡터
public:
	LimitTime append_time;				//연장시간
	LimitTime append_extenstion_time;	 //추가연장시간
	LimitTime close_time;				 //끝시간

	ReadingRoomContral();							//생성자 : 열람실파일의 데이터를 열람실 벡터로 
	void FileSet();									//열람실 벡터의 데이터를 열람실 파일로
	void Member_Show(Member& user);					//회원전용 Show()함수
	void SeatScreen(ReadingRoom& reading_room);		//좌석화면 출력
	void ChoiceReadingRoom();						//열람실 선택화면 출력
	void Reservation(Member& user, string reading_room_name, int seatnumber);	//예약함수
	void AutoReturn();						//자동 반납함수
	void Extension(int seat_vector_index);	//연장함수
	void ReadingRoomAppend(ReadingRoom &readingroom);	//열람실 추가
	bool ReadingRoomUseSet(int room_vector_index);		//열람실 활성,비활성 설정 (활성->비활성, 비활성->활성)
	ReadingRoom& GetRoomVetorElement(int room_vector_index);
};

/*관리자 클래스*/
class Manager
{
public:
	void Show(ReadingRoomContral &readingroomcontral);
};
#endif