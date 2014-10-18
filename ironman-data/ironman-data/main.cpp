//
//  main.cpp
//  ironman-data
//
//  Created by Andrey Zaytsev on 10/18/14.
//  Copyright (c) 2014 AAAD. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Including Myo SDK
#include <myo/myo.hpp>


class DataCollector : public myo::DeviceListener {
public:
    /*
    DataCollector()
    : onArm(false), roll_w(0), pitch_w(0), yaw_w(0), currentPose()
    {
    }
     */
    
    void onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion){
        knownMyos.push_back(myo);
    }

    
    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        //roll_w = 0;
        //pitch_w = 0;
        //yaw_w = 0;
        //onArm = false;
    }
    
    void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
    {
        using std::cout;
        using std::endl;
        cout << "Myo " << identifyMyo(myo) << " has connected." << endl;
    }
    
    void onDisconnect(myo::Myo* myo, uint64_t timestamp)
    {
        using std::cout;
        using std::endl;
        cout << "Myo " << identifyMyo(myo) << " has disconnected." << endl;
    }
    
    // onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
    // as a unit quaternion.
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;
        
        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
        float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                          1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
        
        // Convert the floating point angles in radians to a scale from 0 to 18.
        if(identifyMyo(myo) == 'L') {
            roll_w1 = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
            pitch_w1 = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
            yaw_w1 = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
        } else {
            //This is the right myo
            roll_w2 = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
            pitch_w2 = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
            yaw_w2 = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
        }
        if(roll_w1_o == roll_w1 || roll_w2_o == roll_w2 ||
           pitch_w1_o == pitch_w1 || pitch_w2_o == pitch_w2 ||
           yaw_w1_o == yaw_w1 || yaw_w2_o == yaw_w2){
            return;
        }
        
        //string str = std::to_string(roll_w) + " " + std::to_string(pitch_w) + " " + std::to_string(yaw_w);
        print();
        
        
    }
    
    // onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
    // making a fist, or not making a fist anymore.
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
    {
        /*
        using std::cout;
        using std::endl;
        using std::string;
        using std::flush;
         */
        using std::string;
        
        currentPose = pose;
        
        // Vibrate the Myo whenever we've detected that the user has made a fist.
        if (pose == myo::Pose::fist) {
            myo->vibrate(myo::Myo::vibrationMedium);
        }
        
        //cout << identifyMyo(myo) << " " << roll_w << " " << pitch_w << " " << yaw_w << " ";
        //cout << pose.toString() << endl;
        
        //Old string format
        //cout << (whichArm == myo::armLeft ? "L " : "R ") << roll_w << " " << pitch_w << " " << yaw_w << " ";
        //cout << flush;
        if(identifyMyo(myo) == 'L') {
            m1 = pose.toString();
        } else {
            //This is the right myo
            m2 = pose.toString();
        }
        print();
        
    }
    
    // onArmRecognized() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
    // arm. This lets Myo know which arm it's on and which way it's facing.
    void onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
    {
        //onArm = true;
        //whichArm = arm;
    }
    
    void onArmLost(myo::Myo* myo, uint64_t timestamp)
    {
        //onArm = false;
    }
    
    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    
    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
    {
        using std::cout;
        using std::endl;
        using std::string;
        using std::flush;
        
        
        //string buffer;
        //output_file.seekg(0, output_file.end);
        //output_file.open("output");
        //output_file << "L\t" << roll_w1 << "\t" << pitch_w1 << "\t" << yaw_w1;
        //output_file << "\t" << m1;
        //output_file << "\tR\t" << roll_w2 << "\t" << pitch_w2 << "\t" << yaw_w2;
        //output_file << "\t" << m2<< "\n";
        
       // output_file = fopen("output.txt", "w");
        //fseek(output_file, 0, SEEK_SET);
        
//        fputs(buffer , output_file);
        //output_file;
        
        // Print out the orientation. Orientation data is always available, even if no arm is currently recognized.
        
        //cout << "Myo " << identifyMyo(
        
        
        //if (onArm) {

        string poseString = currentPose.toString();
          /*
            cout << poseString << endl;
        } else {
            // Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
            cout << "[?]" << endl;
        }
         
         cout << identifyMyo(myo) << " " << roll_w << " " << pitch_w << " " << yaw_w << " ";
         
         */
        cout<<"L";
        if (roll_w1 != roll_w1_old) {
            cout<<" roll: "<<(roll_w1-roll_w1_old);
            roll_w1_old = roll_w1;
        }
        if (pitch_w1 != pitch_w1_old){
            cout<<" pitch: "<<(pitch_w1-pitch_w1_old);
            pitch_w1_old = pitch_w1;
        }
        if (yaw_w1 != yaw_w1_old){
            cout<<" yaw: "<<(yaw_w1-yaw_w1_old);
            yaw_w1_old = yaw_w1;
        }
        cout<<endl;
        cout<<"R";
        if (roll_w2 != roll_w2_old) {
            cout<<" roll: "<<(roll_w2-roll_w2_old);
            roll_w2_old = roll_w2;
        }
        if (pitch_w2 != pitch_w2_old){
            cout<<" pitch: "<<(pitch_w2-pitch_w2_old);
            pitch_w2_old = pitch_w2;
        }
        if (yaw_w2 != yaw_w2_old){
            cout<<" yaw: "<<(yaw_w2-yaw_w2_old);
            yaw_w2_old = yaw_w2;
        }
        cout<<endl;
//        cout << "L\t" << roll_w1 << "\t" << pitch_w1 << "\t" << yaw_w1;
//        cout << "\t" << m1;
//        cout << "\tR\t" << roll_w2 << "\t" << pitch_w2 << "\t" << yaw_w2;
//        cout << "\t" << m2 << endl;
        
        //cout << flush;
    }
    
    char identifyMyo(myo::Myo * myo) {
        for(size_t i =0; i<knownMyos.size(); i++){
            if(knownMyos[i]==myo){
                return (i+1) == 2 ? 'R':'L';
            }
        }
        return 0;
    }
    
    // These values are set by onArmRecognized() and onArmLost() above.
    //bool onArm;
    //myo::Arm whichArm;
    
    // These values are set by onOrientationData() and onPose() above.
    int roll_w1, pitch_w1, yaw_w1;
    int roll_w2, pitch_w2, yaw_w2;

    int roll_w1_old, pitch_w1_old, yaw_w1_old;
    int roll_w2_old, pitch_w2_old, yaw_w2_old;

    int roll_w1_o, pitch_w1_o, yaw_w1_o;
    int roll_w2_o, pitch_w2_o, yaw_w2_o;
    
    myo::Pose currentPose;
    std::vector<myo::Myo*> knownMyos;
    std::string m1, m2;
    //std::ifstream output_file;
    
};

int main(int argc, const char * argv[])
{
    // We catch any exceptions that might occur below -- see the catch statement for more details.
    try {
        
        myo::Hub hub("com.aaad.ironman-data");
        
        std::cerr << "Attempting to find a Myo..." << std::endl;
        
        // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
        // immediately.
        // waitForAnyMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
        // if that fails, the function will return a null pointer.
        //myo::Myo* myo = hub.waitForMyo(10000);
        
        // If waitForAnyMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
        /*
        if (!myo) {
            throw std::runtime_error("Unable to find a Myo!");
        }
         */
        
        // We've found a Myo.
        std::cerr << "Connected to a Myo armband!" << std::endl << std::endl;
        
        // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
        DataCollector collector;
        
        // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
        // Hub::run() to send events to all registered device listeners.
        hub.addListener(&collector);
        
        
        //char buffer[100];
        
        
        // Finally we enter our main loop.
        while (1) {
            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
            hub.run(1000/20);
            // After processing events, we call the print() member function we defined above to print out the values we've
            // obtained from any events that have occurred.
            //collector.print();
        }
        
        // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
    return 0;
}

