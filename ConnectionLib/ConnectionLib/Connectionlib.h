
namespace ConnectionLib
{
	class Lib
	{
	public:
		// make a connection with tcp server
		static int init();

		// send data
		static char* SendData(char name[], int mmsi, double lat, double lon);

		
	};
}