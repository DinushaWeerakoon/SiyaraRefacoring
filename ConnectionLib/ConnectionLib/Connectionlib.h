
namespace ConnectionLib
{
	class Lib
	{
	private:
		static bool instanceFlag;
		static Lib *instance;
		Lib(){}

	public:
		static Lib* getInstance();

		// make a connection with tcp server
		static int  init();

		// send data
		//static int  SendData(char name[], int mmsi, double lon, double lat, int rot, double sog, double cog, char dest[]);
		static int  SendData(char name[], int mmsi, double lat, double lon, const char* recvtime);
		static int close();

		
	};
}