#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <fstream>
using namespace std;

class User {
public:
	int id;
	string name;
	bool dayShift; // 0 -night, 1 - day;
	int salary;// 10 000 to 20 000
	
	User() = default;

	User(int id, string name, bool dayShift, int salary)
		:id(id),
		name(name),
		dayShift(dayShift),
		salary(salary) {}

	bool operator== (const User& other)const {
		return id == other.id && name == other.name;
	}

	friend ostream& operator<<(ostream& out, const User& obj) {
		out << obj.id << ' ' << obj.name << ' ' << obj.dayShift << 
			' ' << obj.salary << ' ';
		return out;
	}

	friend istream& operator>>(istream& in, User& obj) {
		in >> obj.id >> obj.name >> obj.dayShift >> obj.salary;
		return in;
	}
};

map<string, User> g_Users;// g - global

void task(int count) {
	vector<User> users;
	users.reserve(count);
	auto begin = chrono::steady_clock::now();
	for (int i = 0; i < users.capacity(); i++) {
		//users.emplace_back(i + 1, "user" + to_string(i + 1));
		users.emplace_back(i + 1,
			"user" + to_string(i + 1),
			static_cast<bool>(::rand() % 2),
			10000 + ::rand());
	}
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>
		(end - begin);
	std::cout << "create vector: " << elapsed_ms.count() << " ms\n";

	map<string, User*> searchTree;
	begin = chrono::steady_clock::now();
	for (auto& user : users){
		searchTree.insert({user.name, &user});
	}
	end = chrono::steady_clock::now();
	elapsed_ms = chrono::duration_cast<chrono::nanoseconds>
		(end - begin);
	std::cout << "create map: " << elapsed_ms.count() << " ms\n";

	begin = chrono::steady_clock::now();
	auto vec_tmp = find(
		users.begin(),
		users.end(),
		User{ count, "user" + to_string(count), true, 11111}
	);
	end = chrono::steady_clock::now();
	elapsed_ms = chrono::duration_cast<chrono::nanoseconds>
		(end - begin);
	std::cout << "Fined in vector: " << elapsed_ms.count() << " ms\n";

	begin = chrono::steady_clock::now();
	auto map_tmp = searchTree.find("user" + to_string(count));
	end = chrono::steady_clock::now();
	elapsed_ms = chrono::duration_cast<chrono::nanoseconds>
		(end - begin);
	std::cout << "Fined in map: " << elapsed_ms.count() << " ms\n";

	ofstream out("base.txt", ios::app);
	for (auto& user : users) {
		//cout << User << '\n';
		out << user << '\n';
	}
	out.close();
	//---------------



}

int main() {
	task(10);

	/*g_Users.insert({"user", {1, "user"}});
	User local;
	local.id = 2;
	local.name = "User2";
	g_Users.insert({ local.name, local});
	g_Users["user3"];
	g_Users["user3"].id = 3;
	g_Users["user3"].name = "user3";
	pair<const string, User> &tmp
		= *(g_Users.begin());
	
	auto where_ = g_Users.find("user3");
	where_->second.id;

	auto &[login, user] = *(g_Users.find("user3"));
	user.id;*/
	
	return 0;
}