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
		cin.clear();	//���� �÷��׸� �ٽ� �����·� ������.
		cin.ignore(MAXSIZE::BUFFER, '\n'); //���۸� ����
		//���۰� ������� �����÷��װ� �ʱ�ȭ�Ǵ� �����Է¿��� cin�� �������� �۵��Ѵ�.
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl << endl;
		ScreenClear();
		return true;
	}
	cin.ignore(MAXSIZE::BUFFER, '\n');
	return false;
}

/*��ü ���� Ŭ����*/
void AllContral::SetProgram(bool program)
{
	AllContral::program = program;
}

void AllContral::show()
{
	ReadingRoomContral readingroomcontral;

	while (true)
	{
		cout << "�¼� ���� ���α׷��Դϴ�." << endl;
		cout << "(1)�α��� (2)ȸ������ (3)ȸ��Ż��" << endl;
		cout << ">>";
		int menu = 0;

		while (!_kbhit())	//�Է��� ���ϸ� �ڵ� ��ȯ �Լ� ȣ��
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
			cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
			ScreenClear();
		}
		if (program == false)
		{
			cout << "���α׷� ����" << endl;
			return;
		}
	}
}

/*ȸ������ Ŭ����*/
void MemberJoining::show()
{
	string id, password, name, phone_number; 
	int sex, age;

	cout << "ȸ�������� �����մϴ�." << endl;
	cout << "�̸� �Է�>>";
	cin >> name;
	if (CinCheck(cin))
		return;

	cout << "���� �Է�(0 : ��, 1 : ��)>>";
	cin >> sex;
	if (CinCheck(cin))
		return;
	
	cout << "���� �Է�>>";
	cin >> age;
	if (CinCheck(cin))
		return;

	cout << "��ȭ��ȣ �Է�>>";
	cin >> phone_number;
	if (CinCheck(cin))
		return;

	cout << "ID �Է�>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	if (name.size() > MAXSIZE::NAME || phone_number.size() > MAXSIZE::PHONE_NUMBER ||
		age > MAXSIZE::AGE || age < 0 || sex < 0 || sex > 1 || id.size() > MAXSIZE::ID)
 	{
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
		ScreenClear();
		return;
	}

	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	while (true)
	{
		Member member;
		if (!(fin_member >> member))
			break;
		if (member.GetId() == id)
		{
			cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
			ScreenClear();
			fin_member.close();
			return;
		}
	}
	fin_member.close();

	cout << "Password �Է�>>";
	cin >> password;
	if (CinCheck(cin))
		return;

	if (password.size() > MAXSIZE::PASSWORD)
	{
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
		ScreenClear();
		return;
	}

	Member member(id, password, name, sex, age, phone_number);
	ofstream fout_member("member.txt", ios::app);
	if (!fout_member)
	{
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	fout_member << member;
	fout_member.close();
	cout << "ȸ������ �Ǿ����ϴ�." << endl;
	ScreenClear();
}

/*ȸ��Ż�� Ŭ����*/
void MemberIeave::show()
{
	string id, password;

	cout << "ȸ��Ż�� �����մϴ�." << endl;
	cout << "���̵� �Է�>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	cout << "�н����� �Է�>>";
	cin >> password;
	if (CinCheck(cin))
		return;
	
	if (id.size() > MAXSIZE::ID || password.size() > MAXSIZE::PASSWORD)
	{
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
		ScreenClear();
		return;
	}

	vector<Member> v;
	vector<Member>::iterator it;
	bool delete_cheak = false;

	/*���ͷ� ������ ����*/
	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "���� ���� ����" << endl;
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

	//���Ϳ��� Ż���� ������ ������ ����
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
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
		ScreenClear();
		return;
	}

	//������ ������ ���Ϸ� ��
	ofstream fout_member("member.txt");
	if (!fout_member)
	{
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	for (it = v.begin(); it != v.end(); it++)
	{
		fout_member << *it;
	}
	fout_member.close();
	cout << "ȸ�� Ż��Ǿ����ϴ�." << endl;
	ScreenClear();
}

