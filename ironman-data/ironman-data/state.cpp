#include <string>
#include <iostream>

class State {
	private :
		char state;

		/**
		 * 1 for up, 0 for none, -1 for down
		 */
		int flyDir;

		char fb;

		char fire;

		void landToFly(int pitch, std::string p1, std::string p2);

		void hoverToFly(int pitch, std::string p1, std::string p2);

		void flyTo(int yaw1, int yaw2, int pitch, std::string p1, std::string p2);

	public :
		State();

		std::string getCurrentState();

		void updateState(int yaw, int roll, int pitch, std::string p1, std::string p2);
		
};

State::State() {
	state = 'l';
	flyDir = 0;
	fire = 'n';
	fb = 0;
}

std::string State::getCurrentState()
{
	using std::string;

	string str;
	if(state == 'l'){
		//str = "land";
		str = "l";
	} else if(state == 'f') {
		//str = "fly";
		str = "f";

		if(flyDir == 1) {
			//str += "Up";
			str += "u";
		} else if(flyDir == -1){
			//str += "Down";
			str += "d";
		}

		if(fb == 'f') {
			//forward
			str += "f";
		} else if(fb == 'b') {
			str += "b";
		} else if(fb == 'l') {
			str += "l";
		} else if(fb == 'r') {
			str += "r";
		}
	} else if(state == 'h') {
		//str = "hover";
		str = "h";
	}

	if(fire != 'n') {
		//if(fire == 'b') str += " fireBoth";
		if(fire == 'b') str += " fb";
		//else if(fire == 'l') str += " fireLeft";
		else if(fire == 'l') str += " fl";
		//else if(fire == 'r') str += " fireRight";
		else if(fire == 'r') str += " fr";
		fire = 'n';
	}

	return str;
}	

void State::updateState(int yaw1, int yaw2, int pitch, std::string p1, std::string p2)
{
	using std::string;

	if(state == 'l') {
		landToFly(pitch, p1, p2);
	} else if(state == 'h') {
		hoverToFly(pitch, p1, p2);
	} else {
		flyTo(yaw1, yaw2, pitch, p1, p2);
	}
}

void State::landToFly(int pitch, std::string p1, std::string p2)
{	
	if(pitch >= 15 && (p1 == "fingersSpread" || p1 == "waveOut" || p2 == "fingersSpread" || p2 == "waveOut")) {
		state = 'f';
		flyDir = 1;
	} else if((p1 == "fingersSpread" || p2 == "waveOut") && (p2 == "fingersSpread" || p2 == "waveOut")){
		fire = 'b';
	} else if(p1 == "fingersSpread" || p1 == "waveOut"){
		fire = 'l';
	} else if(p2 == "fingersSpread" || p2 == "waveOut"){
		fire = 'r';
	}
}

void State::hoverToFly(int pitch, std::string p1, std::string p2)
{
	if(pitch >= 15 && (p1 == "fingersSpread" || p1 == "waveOut" || p2 == "fingersSpread" || p2 == "waveOut")) {
		//we are going up
		state = 'f';
		flyDir = 1;
	} else if(pitch >= 15 && (p1 == "fist" || p2 == "fist" || p1 == "rest" || p2 == "rest")) {
		//we are going down
		state = 'f';
		flyDir = -1;
	} else if((p1 == "fingersSpread" || p2 == "waveOut") && (p2 == "fingersSpread" || p2 == "waveOut")){
		fire = 'b';
	} else if(p1 == "fingersSpread" || p1 == "waveOut"){
		fire = 'l';
	} else if(p2 == "fingersSpread" || p2 == "waveOut"){
		fire = 'r';
	}
}

void State::flyTo(int yaw1, int yaw2, int pitch, std::string p1, std::string p2)
{
	if(pitch >= 15 && (p1 == "fist" || p2 == "fist" || p1 == "rest" || p2 == "rest")) {
		flyDir = -1;
	} else if((pitch<9 &&  pitch>=7) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")){
		state = 'h';
		flyDir = 0;
	} else if(pitch >= 15 && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		flyDir = 1;
	} else if((pitch < 15 && pitch >=9) && (yaw1 < 10 && yaw2 < 10) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		fb = 'f';
	} else if((pitch < 15 && pitch >=9) && (yaw1 >= 10 && yaw2 >= 10) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		fb = 'b';
	} else if((pitch < 15 && pitch >=9) && (yaw1 < 10 && yaw2 >= 10) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		fb = 'l';
	} else if((pitch < 15 && pitch >=9) && (yaw1 >= 10 && yaw2 < 10) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		fb = 'r';
	}
}
