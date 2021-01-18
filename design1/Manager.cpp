#include "stdafx.h"
#include "Manager.h"

Manager::Manager() {} //default constructor

bool Manager::verifyPassword(string e, string p) {
	string a[5];
	ifstream data;
	data.open("UserData.txt");
	
	while (data >> a[fname] >> a[lname] >> a[email] >> a[pword] >> a[mname]) {
		if (e.compare(a[email]) == 0 && p.compare(a[pword]) == 0) { //email and password matches database
			data.close();
			return true;
		}
	}
	data.close();
	return false;
}

bool Manager::userExists(string e) {
	string a[5];
	ifstream data;
	data.open("UserData.txt");

	while (data >> a[fname] >> a[lname] >> a[email] >> a[pword] >> a[mname]) {
		if (e.compare(a[email]) == 0) { //email matches database
			data.close();
			return true;
		}
	}
	data.close();
	return false;
}

bool Manager::passwordNotSame(string p1, string p2) {
	if (!p1.compare(p2) == 0) { //verification password doesn't match
		return true;
	}
	return false;
}

bool Manager::multipleMaidenNames(string mn) {
	string mname = mn;
	for (int i = 0; i < mname.length(); i++) {
		if (isspace(mname.at(i)) != 0) { //space between the maiden name
			return true;
		}
	}
	return false;
}

Status Manager::ValidateLogin(User user) {
	if (verifyPassword(user.getEmail(), user.getPassword())) {
		stat = Status(Status::userSession); //ok status
		return stat;
	}
	else {
		Error e(errorCodes[0], errorMsgs[0]); //"Incorrect email or password"
		stat = Status(e, Status::LoginErrorSession); //error status
		return stat;
	}
}

Status Manager::ValidateRegistration(User user) {
	if (user.getFirstName().empty() || user.getLastName().empty() || 
		user.getEmail().empty() || user.getPassword().empty() || 
		user.getsecpassword().empty() || user.getMaidenName().empty()) { //check fields are empty
		Error e(errorCodes[1], errorMsgs[1]); //"Please fill all fields"
		stat = Status(e, Status::RegistrationErrorSession); //error status
		return stat;
	}
	if (userExists(user.getEmail())) {
		Error e(errorCodes[2], errorMsgs[2]); //"user already exists"
		stat = Status(e, Status::RegistrationErrorSession); //error status
		return stat;
	}
	else if (passwordNotSame(user.getPassword(), user.getsecpassword())) {
		Error e(errorCodes[3], errorMsgs[3]); //"Passwords don't match"
		stat = Status(e, Status::RegistrationErrorSession); //error status
		return stat;
	}
	else if (multipleMaidenNames(user.getMaidenName())) {
		Error e(errorCodes[4], errorMsgs[4]); //"Please enter only one maiden name"
		stat = Status(e, Status::RegistrationErrorSession); //error status
		return stat;
	}
	else {
		ofstream data;
		data.open("UserData.txt", ios::app);
		//save User in file:
		data << "\n" + user.getFirstName() + " " << user.getLastName() + " " <<
			user.getEmail() + " " << user.getPassword() + " " << user.getMaidenName(); 
		data.close();

		stat = Status(Status::RegistrationSession); //ok status
		return stat;
	}
}

Status Manager::ValidateRequestReset(User user) {
	string a[5];
	ifstream data;
	data.open("UserData.txt");
	while (data >> a[fname] >> a[lname] >> a[email] >> a[pword] >> a[mname]) {
		if (user.getEmail().compare(a[email]) == 0 && user.getMaidenName().compare(a[mname]) == 0) { //match found
			data.close();
			stat = Status(Status::ForgotpasswordSession); //ok status
			return stat;
		}
	}
	data.close();
	Error err(errorCodes[5], errorMsgs[5]); //"no such user found"
	stat = Status(err, Status::ForgotPasswordErrorSession); //error status
	return stat;
}

Status Manager::ValidateResetPassword(User user) {
	if (passwordNotSame(user.getPassword(), user.getsecpassword())) {
		Error err(errorCodes[6], errorMsgs[6]); //Passwords don't match
		stat = Status(err, Status::ForgotPasswordErrorSession); //error status
		return stat;
	}
	else {
		string a[5];
		vector<User> userList;

		ifstream data;
		data.open("UserData.txt");
		//read all data into a
		while (data >> a[fname] >> a[lname] >> a[email] >> a[pword] >> a[mname]) {
			//when user found, change password 
			if (a[email].compare(user.getEmail()) == 0) {
				a[pword] = user.getPassword(); 
			}
			User u(a[fname], a[lname], a[email], a[pword], a[mname]);
			userList.push_back(u); // add new user to userList
		}
		data.close();

		ofstream data2;
		data2.open("UserData.txt");
		//write all users in userList into the file, line by line
		for (int i = 0; i < userList.size(); i++) {
			data2 << userList[i].getFirstName() << " " << userList[i].getLastName() << " " << userList[i].getEmail()
				<< " " << userList[i].getPassword() << " " << userList[i].getMaidenName() << "\n";
		}
		data2.close();
		stat = Status(Status::ForgotpasswordSession); //okay status
		return stat;
	}
}