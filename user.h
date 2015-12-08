struct userinfo {
	int flag;/*trag thai tien tr*/
	char username[30];
	char pass[16];
	int success;//=0 fail;=1 ok;=2 default or none
	int errornumber;//=10 loi signup;=20 error login;=30 error Wrong Moves; =0 none;=100 Success
	};
struct cotuong{
	struct userinfo user;
	int start;//nc di
	int end;//nc den
	//int errornumber;
};

