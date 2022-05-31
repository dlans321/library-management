#include"Project.h"

bool AllContral::program = true;

void ScreenClear(int second)
{
	Sleep(second * 1000);
	system("cls");
}
bool CinCheck(istream &cin)
{
	if (!cin)
	{
		cin.clear();	//오류 플래그를 다시 원상태로 돌린다.
		cin.ignore(MAXSIZE::BUFFER, '\n'); //버퍼를 비운다
		//버퍼가 비워지고 오류플래그가 초기화되니 다음입력에서 cin은 정상으로 작동한다.
		cout << "입력이 올바르지 않습니다." << endl << endl;
		ScreenClear();
		return true;
	}
	cin.ignore(MAXSIZE::BUFFER, '\n');
	return false;
}

/*전체 제어 클래스*/
void AllContral::SetProgram(bool program)
{
	AllContral::program = program;
}

void AllContral::show()
{
	ReadingRoomContral readingroomcontral;

	while (true)
	{
		cout << "좌석 예약 프로그램입니다." << endl;
		cout << "(1)로그인 (2)회원가입 (3)회원탈퇴" << endl;
		cout << ">>";
		int menu = 0;

		while (!_kbhit())	//입력을 안하면 자동 반환 함수 호출
		{
			readingroomcontral.AutoReturn();
		} 

		cin >> menu;
		if (CinCheck(cin))
			continue;

		switch (menu)
		{
		case 1:
		{
			Login login;
			ScreenClear();
			login.show(readingroomcontral);
			break;
		}
		case 2:
		{
			MemberJoining memberjoining;
			ScreenClear();
			memberjoining.show();
			break;
		}
		case 3:
		{
			MemberIeave memberleave;
			ScreenClear();
			memberleave.show();
			break;
		}
		default:
			cout << "입력이 올바르지 않습니다." << endl;
			ScreenClear();
		}
		if (program == false)
		{
			cout << "프로그램 종료" << endl;
			return;
		}
	}
}

/*회원가입 클래스*/
void MemberJoining::show()
{
	string id, password, name, phone_number; 
	int sex, age;

	cout << "회원가입을 시작합니다." << endl;
	cout << "이름 입력>>";
	cin >> name;
	if (CinCheck(cin))
		return;

	cout << "성별 입력(0 : 여, 1 : 남)>>";
	cin >> sex;
	if (CinCheck(cin))
		return;
	
	cout << "나이 입력>>";
	cin >> age;
	if (CinCheck(cin))
		return;

	cout << "전화번호 입력>>";
	cin >> phone_number;
	if (CinCheck(cin))
		return;

	cout << "ID 입력>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	if (name.size() > MAXSIZE::NAME || phone_number.size() > MAXSIZE::PHONE_NUMBER ||
		age > MAXSIZE::AGE || age < 0 || sex < 0 || sex > 1 || id.size() > MAXSIZE::ID)
 	{
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}

	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	while (true)
	{
		Member member;
		if (!(fin_member >> member))
			break;
		if (member.GetId() == id)
		{
			cout << "입력이 올바르지 않습니다." << endl;
			ScreenClear();
			fin_member.close();
			return;
		}
	}
	fin_member.close();

	cout << "Password 입력>>";
	cin >> password;
	if (CinCheck(cin))
		return;

	if (password.size() > MAXSIZE::PASSWORD)
	{
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}

	Member member(id, password, name, sex, age, phone_number);
	ofstream fout_member("member.txt", ios::app);
	if (!fout_member)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	fout_member << member;
	fout_member.close();
	cout << "회원가입 되었습니다." << endl;
	ScreenClear();
}

/*회원탈퇴 클래스*/
void MemberIeave::show()
{
	string id, password;

	cout << "회원탈퇴를 시작합니다." << endl;
	cout << "아이디 입력>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	cout << "패스워드 입력>>";
	cin >> password;
	if (CinCheck(cin))
		return;
	
	if (id.size() > MAXSIZE::ID || password.size() > MAXSIZE::PASSWORD)
	{
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}

	vector<Member> v;
	vector<Member>::iterator it;
	bool delete_cheak = false;

	/*벡터로 데이터 추출*/
	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	while (true)
	{
		Member member;
		if (!(fin_member >> member))
			break;
		v.push_back(member);
	}
	fin_member.close();

	//벡터에서 탈퇴할 정보가 있으면 삭제
	for (it = v.begin(); it != v.end();)
	{
		if (it->GetId() == id && it->GetPassword() == password)
		{
			it = v.erase(it);
			delete_cheak = true;
			break;
		}
		else
		{
			it++;
		}
	}

	if (delete_cheak == false)
	{
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}

	//벡터의 내용을 파일로 씀
	ofstream fout_member("member.txt");
	if (!fout_member)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	for (it = v.begin(); it != v.end(); it++)
	{
		fout_member << *it;
	}
	fout_member.close();
	cout << "회원 탈퇴되었습니다." << endl;
	ScreenClear();
}

