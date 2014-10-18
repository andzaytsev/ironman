#include <string>

class State {
	private :
		char state;
		void landToFly(int pitch, std::string p1, std::string p2) 
		{
			
		}
		void hoverToFly(int pitch, std::string p1, std::string p2)
		{
		}
		void flyTo(int pitch, std::string p1, std::string p2)
		{
		}

	public :
		State() 
		{
			state = 'l';
		}

		std::string getCurrentState() 
		{
			using std::string;

			string str;
			if(state == 'l'){
				str = "land";
			} else if(state == 'f') {
				str = "fly";
			} else if(state == 'h') {
				str = "hover";
			}
			return str;
		}	

		void updateState(int yaw, int roll, int pitch, std::string p1, std::string p2) 
		{
			using std::string;

			if(state == 'l') {
				landToFly(pitch, p1, p2);
			} else if(state == 'h') {
				hoverToFly(pitch, p1, p2);
			} else {
				flyTo(pitch, p1, p2);
			}
		}

		
};
