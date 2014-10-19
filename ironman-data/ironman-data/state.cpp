#include <string>
#include <iostream>

class State {
	private :
		char state;

		/**
		 * 1 for up, 0 for none, -1 for down
		 */
		int flyDir;

		char fire;

		void landToFly(int pitch, std::string p1, std::string p2);

		void hoverToFly(int pitch, std::string p1, std::string p2);

		void flyTo(int pitch, std::string p1, std::string p2);

	public :
		State();

		std::string getCurrentState();

		void updateState(int yaw, int roll, int pitch, std::string p1, std::string p2);
		
};

State::State() {
	state = 'l';
	flyDir = 0;
	fire = 'n';
}

std::string State::getCurrentState()
{
	using std::string;

	string str;
	if(state == 'l'){
		str = "land";
	} else if(state == 'f') {
		str = "fly";

		if(flyDir == 1) {
			str += " up";
		} else if(flyDir == -1){
			str += " down";
		}
	} else if(state == 'h') {
		str = "hover";
	}

	if(fire != 'n') {
		if(fire == 'b') str += " fire both";
		else if(fire == 'l') str += " fire left";
		else if(fire == 'r') str += " fire right";
		fire = 'n';
	}

	return str;
}	

void State::updateState(int yaw, int roll, int pitch, std::string p1, std::string p2)
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

void State::flyTo(int pitch, std::string p1, std::string p2)
{
	if(pitch >= 15 && (p1 == "fist" || p2 == "fist" || p1 == "rest" || p2 == "rest")) {
		flyDir = -1;
	} else if((pitch<15 &&  pitch>=7) && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")){
		state = 'h';
		flyDir = 0;
	} else if(pitch >= 15 && (p1 == "fingersSpread" || p2 == "fingersSpread" || p1 == "waveOut" || p2 == "waveOut")) {
		flyDir = 1;
	}
}