/*로그인 클래스*/
void Login::show(ReadingRoomContral& readingroomcontral)
{
	string id, password;

	cout << "로그인" << endl;
	cout << "아이디 입력>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	cout << "패스워드 입력>>";
	cin >> password;
	if (CinCheck(cin))
		return;

	if (id.size() > MAXSIZE::ID || password.size() > MAXSIZE::PASSWORD)
	{
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}
	
	switch (LoginCheak(id,password))
	{
	case 1:
		ScreenClear();
		Manager manger;
		manger.Show(readingroomcontral);
		break;
	case 2:
		ScreenClear();
		readingroomcontral.Member_Show(user);
		break;
	case 0:
		cout << "입력이 올바르지 않습니다." << endl;
		ScreenClear();
		return;
	}
}
int Login::LoginCheak(string &id, string &password)
{
	//관리자 ID면
	if (id == "0000" && password == "0000")
		return 1;

	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	while (true)
	{
		Member member;
		if (!(fin_member >> member))
			break;
		//유저 아이디가 파일에 있으면
		if (id == member.GetId() && password == member.GetPassword())
		{
			user = member;
			fin_member.close();
			return 2;
		}
	}
	//없으면
	fin_member.close();
	return 0;
}
Member& Login::GetUser()
{
	return user;
}

/*도서관 시간 제한*/
LimitTime::LimitTime(int hour, int min, int sec)
{
	this->hour = hour;
	this->min = min;
	this->sec = sec;
}
/*ID 클래스*/
ID::ID(string id, string password) : id(id), password(password)
{

}

/*회원 클래스*/
Member::Member(string id, string password, string name, int sex, int age, string phone_number) :
ID(id, password), name(name), sex(sex), age(age), phone_number(phone_number)
{

}
string Member::GetId()
{
	return id;
}
string Member::GetPassword()
{
	return password;
}
string Member::GetName()
{
	return name;
}
int Member::GetSex()
{
	return sex;
}
int Member::GetAge()
{
	return age;
}
string Member::GetPhoneNumber()
{
	return phone_number;
}
void Member::GetData(string &id, string &password, string &name, int& sex, int& age, string& phone_number)
{
	id = this->id;
	password = this->password;
	name = this->name;
	sex = this->sex;
	age = this->age;
	phone_number = this->phone_number;
}
void Member::SetId(string id)
{
	this->id = id;
}
void Member::SetPassword(string password)
{
	this->password = password;
}
void Member::SetData(string id, string password, string name, int sex, int age, string phone_number)
{
	this->id = id;
	this->password = password;
	this->name = name;
	this->sex = sex;
	this->age = age;
	this->phone_number = phone_number;
}
bool operator>>(ifstream &fin, Member &member)
{
	string line;
	string sub[6];
	int space_point = 0, start_point = 0;
	getline(fin, line);
	if (line == "")
	{
		return false;
	}
	for (int i = 0; i < 5; i++)
	{
		space_point = line.find(' ', start_point);
		sub[i] = line.substr(start_point, space_point - start_point);
		start_point = space_point + 1;
	}
	sub[5] = line.substr(start_point);
	member.SetData(sub[0], sub[1], sub[2], stoi(sub[3]), stoi(sub[4]), sub[5]);
	return true;
}
void operator<<(ofstream &fout, Member &member)
{
	fout << member.id << ' ' << member.password << ' ' << member.name << ' '
		<< member.sex << ' ' << member.age << ' ' << member.phone_number << endl;
}