/*�α��� Ŭ����*/
void Login::show(ReadingRoomContral& readingroomcontral)
{
	string id, password;

	cout << "�α���" << endl;
	cout << "���̵� �Է�>>";
	cin >> id;
	if (CinCheck(cin))
		return;

	cout << "�н����� �Է�>>";
	cin >> password;
	if (CinCheck(cin))
		return;

	if (id.size() > MAXSIZE::ID || password.size() > MAXSIZE::PASSWORD)
	{
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
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
		cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
		ScreenClear();
		return;
	}
}
int Login::LoginCheak(string &id, string &password)
{
	//������ ID��
	if (id == "0000" && password == "0000")
		return 1;

	ifstream fin_member("member.txt");
	if (!fin_member)
	{
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	while (true)
	{
		Member member;
		if (!(fin_member >> member))
			break;
		//���� ���̵� ���Ͽ� ������
		if (id == member.GetId() && password == member.GetPassword())
		{
			user = member;
			fin_member.close();
			return 2;
		}
	}
	//������
	fin_member.close();
	return 0;
}
Member& Login::GetUser()
{
	return user;
}

/*������ �ð� ����*/
LimitTime::LimitTime(int hour, int min, int sec)
{
	this->hour = hour;
	this->min = min;
	this->sec = sec;
}
/*ID Ŭ����*/
ID::ID(string id, string password) : id(id), password(password)
{

}

/*ȸ�� Ŭ����*/
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

/*������ Ŭ����*/
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

/*�¼� ���� Ŭ����*/
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

/*������ ���� Ŭ����*/
ReadingRoomContral::ReadingRoomContral() : append_time(0, 5, 0), append_extenstion_time(0, 3, 0), close_time(23, 0, 0)
{
	ifstream fin_readingroom("reading_room.txt");
	if (!fin_readingroom)
	{
		cout << "���� ���� ����" << endl;
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
		cout << "���� ���� ����" << endl;
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
	//�������� ���ٸ�
	if (room_vector.size() == 0)
	{
		cout << "���� ������ �������� �����ϴ�." << endl;
		ScreenClear();
		return;
	}

	//�����ϰ� �ִٸ� �¼� ���� seat_vector_index�� ����� ������ ����
	int seat_vector_index = -1;
	for (int i = 0; i < seat_vector.size(); i++)
	{
		if (seat_vector[i].GetMember().GetId() == user.GetId())
		{
			seat_vector_index = i;
			break;
		}
	}

	if (seat_vector_index != -1) //���� or �ݳ�
	{
		//���� ���
		cout << seat_vector[seat_vector_index].GetRedingRoomName() << " " << seat_vector[seat_vector_index].GetSeatNumber() << "��" << endl << endl;
		cout << "���� : " << seat_vector[seat_vector_index].GetMember().GetName() << endl << endl;
		cout << "���۽ð�  :  " << asctime(&seat_vector[seat_vector_index].GetStartTime());
		cout << "����ð�  :  " << asctime(&seat_vector[seat_vector_index].GetEndTime());
		cout << "���尡�ɽð� : " << asctime(&seat_vector[seat_vector_index].GetExtensionTime());
		cout << "���尡��Ƚ�� : " << seat_vector[seat_vector_index].GetExtensionNum() << endl;
		cout << endl;

		//����Ƚ���� 0�̸�
		//����Ƚ���� 0�� �ƴ����� ���� ���� �ð��� �ѱ��� �ʾ����� �ݳ�
		if (seat_vector[seat_vector_index].GetExtensionNum() == 0 ||
			time(NULL) < mktime(&seat_vector[seat_vector_index].GetExtensionTime()))
		{
			cout << "�ݳ��Ͻðڽ��ϱ�?" << endl;
			cout << "Yes : 1, NO : 0" << endl;
			cout << ">>";

			int menu = 0;
			cin >> menu;
			if (CinCheck(cin))
				return;

			if (menu < 0 || menu > 1)
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
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
			cout << "�ݳ��� �Ϸ�Ǿ����ϴ�." << endl;
			ScreenClear();
		}

		else	//����
		{
			cout << "���� Ȥ�� �ݳ� �Ͻðڽ��ϱ�?" << endl;
			cout << "���� : 1, �ݳ� : 2, NO : 0" << endl;
			cout << ">>";

			int menu = 0;
			cin >> menu;
			if (CinCheck(cin))
				return;
			if (menu < 0 || menu > 2)
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
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

				//�ٽ� �ѹ� ���� ���
				cout << seat_vector[seat_vector_index].GetRedingRoomName() << " " << seat_vector[seat_vector_index].GetSeatNumber() << "��" << endl << endl;
				cout << "���� : " << seat_vector[seat_vector_index].GetMember().GetName() << endl << endl;
				cout << "���۽ð�  :  " << asctime(&seat_vector[seat_vector_index].GetStartTime());
				cout << "����ð�  :  " << asctime(&seat_vector[seat_vector_index].GetEndTime());
				cout << "���尡�ɽð� : " << asctime(&seat_vector[seat_vector_index].GetExtensionTime());
				cout << "���尡��Ƚ�� : " << seat_vector[seat_vector_index].GetExtensionNum() << endl;
				cout << endl;
				cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
				ScreenClear(5);
			}
			else
			{
				vector<SeatInformation>::iterator it;
				it = seat_vector.begin();
				it += seat_vector_index;
				seat_vector.erase(it);
				cout << "�ݳ��� �Ϸ�Ǿ����ϴ�." << endl;
				ScreenClear();
			}
		}
	}
	else //����
	{
		int room_vector_index = 0;
		ChoiceReadingRoom();	//������ ���
		cout << "������ ����>>";
		cin >> room_vector_index;
		if (CinCheck(cin))
			return;

		room_vector_index--; //������ �Է��� 1���� �����ϱ⿡ ��ġ�� 1�� �������

		//��ȿ���� �ʴ� ������ �����̸�
		if (room_vector_index < 0 || room_vector_index >= (int)room_vector.size())
		{
			cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
			ScreenClear();
			return;
		}
		
		//�������� �¼��� 0�����
		if (room_vector[room_vector_index].GetSeatCapacity() <= 0)
		{
			cout << "�ش� �������� �¼��� �����ϴ�." << endl;
			ScreenClear();
			return;
		}

		//�ش� �������� ���Ұ��̸�
		if (room_vector[room_vector_index].GetUse() == 0)
		{
			cout << "�ش� �������� ������ �ȵ˴ϴ�." << endl;
			ScreenClear();
			return;
		}
		ScreenClear();

		int seatnumber = 0;
		SeatScreen(room_vector[room_vector_index]);	//�¼� ���� ���
		cout << "�¼� ����>>";
		cin >> seatnumber;
		if (CinCheck(cin))
			return;

		//��ȿ���� �ʴ� �¼� �����̸�
		if (seatnumber < 1 || seatnumber > room_vector[room_vector_index].GetSeatCapacity())
		{
			cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
			ScreenClear();
			return;
		}

		//�ش� �¼��� �̹� ������̸�
		for (int i = 0; i < seat_vector.size(); i++)
		{
			if (room_vector[room_vector_index].GetName() == seat_vector[i].GetRedingRoomName())
			{
				if (seatnumber == seat_vector[i].GetSeatNumber())
				{
					cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
					ScreenClear();
					return;
				}
			}
		}

		//�ش� �¼����� ����, �¼� ���� ���� �ϳ� �߰���
		Reservation(user, room_vector[room_vector_index].GetName(), seatnumber);
		ScreenClear();

		cout << seat_vector[seat_vector.size() - 1].GetRedingRoomName() << " " << seatnumber << "��" << endl << endl;
		cout << "���� : " << seat_vector[seat_vector.size() - 1].GetMember().GetName() << endl << endl;
		cout << "���۽ð�  :  " << asctime(&seat_vector[seat_vector.size() - 1].GetStartTime());
		cout << "����ð�  :  " << asctime(&seat_vector[seat_vector.size() - 1].GetEndTime());
		cout << "���尡�ɽð� : " << asctime(&seat_vector[seat_vector.size() - 1].GetExtensionTime());
		cout << "���尡��Ƚ�� : " << seat_vector[seat_vector.size() - 1].GetExtensionNum() << endl;
		cout << endl;
		cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
		ScreenClear(5);
	}
}
void ReadingRoomContral::ChoiceReadingRoom()
{
	int i = 0;
	cout << "�������� �������ּ���." << endl;
	for (i = 1; i <= (int)room_vector.size(); i++)
	{
		cout << i << " : " << room_vector[i - 1].GetName();
		if (room_vector[i - 1].GetUse() == 1)
			cout << "(��밡��)" << endl;
		else
			cout << "(���Ұ�)" << endl;
	}
	cout << endl;
}
void ReadingRoomContral::SeatScreen(ReadingRoom &reading_room)
{
	//�ش� �������� ���� �ִ� �¼���ȣ�� temp�� �ӽ����� 
	vector<int> temp;
	for (int i = 0; i < seat_vector.size(); i++)
	{
		if (reading_room.GetName() == seat_vector[i].GetRedingRoomName())
			temp.push_back(seat_vector[i].GetSeatNumber());
	}

	//�ش� �������� ��ü �¼� ���, temp�� �ش��ϴ� �¼���ȣ�� off�� ���
	cout << reading_room.GetName() << endl;
	cout << "�¼��� �������ּ���." << endl;

	bool on = false;
	for (int i = 1; i <= reading_room.GetSeatCapacity(); i++)
	{
		cout << i << "�� �ڸ� : ";
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
	//���ð��� time_t ctime�� �����Ѵ�.
	time_t ctime = time(NULL);		
	tm tmtime = *localtime(&ctime);
	tmtime.tm_hour = close_time.hour;
	tmtime.tm_min = close_time.min;
	tmtime.tm_sec = close_time.sec;
	ctime = mktime(&tmtime);

	//time_t ���۽ð�, ���尡�ɽð�, ����ð��� ���Ѵ�
	time_t stime, etime, extime;
	stime = etime = extime = time(NULL);

	etime += append_time.hour * 3600 + append_time.min * 60 + append_time.sec;
	extime += append_extenstion_time.hour * 3600 + append_extenstion_time.min * 60 + append_extenstion_time.sec;
	if (etime > ctime)
	{
		etime = ctime;
		extime = ctime;
	}

	//tm ����ü�� ��ȯ�� �¼������� �¼��������Ϳ� �߰��Ѵ�.
	tm start_time = *localtime(&stime);
	tm end_time = *localtime(&etime);
	tm extension_time = *localtime(&extime);
	SeatInformation temp(user, reding_room_name, seatnumber, 2, start_time, end_time, extension_time);
	seat_vector.push_back(temp);
}
void ReadingRoomContral::AutoReturn()
{
	/*�� �ڵ带 �ߺ��ߵ�. ���� �ذ�*/
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
	//���ð��� time_t ctime�� �����Ѵ�.
	time_t ctime = time(NULL);
	tm tmtime = *localtime(&ctime);
	tmtime.tm_hour = close_time.hour;
	tmtime.tm_min = close_time.min;
	tmtime.tm_sec = close_time.sec;
	ctime = mktime(&tmtime);

	//time_t ���۽ð�, ���尡�ɽð�, ����ð��� ���Ѵ�
	time_t stime, etime, extime;
	etime = mktime(&seat_vector[seat_vector_index].GetEndTime());
	extime = mktime(&seat_vector[seat_vector_index].GetExtensionTime());

	//time_t ���۽ð��� ����ð��� �ȴ�.
	stime = time(NULL);

	//time_t ����ð��� ���尡�ɽð��� ����Ѵ�.
	extime = etime + append_extenstion_time.hour * 3600 +
		append_extenstion_time.min * 60 + append_extenstion_time.sec;
	etime += append_time.hour * 3600 + append_time.min * 60 + append_time.sec;
	if (etime > ctime)
	{
		etime = ctime;
		extime = ctime;
	}
	
	//time_t �ð����� tm ����ü�� ��ȯ�Ͽ� �¼� ���Ϳ� �ִ´�.
	seat_vector[seat_vector_index].SetStartTime(*localtime(&stime));
	seat_vector[seat_vector_index].SetEndTime(*localtime(&etime));
	seat_vector[seat_vector_index].SetExtensionTime(*localtime(&extime));

	//���� Ƚ���� -1�Ѵ�.
	seat_vector[seat_vector_index].SetExtensionNum(seat_vector[seat_vector_index].GetExtensionNum() - 1);
}
void ReadingRoomContral::ReadingRoomAppend(ReadingRoom &readingroom)
{
	room_vector.push_back(readingroom);

	ofstream fout_readingroom("reading_room.txt", ios::app);
	if (!fout_readingroom)
	{
		cout << "���� ���� ����" << endl;
		exit(1);
	}
	fout_readingroom << room_vector[room_vector.size() - 1];
	fout_readingroom.close();
}
bool ReadingRoomContral::ReadingRoomUseSet(int room_vector_index)
{
	if (room_vector_index < 0 || room_vector_index >= room_vector.size())
		return false;

	//Ȱ�� ���¸� ��Ȱ��ȭ ���·� �ٲٰ� �ش� �������� ���� �¼����� �� �ݳ�����
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
	//�ٲ� �������� ���Ͽ� ����
	FileSet();
	return true;
}
ReadingRoom& ReadingRoomContral::GetRoomVetorElement(int room_vector_index)
{
	return room_vector[room_vector_index];
}

/*������ Ŭ����*/
void Manager::Show(ReadingRoomContral &readingroomcontral)
{
	while (true)
	{
		int menu = 0;
		cout << "������ ����Դϴ�." << endl;
		cout << "(1)Ư�� ȸ�� ���� ���" << endl;
		cout << "(2)������ �߰�" << endl;
		cout << "(3)������ Ȱ��/��Ȱ��ȭ" << endl;
		cout << "(4)�α׾ƿ�" << endl;
		cout << "(5)���α׷� ����" << endl;
		cout << ">>";
		cin >> menu;

		if (CinCheck(cin))
			continue;

		if (menu < 1 || menu > 5)
		{
			cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
			ScreenClear();
			continue;
		}
		ScreenClear();

		switch (menu)
		{
		case 1:
		{
			string id;
			cout << "Ư�� ȸ�� ������ ����մϴ�." << endl;
			cout << "���̵� �Է�>>";
			cin >> id;

			if (CinCheck(cin))
				break;

			if (id.size() > MAXSIZE::ID)
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
				ScreenClear();
				break;
			}
			ScreenClear();

			// Ư�� ȸ�� ���� ���
			ifstream fin_member("member.txt");
			if (!fin_member)
			{
				cout << "���� ���� ����" << endl;
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
				cout << "�ش� ȸ�� ����" << endl;
				cout << "ID : " << member.GetId() << endl;
				cout << "�̸� : " << member.GetName() << endl;
				cout << "���� : ";
				if (member.GetSex() == 1)
					cout << "��" << endl;
				else
					cout << "��" << endl;
				cout << "���� : " << member.GetAge() << endl;
				cout << "��ȭ��ȣ : " << member.GetPhoneNumber() << endl;
				cout << endl;
				cout << "�ڷ� ������ �ƹ� Ű�� ��������." << endl;
				cout << ">>";
				_getch();
				ScreenClear();
			}
			else
			{
				cout << id << " " << "�ش� ���̵� �����ϴ�." << endl;
				ScreenClear();
			}
			break;
		}
		case 2:
		{
			int menu = 0;
			string room_name;
			int room_capacity = 0;

			cout << "������ �߰� �մϴ�." << endl;
			cout << "�߰��� ������ �̸�>>";
			cin >> room_name;
			if(CinCheck(cin))
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
				ScreenClear();
				break;
			}
			cout << "�߰��� ������ �¼� ��>>";
			cin >> room_capacity;
			if (CinCheck(cin))
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
				ScreenClear();
				break;
			}
			if (room_name.size() > MAXSIZE::ROOM_NAME || room_capacity < 0 || room_capacity > MAXSIZE::ROOM_CAPACITY)
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
				ScreenClear();
				break;
			}
			ReadingRoom readingroom(room_name, room_capacity, 1);
			readingroomcontral.ReadingRoomAppend(readingroom);
			cout << "�������� �߰��Ǿ����ϴ�." << endl;
			ScreenClear();
			break;
		}
		//������ Ȱ��/��Ȱ��ȭ
		case 3:
		{
			int room_vector_index = 0;
			cout << "������ ���� ��밡�� ���¸� �����մϴ�." << endl;
			cout << "��밡�� -> ���Ұ�,  ���Ұ� -> ��밡��" << endl << endl;

			readingroomcontral.ChoiceReadingRoom();
			cout << ">>";
			cin >> room_vector_index;

			if (CinCheck(cin))
			{
				break;
			}

			room_vector_index--; //������ �Է��� 1���� �����ϱ⿡ ��ġ�� 1�� �������
			if (readingroomcontral.ReadingRoomUseSet(room_vector_index) == false)
			{
				cout << "�Է��� �ùٸ��� �ʰų� �������� �������� �ʽ��ϴ�." << endl;
				ScreenClear();
				break;
			}
			ScreenClear();

			if (readingroomcontral.GetRoomVetorElement(room_vector_index).GetUse() == 1)
			{
				cout << readingroomcontral.GetRoomVetorElement(room_vector_index).GetName() << " �������� ���� ��밡�� ���·� ��ȯ�߽��ϴ�." << endl;
			}
			else
			{
				cout << readingroomcontral.GetRoomVetorElement(room_vector_index).GetName() << " �������� ���� ���Ұ� ���·� ��ȯ�߽��ϴ�." << endl;
			}
			ScreenClear();
			break;
		}
		//�α׾ƿ�
		case 4:
		{
			return;
		}
		//���α׷� ����
		case 5:
		{
			int menu = 0;
			cout << "���α׷��� �����Ͻðڽ��ϱ�?" << endl;
			cout << "����Ǹ� ��� �¼��� �ݳ��˴ϴ�." << endl;
			cout << "Yes : 1, NO : 0" << endl;
			cin >> menu;

			if (CinCheck(cin))
				break;

			if (menu < 0 || menu > 1)
			{
				cout << "�Է��� �ùٸ��� �ʽ��ϴ�." << endl;
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