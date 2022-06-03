#ifndef CLIENT_HPP
#define CLIENT_HPP
 
class Client
{
	private:
		std::string     nickname;
		std::string     name;
		sock_t          fd;

	public:
		Client();
		~Client();
};
#endif