/*열람실 클래스*/
ReadingRoom::ReadingRoom(string name, int seat_capacity, int use) : name(name), seat_capacity(seat_capacity), use(use)
{

}
void ReadingRoom::SetName(string name)
{
	this->name = name;
}
void ReadingRoom::SetSeatCapacity(int seat_capacity)
{
	this->seat_capacity = seat_capacity;
}
void ReadingRoom::SetUse(int use)
{
	this->use = use;
}
string ReadingRoom::GetName()
{
	return name;
}
int ReadingRoom::GetSeatCapacity()
{
	return seat_capacity;
}
int ReadingRoom::GetUse()
{
	return use;
}
bool operator>>(ifstream &fin, ReadingRoom &reading_room)
{
	string line;
	string sub[3];
	int space_point = 0, start_point = 0;
	getline(fin, line);
	if (line == "")
	{
		return false;
	}
	for (int i = 0; i < 2; i++)
	{
		space_point = line.find(' ', start_point);
		sub[i] = line.substr(start_point, space_point - start_point);
		start_point = space_point + 1;
	}
	sub[2] = line.substr(start_point);
	reading_room.SetName(sub[0]);
	reading_room.SetSeatCapacity(stoi(sub[1]));
	reading_room.SetUse(stoi(sub[2]));
	return true;
}
void operator<<(ofstream &fout, ReadingRoom &reading_room)
{
	fout << reading_room.GetName() << ' ' << reading_room.GetSeatCapacity() << ' '
		<< reading_room.GetUse() << endl;
}

/*좌석 정보 클래스*/
SeatInformation::SeatInformation(Member& member, string reding_room_name, int seatnumber, int extension_num, tm start_time, tm end_time, tm extenstion_time) : 
member(member), reding_room_name(reding_room_name), seatnumber(seatnumber), extension_num(extension_num), start_time(start_time), end_time(end_time), extension_time(extenstion_time)
{

}
void SeatInformation::SetExtensionNum(int extension_num)
{
	this->extension_num = extension_num;
}
void SeatInformation::SetStartTime(tm& start_time)
{
	this->start_time = start_time;
}
void SeatInformation::SetEndTime(tm& end_time)
{
	this->end_time = end_time;
}
void SeatInformation::SetExtensionTime(tm& extension_time)
{
	this->extension_time = extension_time;
}
Member& SeatInformation::GetMember()
{
	return member;
}
string SeatInformation::GetRedingRoomName()
{
	return reding_room_name;
}
int SeatInformation::GetSeatNumber()
{
	return seatnumber;
}
int SeatInformation::GetExtensionNum()
{
	return extension_num;
}
tm& SeatInformation::GetStartTime()
{
	return start_time;
}
tm& SeatInformation::GetEndTime()
{
	return end_time;
}
tm& SeatInformation::GetExtensionTime()
{
	return extension_time;
}

/*열람실 제어 클래스*/
ReadingRoomContral::ReadingRoomContral() : append_time(0, 5, 0), append_extenstion_time(0, 3, 0), close_time(23, 0, 0)
{
	ifstream fin_readingroom("reading_room.txt");
	if (!fin_readingroom)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	while (true)
	{
		ReadingRoom readingroom;
		if (!(fin_readingroom >> readingroom))
			break;
		room_vector.push_back(readingroom);
	}
	fin_readingroom.close();
}
void ReadingRoomContral::FileSet()
{
	ofstream fout_readingroom("reading_room.txt");
	if (!fout_readingroom)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	vector<ReadingRoom>::iterator it;
	for (it = room_vector.begin(); it != room_vector.end(); it++)
	{
		fout_readingroom << *it;
	}
	fout_readingroom.close();
}
void ReadingRoomContral::Member_Show(Member &user)
{	
	//열람실이 없다면
	if (room_vector.size() == 0)
	{
		cout << "예약 가능한 열람실이 없습니다." << endl;
		ScreenClear();
		return;
	}

	//예약하고 있다면 좌석 벡터 seat_vector_index에 사용자 정보가 있음
	int seat_vector_index = -1;
	for (int i = 0; i < seat_vector.size(); i++)
	{
		if (seat_vector[i].GetMember().GetId() == user.GetId())
		{
			seat_vector_index = i;
			break;
		}
	}

	if (seat_vector_index != -1) //연장 or 반납
	{
		//정보 출력
		cout << seat_vector[seat_vector_index].GetRedingRoomName() << " " << seat_vector[seat_vector_index].GetSeatNumber() << "번" << endl << endl;
		cout << "성명 : " << seat_vector[seat_vector_index].GetMember().GetName() << endl << endl;
		cout << "시작시간  :  " << asctime(&seat_vector[seat_vector_index].GetStartTime());
		cout << "종료시간  :  " << asctime(&seat_vector[seat_vector_index].GetEndTime());
		cout << "연장가능시간 : " << asctime(&seat_vector[seat_vector_index].GetExtensionTime());
		cout << "연장가능횟수 : " << seat_vector[seat_vector_index].GetExtensionNum() << endl;
		cout << endl;

		//연장횟수가 0이면
		//연장횟수는 0이 아니지만 연장 가능 시간을 넘기지 않았으면 반납
		if (seat_vector[seat_vector_index].GetExtensionNum() == 0 ||
			time(NULL) < mktime(&seat_vector[seat_vector_index].GetExtensionTime()))
		{
			cout << "반납하시겠습니까?" << endl;
			cout << "Yes : 1, NO : 0" << endl;
			cout << ">>";

			int menu = 0;
			cin >> menu;
			if (CinCheck(cin))
				return;

			if (menu < 0 || menu > 1)
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				return;
			}
			if (menu == 0)
			{
				ScreenClear();
				return;
			}
			vector<SeatInformation>::iterator it;
			it = seat_vector.begin();
			it += seat_vector_index;
			seat_vector.erase(it);
			cout << "반납이 완료되었습니다." << endl;
			ScreenClear();
		}

		else	//연장
		{
			cout << "연장 혹은 반납 하시겠습니까?" << endl;
			cout << "연장 : 1, 반납 : 2, NO : 0" << endl;
			cout << ">>";

			int menu = 0;
			cin >> menu;
			if (CinCheck(cin))
				return;
			if (menu < 0 || menu > 2)
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				return;
			}
			if (menu == 0)
			{
				ScreenClear();
				return;
			}
			else if (menu == 1)
			{
				Extension(seat_vector_index);
				ScreenClear();

				//다시 한번 정보 출력
				cout << seat_vector[seat_vector_index].GetRedingRoomName() << " " << seat_vector[seat_vector_index].GetSeatNumber() << "번" << endl << endl;
				cout << "성명 : " << seat_vector[seat_vector_index].GetMember().GetName() << endl << endl;
				cout << "시작시간  :  " << asctime(&seat_vector[seat_vector_index].GetStartTime());
				cout << "종료시간  :  " << asctime(&seat_vector[seat_vector_index].GetEndTime());
				cout << "연장가능시간 : " << asctime(&seat_vector[seat_vector_index].GetExtensionTime());
				cout << "연장가능횟수 : " << seat_vector[seat_vector_index].GetExtensionNum() << endl;
				cout << endl;
				cout << "연장이 완료되었습니다." << endl;
				ScreenClear(5);
			}
			else
			{
				vector<SeatInformation>::iterator it;
				it = seat_vector.begin();
				it += seat_vector_index;
				seat_vector.erase(it);
				cout << "반납이 완료되었습니다." << endl;
				ScreenClear();
			}
		}
	}
	else //예약
	{
		int room_vector_index = 0;
		ChoiceReadingRoom();	//열람실 출력
		cout << "열람실 선택>>";
		cin >> room_vector_index;
		if (CinCheck(cin))
			return;

		room_vector_index--; //열람실 입력은 1부터 시작하기에 위치는 1를 빼줘야함

		//유효하지 않는 열람실 범위이면
		if (room_vector_index < 0 || room_vector_index >= (int)room_vector.size())
		{
			cout << "입력이 올바르지 않습니다." << endl;
			ScreenClear();
			return;
		}
		
		//열람실의 좌석이 0개라면
		if (room_vector[room_vector_index].GetSeatCapacity() <= 0)
		{
			cout << "해당 열람실은 좌석이 없습니다." << endl;
			ScreenClear();
			return;
		}

		//해당 열람실이 사용불가이면
		if (room_vector[room_vector_index].GetUse() == 0)
		{
			cout << "해당 열람실은 예약이 안됩니다." << endl;
			ScreenClear();
			return;
		}
		ScreenClear();

		int seatnumber = 0;
		SeatScreen(room_vector[room_vector_index]);	//좌석 정보 출력
		cout << "좌석 선택>>";
		cin >> seatnumber;
		if (CinCheck(cin))
			return;

		//유효하지 않는 좌석 범위이면
		if (seatnumber < 1 || seatnumber > room_vector[room_vector_index].GetSeatCapacity())
		{
			cout << "입력이 올바르지 않습니다." << endl;
			ScreenClear();
			return;
		}

		//해당 좌석이 이미 사용중이면
		for (int i = 0; i < seat_vector.size(); i++)
		{
			if (room_vector[room_vector_index].GetName() == seat_vector[i].GetRedingRoomName())
			{
				if (seatnumber == seat_vector[i].GetSeatNumber())
				{
					cout << "입력이 올바르지 않습니다." << endl;
					ScreenClear();
					return;
				}
			}
		}

		//해당 좌석으로 예약, 좌석 정보 벡터 하나 추가됨
		Reservation(user, room_vector[room_vector_index].GetName(), seatnumber);
		ScreenClear();

		cout << seat_vector[seat_vector.size() - 1].GetRedingRoomName() << " " << seatnumber << "번" << endl << endl;
		cout << "성명 : " << seat_vector[seat_vector.size() - 1].GetMember().GetName() << endl << endl;
		cout << "시작시간  :  " << asctime(&seat_vector[seat_vector.size() - 1].GetStartTime());
		cout << "종료시간  :  " << asctime(&seat_vector[seat_vector.size() - 1].GetEndTime());
		cout << "연장가능시간 : " << asctime(&seat_vector[seat_vector.size() - 1].GetExtensionTime());
		cout << "연장가능횟수 : " << seat_vector[seat_vector.size() - 1].GetExtensionNum() << endl;
		cout << endl;
		cout << "예약이 완료되었습니다." << endl;
		ScreenClear(5);
	}
}
void ReadingRoomContral::ChoiceReadingRoom()
{
	int i = 0;
	cout << "열람실을 선택해주세요." << endl;
	for (i = 1; i <= (int)room_vector.size(); i++)
	{
		cout << i << " : " << room_vector[i - 1].GetName();
		if (room_vector[i - 1].GetUse() == 1)
			cout << "(사용가능)" << endl;
		else
			cout << "(사용불가)" << endl;
	}
	cout << endl;
}
void ReadingRoomContral::SeatScreen(ReadingRoom &reading_room)
{
	//해당 열람실을 쓰고 있는 좌석번호를 temp에 임시저장 
	vector<int> temp;
	for (int i = 0; i < seat_vector.size(); i++)
	{
		if (reading_room.GetName() == seat_vector[i].GetRedingRoomName())
			temp.push_back(seat_vector[i].GetSeatNumber());
	}

	//해당 열람실의 전체 좌석 출력, temp에 해당하는 좌석번호는 off로 출력
	cout << reading_room.GetName() << endl;
	cout << "좌석을 선택해주세요." << endl;

	bool on = false;
	for (int i = 1; i <= reading_room.GetSeatCapacity(); i++)
	{
		cout << i << "번 자리 : ";
		for (int j = 0; j < temp.size(); j++)
		{
			if (i == temp[j])
				on = true;
		}
		if (on)
			cout << "on" << endl;
		else
			cout << "off" << endl;
		on = false;
	}
	cout << endl;
}
void ReadingRoomContral::Reservation(Member& user, string reding_room_name, int seatnumber)
{
	//끝시간을 time_t ctime에 저장한다.
	time_t ctime = time(NULL);		
	tm tmtime = *localtime(&ctime);
	tmtime.tm_hour = close_time.hour;
	tmtime.tm_min = close_time.min;
	tmtime.tm_sec = close_time.sec;
	ctime = mktime(&tmtime);

	//time_t 시작시간, 연장가능시간, 종료시간을 구한다
	time_t stime, etime, extime;
	stime = etime = extime = time(NULL);

	etime += append_time.hour * 3600 + append_time.min * 60 + append_time.sec;
	extime += append_extenstion_time.hour * 3600 + append_extenstion_time.min * 60 + append_extenstion_time.sec;
	if (etime > ctime)
	{
		etime = ctime;
		extime = ctime;
	}

	//tm 구조체로 변환해 좌석정보를 좌석정보벡터에 추가한다.
	tm start_time = *localtime(&stime);
	tm end_time = *localtime(&etime);
	tm extension_time = *localtime(&extime);
	SeatInformation temp(user, reding_room_name, seatnumber, 2, start_time, end_time, extension_time);
	seat_vector.push_back(temp);
}
void ReadingRoomContral::AutoReturn()
{
	/*이 코드를 잘봐야됨. 오류 해결*/
	vector<SeatInformation>::iterator it;

	for (it = seat_vector.begin(); it != seat_vector.end();)
	{
		if (time(NULL) > mktime(&it->GetEndTime()))
		{
			it = seat_vector.erase(it);
		}
		else
		{
			it++;
		}
	}
}
void ReadingRoomContral::Extension(int seat_vector_index)
{
	//끝시간을 time_t ctime에 저장한다.
	time_t ctime = time(NULL);
	tm tmtime = *localtime(&ctime);
	tmtime.tm_hour = close_time.hour;
	tmtime.tm_min = close_time.min;
	tmtime.tm_sec = close_time.sec;
	ctime = mktime(&tmtime);

	//time_t 시작시간, 연장가능시간, 종료시간을 구한다
	time_t stime, etime, extime;
	etime = mktime(&seat_vector[seat_vector_index].GetEndTime());
	extime = mktime(&seat_vector[seat_vector_index].GetExtensionTime());

	//time_t 시작시간은 현재시간이 된다.
	stime = time(NULL);

	//time_t 종료시간과 연장가능시간을 계산한다.
	extime = etime + append_extenstion_time.hour * 3600 +
		append_extenstion_time.min * 60 + append_extenstion_time.sec;
	etime += append_time.hour * 3600 + append_time.min * 60 + append_time.sec;
	if (etime > ctime)
	{
		etime = ctime;
		extime = ctime;
	}
	
	//time_t 시간들을 tm 구조체로 변환하여 좌석 벡터에 넣는다.
	seat_vector[seat_vector_index].SetStartTime(*localtime(&stime));
	seat_vector[seat_vector_index].SetEndTime(*localtime(&etime));
	seat_vector[seat_vector_index].SetExtensionTime(*localtime(&extime));

	//연장 횟수를 -1한다.
	seat_vector[seat_vector_index].SetExtensionNum(seat_vector[seat_vector_index].GetExtensionNum() - 1);
}
void ReadingRoomContral::ReadingRoomAppend(ReadingRoom &readingroom)
{
	room_vector.push_back(readingroom);

	ofstream fout_readingroom("reading_room.txt", ios::app);
	if (!fout_readingroom)
	{
		cout << "파일 연결 실패" << endl;
		exit(1);
	}
	fout_readingroom << room_vector[room_vector.size() - 1];
	fout_readingroom.close();
}
bool ReadingRoomContral::ReadingRoomUseSet(int room_vector_index)
{
	if (room_vector_index < 0 || room_vector_index >= room_vector.size())
		return false;

	//활성 상태면 비활성화 상태로 바꾸고 해당 열람실을 쓰는 좌석들을 다 반납해줌
	if (room_vector[room_vector_index].GetUse() == 1)
	{
		room_vector[room_vector_index].SetUse(0);
		vector<SeatInformation>::iterator it;
		for (it = seat_vector.begin(); it != seat_vector.end();)
		{
			if (room_vector[room_vector_index].GetName() == it->GetRedingRoomName())
			{
				it = seat_vector.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	else
	{
		room_vector[room_vector_index].SetUse(1);
	}
	//바뀐 정보들을 파일에 써줌
	FileSet();
	return true;
}
ReadingRoom& ReadingRoomContral::GetRoomVetorElement(int room_vector_index)
{
	return room_vector[room_vector_index];
}

/*관리자 클래스*/
void Manager::Show(ReadingRoomContral &readingroomcontral)
{
	while (true)
	{
		int menu = 0;
		cout << "관리자 모드입니다." << endl;
		cout << "(1)특정 회원 정보 출력" << endl;
		cout << "(2)열람실 추가" << endl;
		cout << "(3)열람실 활성/비활성화" << endl;
		cout << "(4)로그아웃" << endl;
		cout << "(5)프로그램 종료" << endl;
		cout << ">>";
		cin >> menu;

		if (CinCheck(cin))
			continue;

		if (menu < 1 || menu > 5)
		{
			cout << "입력이 올바르지 않습니다." << endl;
			ScreenClear();
			continue;
		}
		ScreenClear();

		switch (menu)
		{
		case 1:
		{
			string id;
			cout << "특정 회원 정보를 출력합니다." << endl;
			cout << "아이디 입력>>";
			cin >> id;

			if (CinCheck(cin))
				break;

			if (id.size() > MAXSIZE::ID)
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				break;
			}
			ScreenClear();

			// 특정 회원 정보 출력
			ifstream fin_member("member.txt");
			if (!fin_member)
			{
				cout << "파일 연결 실패" << endl;
				exit(1);
			}

			Member member;
			bool search = false;
			while (true)
			{
				if (!(fin_member >> member))
					break;

				if (id == member.GetId())
				{
					search = true;
					break;
				}
			}
			fin_member.close();

			if (search)
			{
				cout << "해당 회원 정보" << endl;
				cout << "ID : " << member.GetId() << endl;
				cout << "이름 : " << member.GetName() << endl;
				cout << "성별 : ";
				if (member.GetSex() == 1)
					cout << "남" << endl;
				else
					cout << "여" << endl;
				cout << "나이 : " << member.GetAge() << endl;
				cout << "전화번호 : " << member.GetPhoneNumber() << endl;
				cout << endl;
				cout << "뒤로 갈려면 아무 키나 누르세요." << endl;
				cout << ">>";
				_getch();
				ScreenClear();
			}
			else
			{
				cout << id << " " << "해당 아이디가 없습니다." << endl;
				ScreenClear();
			}
			break;
		}
		case 2:
		{
			int menu = 0;
			string room_name;
			int room_capacity = 0;

			cout << "열람실 추가 합니다." << endl;
			cout << "추가할 열람실 이름>>";
			cin >> room_name;
			if(CinCheck(cin))
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				break;
			}
			cout << "추가할 열람실 좌석 수>>";
			cin >> room_capacity;
			if (CinCheck(cin))
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				break;
			}
			if (room_name.size() > MAXSIZE::ROOM_NAME || room_capacity < 0 || room_capacity > MAXSIZE::ROOM_CAPACITY)
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				break;
			}
			ReadingRoom readingroom(room_name, room_capacity, 1);
			readingroomcontral.ReadingRoomAppend(readingroom);
			cout << "열람실이 추가되었습니다." << endl;
			ScreenClear();
			break;
		}
		//열람실 활성/비활성화
		case 3:
		{
			int room_vector_index = 0;
			cout << "열람실 예약 사용가능 상태를 변경합니다." << endl;
			cout << "사용가능 -> 사용불가,  사용불가 -> 사용가능" << endl << endl;

			readingroomcontral.ChoiceReadingRoom();
			cout << ">>";
			cin >> room_vector_index;

			if (CinCheck(cin))
			{
				break;
			}

			room_vector_index--; //열람실 입력은 1부터 시작하기에 위치는 1를 빼줘야함
			if (readingroomcontral.ReadingRoomUseSet(room_vector_index) == false)
			{
				cout << "입력이 올바르지 않거나 열람실이 존재하지 않습니다." << endl;
				ScreenClear();
				break;
			}
			ScreenClear();

			if (readingroomcontral.GetRoomVetorElement(room_vector_index).GetUse() == 1)
			{
				cout << readingroomcontral.GetRoomVetorElement(room_vector_index).GetName() << " 열람실을 예약 사용가능 상태로 변환했습니다." << endl;
			}
			else
			{
				cout << readingroomcontral.GetRoomVetorElement(room_vector_index).GetName() << " 열람실을 예약 사용불가 상태로 변환했습니다." << endl;
			}
			ScreenClear();
			break;
		}
		//로그아웃
		case 4:
		{
			return;
		}
		//프로그램 종료
		case 5:
		{
			int menu = 0;
			cout << "프로그램을 종료하시겠습니까?" << endl;
			cout << "종료되면 모든 좌석이 반납됩니다." << endl;
			cout << "Yes : 1, NO : 0" << endl;
			cin >> menu;

			if (CinCheck(cin))
				break;

			if (menu < 0 || menu > 1)
			{
				cout << "입력이 올바르지 않습니다." << endl;
				ScreenClear();
				break;
			}
			if (menu == 1)
			{
				AllContral::SetProgram(false);
				return;
			}
			else
			{
				ScreenClear();
				break;
			}
		}
		}
	}
}